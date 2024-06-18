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
void fault_next_instruction();

uint32_t* MMFAR = (uint32_t*)0xE000ED34;
uint32_t tab[10];
int index=0;

void MemManage_Handler()
{
	tab[index++]=*MMFAR; //store address wich make error
	SCB->CFSR=0xFFFFFFFF; //acquittement interrupt
	LPC_GPIO2->FIOPIN=index;
	fault_next_instruction();
	//asm("pop {r7}"); // because handler push{r7} // crash if this line is present work if not
}

int *p_sram2=(int *)0x2007c000, a;
int i;

int main(void)
{
	LPC_GPIO2->FIODIR=0xFF;		// active leds
	// configurer la MPU ici ...

	//flash
	//choose region
	MPU->RBAR=0|(1<<4); //address/region0  + valid
	//choose rights
	MPU->RASR=1|(18<<1)|(1<<19)|(7<<24);//enable + size + non-shareable normal + read only

	//SRAM1
	//choose region
	MPU->RBAR=0x10000000|1|(1<<4); //address  + region + valid
	//choose rights
	MPU->RASR=1|(14<<1)|(1<<19)|(3<<24);//enable + size + non-shareable normal + read write

	//SRAM2
	//choose region
	MPU->RBAR=0x2007C000|2|(1<<4); //address  + region + valid
	//choose rights
	MPU->RASR=1|(14<<1)|(1<<19)|(2<<24);//enable + size + non-shareable normal + read write / read only for unpriviligied

	//GPIO
	//choose region
	MPU->RBAR=0x2009C000|3|(1<<4); //address  + region + valid
	//choose rights
	MPU->RASR=1|(13<<1)|(2<<19)|(2<<24);//enable + size + non-shareable device + read write / read only for unpriviligied

	// enable memory exception
	SCB->SHCSR |= (1<<16);
	//enable mpu
	MPU->CTRL=1;


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
