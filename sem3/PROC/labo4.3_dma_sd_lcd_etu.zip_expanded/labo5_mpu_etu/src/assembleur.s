.section .text,"ax"
.cpu cortex-m3
.thumb
.syntax unified

.global asm_test_fault
.global fault_next_instruction

/***************************************************************
 * function: test the size of the instruction
 *           pointed by the PC value (on stack). It is a 32 bits
 *           instr. if bits 15:13 are 111 and 12:11 !=0.
 *           Otherwise the instr. size is 16 bits.
 *           The PC is then incremented to be positionned
 *           to the next instruction and written back to the stack
 *           at the right position.
 ***************************************************************/
.thumb_func
fault_next_instruction:

    bx  lr


.equ bad_addr,0x90000

.thumb_func
asm_test_fault:
	ldr r0,=bad_addr
	ldr r1,[r0]				// mem access error
	mov r2,#2
	mov r3,#3
	nop
	bx  lr

//.weak add_sat
.ltorg
