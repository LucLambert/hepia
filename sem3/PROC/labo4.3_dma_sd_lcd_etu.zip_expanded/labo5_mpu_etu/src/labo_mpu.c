/*
===============================================================================
 Name        : test_mpu.c
 Author      : VP
 Date        : 15.5.2020
 Description : template of MPU lab
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>


#define SET_USER_MODE() __asm volatile ("	mov r0, #1\n msr	control, r0\n")

void asm_test_fault();

void MemManage_Handler()
{

}

int *p_sram2=(int *)0x2007c000, a;
int i;


int main(void)
{
	LPC_GPIO2->FIODIR=0xFF;		// active leds

	// configurer la MPU ici ...

	a=*p_sram2;					// OK
	*p_sram2=5;					// OK (write in privileged mode)
	LPC_GPIO2->FIOPIN=0xaa;		// OK
	asm_test_fault();			// not OK (out of regions mem. access)

	// switch to unprivileged mode: warning: MPU can't be accessed in this mode!!

	SET_USER_MODE();
	LPC_GPIO2->FIOPIN=0xaa;		// not OK (read only)
	a=LPC_GPIO2->FIOPIN;		// OK
	a=*p_sram2;					// OK (unprivileged read only)
	i=30;
	*p_sram2=5;					// not OK (privileged only for writing)

	i=20;


    while(1);

    return 0;
}
