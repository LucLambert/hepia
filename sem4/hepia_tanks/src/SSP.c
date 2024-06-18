/*
 * SSP.c
 *
 *  Created on: Mar 1, 2022
 *      Author: luclaptop
 */
#include "LPC17xx.h"

void ssp_config(){
	LPC_SC->PCLKSEL1=1<<10;
	LPC_SSP0->CPSR=10;
	LPC_PINCON->PINSEL1|=(0b10<<2|0b10<<4|0b10);
	LPC_PINCON->PINSEL0|=2<<30;
	LPC_SSP0->CR0=0b0111;
	LPC_SSP0->CR1=1<<1;
}

void ssp_send_char(uint8_t c){
	LPC_SSP0->DR=c;
	while(LPC_SSP0->SR & (1<<4));
}

void ssp_send(char* str, uint32_t length){
	for(uint32_t i=0; i < length; i++){
		ssp_send_char(str[i]);
	}
}








