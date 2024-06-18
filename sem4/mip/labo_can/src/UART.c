/*
 * UART.c
 *
 *  Created on: Mar 15, 2022
 *      Author: luclaptop
 */

#include "LPC17xx.h"
#include "UART.h"

#define DIVISOR_LATCH (1<<7)

void uart_config(uint32_t baudrate, uint8_t word_length, uint8_t parity, uint8_t stop_bit){
	LPC_SC->PCLKSEL0&=~(0b11<<6);
	LPC_SC->PCLKSEL0|=(1<<6); // sel clk uart0 100MHZ

	LPC_UART0->LCR=word_length|parity|stop_bit|DIVISOR_LATCH;

	uint16_t dl = 100000000/(baudrate*16);
	LPC_UART0->DLM=dl>>8;
	LPC_UART0->DLL=dl&0xff;
	LPC_UART0->FCR=7;

	LPC_PINCON->PINSEL0&=~((0b11<<4)|(0b11<<6));
	LPC_PINCON->PINSEL0|=(0b01<<4)|(0b01<<6);

	LPC_UART0->LCR=word_length|parity|stop_bit;
}

void uart_send(uint8_t c){
	while((LPC_UART0->LSR & (1<<5)) == 0);
	LPC_UART0->THR=c;
}

uint8_t uart_receive(){
	while((LPC_UART0->LSR & 1) == 0);
	return LPC_UART0->RBR&0xff;
}

void uart_send_str(char* data, uint32_t length){
	for(int i=0;i<length;i++){
		uart_send(data[i]);
	}
}
