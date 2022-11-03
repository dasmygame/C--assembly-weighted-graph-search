//=================================================================
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================

/*     D i a m o n d   S e a r c h
Student Name:
Date:

ECE 2035 Project 1-1

This is the only file that should be modified for the C implementation
of Project 1.

Do not include any additional libraries.
------------------------------------------
This program finds the lowest cost 5-step path out of a diamond of weighted 
squares. */

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 // RESET THIS TO 0 BEFORE SUBMITTING YOUR CODE

/* Example from Project description (illustrated in Fig.1):
int Array[121] = {
  10000, 10000, 10000, 10000, 10000, -99,  10000, 10000, 10000, 10000, 10000,
  10000, 10000, 10000, 10000,   -49, -37,  83, 10000, 10000, 10000, 10000,
  10000, 10000, 10000,   -64,    19,  67, -82,    -2, 10000, 10000, 10000,
  10000, 10000,   -30,   -37,    64, -68,  92,    40,     2, 10000, 10000,
  10000,    27,   -70,    52,    79, -77, -31,   -41,   -77,   -81, 10000,
     80,   -73,    -8,   -59,    53,   0, -47,    46,   -32,    98,   -98,
  10000,    13,   -99,   -47,   -60, -14, -45,    80,    15,    69, 10000,
  10000, 10000,    -9,     8,   -88,  69,  54,    12,    53, 10000, 10000,
  10000, 10000, 10000,   -21,     3, -61, -43,    29, 10000, 10000, 10000,
  10000, 10000, 10000, 10000,    45, -34, -85, 10000, 10000, 10000, 10000,
  10000, 10000, 10000, 10000, 10000,  59, 10000, 10000, 10000, 10000, 10000 };

DO NOT use this to provide a test case to your program.
Instead, provide the test case as a command-line argument in the form of
a test file (e.g., test-307.txt).  The code below uses Load_Mem to read the
values in a given test file into the local Array in main.
*/

#define ArraySize 121
//#define start 60

int main(int argc, char *argv[]) {
  int Array[ArraySize];
  int Length, MinCost = 10000;
  int  Load_Mem(char *, int *);

  if (argc != 2) {
    printf("usage: P1-1 valuefile\n");
    exit(1);
  }
  Length = Load_Mem(argv[1], Array);
  if (Length != ArraySize) {
     printf("valuefile does not contain valid data.\n");
     exit(1);
  }

  /* Your diamond search code goes here */
  //Northeast Quadrant
   int start = 60;
   int minPath = 1000;

    //STRAIGHT_PATHS
    for(int i = 0; i < 4; i++) {
        start = 60;
        for (int j = 0; j < 5; j++) {
            switch(i) {
                case 0:
                    Array[start + 1] += Array[start];
                    start += 1;
                    break;
                case 1:
                    Array[start - 11] += Array[start];
                    start += -11;
                    break;
                case 2:
                    Array[start - 1] += Array[start];
                    start -= 1;
                    //printf("%d - array(start-1)\n", Array[start-1]);
                    break;

                case 3:
                    Array[start + 11] += Array[start];
                    start += 11;
                    break;
            }
        }
        if (Array[start] < minPath) {
            minPath = Array[start];
        }
    }
    //printf("%d - Array(55)", Array[55]);
    //NE
    start = 50;
    for (int i = 0; i < 4; i++) {
        start = 50 - 11*i;
        for(int j = i; j < 4 ; j++) {
            if (Array[start - 1] < Array[start + 11]) {
                Array[start] += Array[start - 1];
                start += 1;
            } else {
                Array[start] += Array[start + 11];
                start += 1;
            }
        }
        if(Array[start-1] < minPath) {
            minPath = Array[start-1];
        }
    }
 

    //NW
    start = 48;
    for (int i = 0; i < 4; i++) {
        start = 48 - 11*i;
        for(int j = i; j < 4; j++) {
            //printf("%d start - %d array(start) - %d minpath - %d i - %d j \n", start, Array[start], minPath, i, j);

            if (Array[start + 1] < Array[start + 11]) {
                Array[start] += Array[start + 1];
                start -= 1;
            } else {
                Array[start] += Array[start + 11];
                start -= 1;
            }
            //printf("%d - array(start+1)\n", Array[start+1]);
        }
        if(Array[start+1] < minPath) {
            minPath = Array[start+1];
        }
        //printf("%d minpath\n", minPath);
    }

    //SW
    start = 70;
    for (int i = 0; i < 4; i++) {
        start = 70 + 11*i;
        for(int j = i; j < 4 ; j++) {
            //printf("%d start - %d array(start) - %d minpath - %d i - %d j \n", start, Array[start], minPath, i, j);

            if (Array[start + 1] < Array[start - 11]) {
                Array[start] += Array[start + 1];
                start -= 1;
            } else {
                Array[start] += Array[start - 11];
                start -= 1;
            }
            //printf("%d - array(start+1)\n", Array[start+1]);
        }
        if(Array[start+1] < minPath) {
            minPath = Array[start+1];
        }
        //printf("%d minpath\n", minPath);
    }

    //SE
    start = 72;
    for (int i = 0; i < 4; i++) {
        start = 72 + 11*i;
        for(int j = i; j < 4; j++) {
            //printf("%d start - %d array(start) - %d minpath - %d i - %d j \n", start, Array[start], minPath, i, j);

            if (Array[start - 1] < Array[start - 11]) {
                Array[start] += Array[start - 1];
                start += 1;
            } else {
                Array[start] += Array[start - 11];
                start += 1;
            }
            //printf("%d - array(start+1)\n", Array[start+1]);
        }
        if(Array[start-1] < minPath) {
            minPath = Array[start-1];
        }
        //printf("%d minpath\n", minPath);
    }





  MinCost = minPath;

  if (DEBUG){
    printf("Remember to reset DEBUG to 0 before submitting your code.");
  }
  /* include this print statement. */ 
  printf("The shortest path cost is [%d]\n", MinCost);
  return 0;
}

/* This routine loads in up to ArraySize newline delimited integers from
a named file in the local directory. The values are placed in the
passed integer array. The number of input integers is returned. */

int Load_Mem(char *InputFileName, int IntArray[]) {
   int	N, Addr, Value, NumVals;
   FILE	*FP;

   FP = fopen(InputFileName, "r");
   if (FP == NULL) {
      printf("%s could not be opened; check the filename\n", InputFileName);
      return 0;
   } else {
      for (N=0; N < ArraySize; N++) {
         NumVals = fscanf(FP, "%d: %d", &Addr, &Value);
         if (NumVals == 2)
            IntArray[N] = Value;
         else
            break;
      }
      fclose(FP);
      return N;
   }
}


      
