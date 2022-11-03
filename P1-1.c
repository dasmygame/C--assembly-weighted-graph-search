

#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0 

/* 
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


*/

#define ArraySize 121
#define source = 60;

int findMin(int num1, int num2) {
   //finding and returning minimum of num1 and num2
   if (num2 < num1) {
      return num2;
   } else {
      return num1;
   }
}

//Sorts NorthEast quadrant and returns the minimum from quadrant
int sortNE(int Array[ArraySize], int start, int numSteps) {
    //maximum of 5 moves
    while(numSteps != 5) {
      //double recursive call checking all paths to a vertex
      return findMin((Array[start] + sortNE(Array, start-11, numSteps+1)), (Array[start] + 
         sortNE(Array, start+1, numSteps+1)));
    }
    return Array[start];

}

//Sorts NorthWest quadrant and returns the minimum from quadrant
int sortNW(int Array[ArraySize], int start, int numSteps) {
   //maximum of 5 moves
   while (numSteps != 5) {
      //double recursive call checking all paths to a vertex
      return findMin((Array[start] + sortNW(Array, start-11, numSteps+1)), (Array[start] + 
        sortNW(Array, start-1, numSteps+1)));
   }
   return Array[start];

}

//Sorts SouthWest quadrant and returns the minimum from quadrant
int sortSW(int Array[ArraySize], int start, int numSteps) {
   //maximum of 5 moves
   while (numSteps != 5) {
      //double recursive call checking all paths to a vertex
      return findMin((Array[start] + sortSW(Array, start+11, numSteps+1)), (Array[start] + 
         sortSW(Array, start-1, numSteps+1)));
   }
   return Array[start];
}

//Sorts SouthEast quadrant and returns the minimum from quadrant
int sortSE(int Array[ArraySize], int start, int numSteps) {
   //maximum of 5 moves  
   while (numSteps != 5) {                
      //double recursive call checking all paths to a vertex
      return findMin((Array[start] + sortNE(Array, start+11, numSteps+1)), (Array[start] + 
         sortNE(Array, start+1, numSteps+1)));
   }
   return Array[start]; 
}

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

//computing and storing minimums of all of the quadrants
  int neMin = sortNE(Array, 60, 0);
  int nwMin = sortNW(Array, 60, 0);
  int seMin = sortSE(Array, 60, 0);
  int swMin = sortSW(Array, 60, 0);

//comparing the minimums of all the qudrants, storing overall minimum in MinCost
  int min1 = findMin(neMin, nwMin); 
  int min2 = findMin(seMin, swMin);
  MinCost = findMin(min1, min2);
  
  //int neMin = sortNE(Array, 60, 0);
  //printf("%d", neMin);
  //printf("%d", nwMin);
  //printf("%d", seMin);
  //printf("%d", swMin);

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


      
