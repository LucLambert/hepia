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


/*****************************************************
 * function     : exercice1
 * R0: a
 * R1: b
 * R2: c
 * R3: d
 * SP: &e
 * return value : *e = a XOR b XOR c XOR d
 *****************************************************/
.thumb_func
funcexo1:
	eor r0, r1
	eor r0, r2
	eor r0, r3
	ldr r1, [sp]
	str r0, [r1]
	bx  lr

/*****************************************************
 * 32 bits (unsigned) multiplication with overflow detection
 * r0: multiplicand
 * r1: multiplier
 * return values :
 * r0 = r0 * r1, r1=1 if 32 bits overflow (0 otherwise)
 *****************************************************/
.thumb_func
mult32:
	umull r0,r1,r0,r1
	cmp   r1,#0
	it    ne
	movne r1,#1				// add carry to r1
	bx    lr

/*****************************************************
 * function     : exercice 2
 * R0: a
 * R1: b
 * R2: c
 * R3: d
 * return value : a*b+c*d or 0 if overflow
 *****************************************************/
.thumb_func
funcexo2:
	push {lr}
	bl mult32
	cmp r1, #1
	push {r0}
	beq exit2
	mov r0, r2
	mov r1, r3
	bl mult32
	cmp r1, #1
	beq exit2
	mov r2, r0
	pop {r0}
	adds r0, r2, r0
	bcs exit3
	b exit4

exit2:
	pop {r0}

exit3:
	mov r0, #0
	mov r1, #1

exit4:
	pop {lr}
	bx lr
	
	
/*****************************************************
 * function     : exercice 3
 * R0: a
 * R1: b and c (c in high 16 bits)
 * R2: d
 * R3: e
 * return value : addition of the elements of the structure
 *****************************************************/
.thumb_func
funcexo3:
	lsr r4, r1, #16 //c=-1
	//and r1, #15 //b sur 8 bits
	sxth r4, r4
	and r2, #255
	sxtb r2, r2
	sxtb r1, r1
	add r0, r1
	add r0, r4
	add r0, r2
	add r0, r3
	bx    lr

//.weak add_sat
.ltorg
