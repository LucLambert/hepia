/*
 * exercice4.c
 *
 *  Created on: Mar 2, 2022
 *      Author: luclaptop
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>
#include <stdlib.h>
#include "adc.h"
#include "ethernet.h"



short read(){
	while(LPC_ADC->ADDR0 & 1<<31 != 1<<31);
	LPC_ADC->ADCR|=(1<<24);
	return LPC_ADC->ADDR0>>4 & 0x00000FFF;
}

TIMER0_IRQHandler(void){
	LPC_TIM0->IR=1;
	LPC_DAC->DACR=(read() & 0xFFC) <<4;
}

int main(void)
{
	ethernet_power_down();
	adc_init(0);
	LPC_PINCON->PINSEL1 |= 0x00200000;

	LPC_TIM0->MR0=568;
	LPC_TIM0->MCR|=3;
	LPC_TIM0->TCR=1;

	while(1){}
	return 0 ;
}
