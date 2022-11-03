#=================================================================
# Copyright 2022 Georgia Tech.  All rights reserved.
# The materials provided by the instructor in this course are for
# the use of the students currently enrolled in the course.
# Copyrighted course materials may not be further disseminated.
# This file must not be made publicly available anywhere.
# =================================================================
#     D i a m o n d   S e a r c h
#
# P1-2
# Student Name: Rahul Das
# Date: 10/24/22
#
# This program finds the shortest path out of a diamond of weighted squares.
#
#===========================================================================
# CHANGE LOG: brief description of changes made from P1-2.asm
# to this version of code.
# Date  Modification
# 09/22 Looping through squares from start to one of the corners
# 09/23 Computing the total cost of a path from start to that corner 
# 10/02 Started straight paths method, completed East path
# 10/04 Created straight paths method for North, South, West
# 10/09 Converting jumping straight paths to jal function from main
# 10/10 found consistest paramters to change in main to reduce lines 
#       for the straight paths.
# 10/14 Created NE quadrant method that mirrors iterative C code 
# 10/15 Converted NE quadrant method to jal from main with parameters
# 10/17 Created NW quadrant method that mirrors iterative C code
# 10/18 Aligned "horiz" and "vert" paramaters for NW and NE
# 10/19 Removed all immediated values (addi) from array index incrementers
# 10/19 Replaced all immediate values with "horiz" and "vert" paramaters
# 10/20 Combined NW and NE functions into one Quad function with 
#       unified parameters that are switch before each jal in main
# 10/21 Changed parameters and called function on main for SW and SE
# 10/22 Added a minPath check at the endQuad in order to check for the 
#       minPath at the last index, which could contain potential minPath
# 10/24 Deleted unneccessary jumps and unneeded registers to optimize
#===========================================================================

.data
Array:	.alloc	121	# allocate static space for padded weight map

.text
PathOut:	addi	$1, $0, Array	# set memory base
                swi	514		# create weight map in memory

# your code goes here

        addi $16, $0, 5			# maxSteps = 5
        add $17, $31, $0		# save for JAL
        addi $14, $0, 1000		# minPath = 1000
        addi $5, $0, 0          # int j = 0
        addi $12, $0, 0			# int i = 0
        addi $2, $0, 240        # start = 240
		j main

# MAIN METHOD1 ------------------------------>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

main:   addi $6, $0, 4			# Move = 4
		jal straight            # East

		addi $6, $0, -44		# Move = -44
        jal straight            # North

		addi $6, $0, -4		    # Move = -4
        jal straight            # West
        
		addi $6, $0, 44		    # Move = +44
        jal straight            # South


		addi $10, $0, -4		# horiz = 4 = +1
		addi $13, $0, 44		# vert = 48 = +12
		addi $2, $0, 200 		# start = 200 = 50*4
		add $16, $0, $2 		# start = 200 = 50*4
		

		jal Quad			#starting quadrant NE

		
		addi $10, $0, 4			# horiz = 4 = +1
		#addi $13, $0, 44		# vert = 48 = +12
		addi $2, $0, 192 		# start 
		add $16, $0, $2 		# start 
		

		jal Quad			#starting quadrant NW

		
		#addi $10, $0, 4			# horiz = 4 = +1
		addi $13, $0, -44		# vert = 48 = +12
		addi $2, $0, 280 		# start 
		add $16, $0, $2 		# startCopy
		

		jal Quad			#starting quadrant SW

	
		addi $10, $0, -4		# horiz = 4 = +1
		#addi $13, $0, -44		# vert = 48 = +12
		addi $2, $0, 288 		# start 
		add $16, $0, $2 		# startCopy 
		

		jal Quad			#starting quadrant SE

		
		j end



# STRAIGHT PATHS ------------------------------>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		
		
straight:	beq $12, $16, checkMin		# i=5, branch to restart 
		lw $9, Array($2)		# loading Array[start]
		add $2, $2, $6			# start += move
		lw $4, Array($2)		# loading Array[start+move]
		add $4, $9, $4			# Array[start+move] + Array[start]
		sw $4, Array($2)		# Array[start+move] += Array[start]
		addi $12, $12, 1			# i += 1
		j straight

checkMin:	slt $11, $4, $14	# set if Array[start] < minPath
		beq $11, $0, reset
        add $14, $0, $4

reset:  addi $2, $0, 240        # reset start = 240
        addi $12, $0, 0			# int i = 0
		jr $31


# QUADRANT PATHS ------------------------------>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#	$12 = i = 0
#	$5 = j = 0
#	$2 = start
#	$10 =  horiz
#	$13 = vert
#	$16 = newStart


Quad:	slti	$11, $12, 4		# shift if i < 4
		beq		$11, $0, endQuad	# BRANCH if i = 4

jLoop:	slti	$11, $5, 3			# shift if j < 4
		beq		$11, $0, checkHoriz	# BRANCH if j = 4

checkHoriz:	add $6, $2, $10		# start + horiz
			add $7, $2, $13		# start + vert
			lw $6, Array($6)	#loading Array[start+horiz]
			lw $7, Array($7)	#loading Array[start+vert]
			lw $9, Array($2)	#loading Array[start]
			slt $11, $6, $7		#set if A[horiz] < A[vert]
			beq $11, $0, checkVert
			add $9, $6, $9		#Array[start] + Array[start+horiz]
			sw $9, Array($2)	#Array[start] += Array[start+horiz]
			j incJ

checkVert: 	add $7, $7, $9		# Array[start] + Array[start+vert]
			sw $7, Array($2)	# Array[start] += Array[start+vert] 
	
incJ:		slti	$11, $5, 3			# shift if j < 4
			beq		$11, $0, incI		# BRANCH if j = 4
			addi $5, $5, 1				# j++
			sub $2, $2, $10 			# start - horiz = start + 1
			j jLoop

incI: 		addi $12, $12, 1		# i++	
			add $5, $0, $12			# j = i
			slti $11, $12, 4
			beq $11, $0, endQuad	# if i = 4 branch to endQuad
			lw $4, Array($2)		# loading Array[] after 5 steps 
			slt $11, $4, $14		# set if Array[current] < minPath
			beq $11, $0, resetStart
			add $14, $0, $4			# setting new minPath

resetStart: mult $12, $13			# i*44
			mflo $11
			sub $2, $16, $11		# start = 50-11i = 200 - 44i
			j Quad

endQuad:	lw $4, Array($2)		# loading Array[start]
			slt $11, $4, $14		# set if Array[start] < minPath
			beq $11, $0, next 		# if minPath < Array[start] go into next
			add $14, $0, $4			# minPath = Array[start]

next:		addi $12, $0, 0			# i = 0
		    addi $5, $0, 0			# j = 0
            jr $31



# END ------------------------------>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

end:		add    $4, $0, $14	# store MinCost = minPath
		add $31, $17, $0		# reset $31
		swi     591             # report the answer
		jr	$31		# return to caller