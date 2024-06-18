#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

.section .text,"ax"
.cpu cortex-m3
.thumb
.syntax unified

.global funcexo1
.global funcexo2
.global funcexo3
.global funcexo4

/*****************************************************
 * function     : exercice1
 * arguments    : unsigned integer number: register R0
                : unsigned integer number: register R1
 * return value : unsigned integer result: register R0
 *   Code for the first exercise
 *****************************************************/
.thumb_func
funcexo1:
	subs r2, r0, r1
	bhi  funcexo1_next
	sub  r2, r1, r0
funcexo1_next:
    mov     r0, r2

	mov	pc, r14		/* end of subroutine */
/*****************************************************
 EN C
 if (a > b)
 		return a-b;
 	return b-a;
 *****************************************************/


/*****************************************************
 * function     : exercice2
 * arguments    : unsigned integer number: register R0
 * return value : unsigned integer result: register R0
 *   Code for the second exercise
 *****************************************************/
.thumb_func
funcexo2:
	mov	  r1, #0
	mov	  r2, #1
funcexo2_loop:
	add   r1, r1, r2
	add   r2, r2, #1
	subs  r3, r0, r1
	bpl   funcexo2_loop
	mov   r0, r1

	mov	pc, r14		/* end of subroutine */



/*****************************************************
 * function     : exercice3 - Fibonacci
 * arguments    : unsigned integer number: register R0
 * return value : unsigned integer number: register R0
 *   Code for the third exercise
 *****************************************************/
.thumb_func
funcexo3:

	// insert your code here
	mov r1, #2
	mov r2, #1
	mov r3, #0
funcexo3_loop:
	add r1, r1, r2
	sub r2, r1, r2
	add r3, r3, #1
	cmp r3, r0
	blt funcexo3_loop
	mov r0, r1
	mov	pc, r14		/* end of subroutine */


/*****************************************************
 * function     : exercice4
 * arguments    : long long: register R1,R0
                : unsigned integer: register R2
 * return value : long long: register R1,R0
 *   Code for the fourth exercise
 *****************************************************/
.thumb_func
funcexo4:

	// insert your code here
	cmp r2, #0
	beq l1
	cmp r2, #1
	beq l2
	mov R1, R0
l1:
	lsls r1, r1, #1
	lsl r0, r0, #1
	adc r0, r0, #0 //add carry r0 = r0 + 0 + c
	b l3
l2:
	lsrs r1, r1, #1
	rrx r0, r0

l3:
	mov	pc, r14		/* end of subroutine */


.weak funcexo1, funcexo2, funcexo3, funcexo4
.ltorg
