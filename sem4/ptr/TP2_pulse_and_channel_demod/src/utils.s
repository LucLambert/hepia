#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

.section .text,"ax"
.cpu cortex-m3
.thumb
.syntax unified

.global scalar_prod_int16
.global scalar_prod_int8

/*****************************************************
 * function     : scalar product with int16_t vectors
 * R0: A pointer
 * R1: B pointer
 * R2: arrays size
 * return value : A'*B
 *****************************************************/
.thumb_func
scalar_prod_int16:
    push {r4,r5}
	mov r5, #0		    	// accumulateur
sp_loop:
	ldrsh r3, [r0],#2
	ldrsh r4, [r1],#2
	mla r5, r3, r4, r5		// r5=r3 * r4 + r5
	subs r2, #1				// i--
	bne sp_loop				// if i != 0 loop
	mov r0, r5
	pop {r4,r5}
	bx  lr

/*****************************************************
 * function     : scalar product with int8_t vectors
 * R0: A pointer
 * R1: B pointer
 * R2: arrays size
 * return value : A'*B
 *****************************************************/
.thumb_func
scalar_prod_int8:
	mov r5, #0		    	// accumulateur
sp_loop_u8:
	ldrsb r3, [r0],#1		// (sb=sign extent)
	ldrsb r4, [r1],#1
	mla r5, r3, r4, r5		// r5=r3 * r4 + r5
	subs r2, #1				// i--
	bne sp_loop_u8			// if i != 0 loop
	mov r0, r5
	bx  lr


.ltorg
