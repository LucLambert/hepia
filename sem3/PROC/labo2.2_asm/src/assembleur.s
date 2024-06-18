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
.global majuscule

/*****************************************************
 * function     : exercice1
 * R0: A pointer
 * R1: B pointer
 * return value : *A + *B
 *****************************************************/
.thumb_func
funcexo1:
	ldr r0, [r0]
	ldr r1, [r1]
	adds r0, r0, r1
	bcc exit
	mov r0, #0
exit:
	bx  lr


/*****************************************************
 * function     : exercice2
 * R0: A pointer
 * R1: B pointer
 * R2: arrays size
 * return value : B[]=2*A[]
 *****************************************************/
.thumb_func
funcexo2:
loop:
	ldr r3, [R0], #4
	adds r4, r3, r3
	str r4, [r1], #4
	bcs error
	subs r2, r2, #1
	beq ex
	b loop
error:
	mov r0, #0
ex:
	bx  lr


.thumb_func
majuscule:
	ldrb r2, [r0] //r2 = chaine[0]
	cmp r2, #0
	beq end
while:
	ldrb r2, [r0]
	cmp r2, #97
	blo end
	cmp r2, #122
	bhi end
	sub r2, r2, #32
end:
	strb r2, [r0], #1
	cmp r2, #0
	bne while
	bx lr


//.weak add_sat
.ltorg
