/*
 * UART.c
 *
 *  Created on: Mar 15, 2022
 *      Author: luclaptop
 */

#include "LPC17xx.h"
#include "UART.h"
#include "circular_buffer.h"

#define DIVISOR_LATCH (1<<7)
#define UART_IER_RBR 1
#define UART_IIR_IID 1
#define UART_INT_ID_RDA 2

static volatile circbuf_struct c_buff;
static volatile uint16_t flag_receive=0;

void UART0_IRQHandler(){
	if(((LPC_UART0->IIR>>UART_IIR_IID) & 0x7)==UART_INT_ID_RDA){
		uint8_t n = (LPC_UART0->RBR&0xff);
		circbuf_put(&c_buff, n);
		flag_receive++;
	}
}

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

	c_buff.ptr_read=0;
	c_buff.ptr_write=0;

	circbuf_clear(&c_buff);
//
//	NVIC_EnableIRQ(UART0_IRQn);
//	LPC_UART0->IER=UART_IER_RBR;

}

void uart_send(uint8_t c){
	while((LPC_UART0->LSR & (1<<6)) == 0);
	LPC_UART0->THR=c;
}

uint8_t uart_receive(){
	while((LPC_UART0->LSR & 1) == 0);
	return LPC_UART0->RBR&0xff;
}

uint16_t uart_receive_msg(uint8_t* buff){
	uint16_t i=0;
	while(flag_receive>0){
		buff[i++]=circbuf_get(&c_buff);
		flag_receive--;
	}
	return i;
}

void uart_receive_size(uint8_t buff[], uint16_t length){
	for(uint16_t i = 0; i<length; i++)
		buff[i]=uart_receive();
}

void uart_send_str(char* data, uint32_t length){
	for(int i=0;i<length;i++){
		uart_send(data[i]);
	}
}
