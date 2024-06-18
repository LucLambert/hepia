/*
 * I2C.c
 *
 *  Created on: Mar 19, 2022
 *      Author: luclaptop
 */

#include "LPC17xx.h"
#include "I2C.h"

#define I2C_START 0x8
#define I2C_RESTART 0x10
#define I2C_MASTER_W 0x18
#define I2C_SLAVE_NACK 0x20
#define I2C_SLAVE_ACK_RECEIVE 0x28
#define	I2C_SLAVE_NACK_RECEIVE 0x30
#define I2C_SLAVE_READY_TO_SEND 0x40
#define I2C_SLAVE_NOT_READY_TO_SEND 0x48
#define I2C_MASTER_ACK_RECEIVE 0x50
#define	I2C_MASTER_NACK_RECEIVE 0x58

#define I2C_AA LPC_I2C0->I2CONSET=(1<<2)
#define I2C_SI LPC_I2C0->I2CONSET=(1<<3)
#define I2C_STO LPC_I2C0->I2CONSET=(1<<4)
#define I2C_STA LPC_I2C0->I2CONSET=(1<<5)
#define I2C_I2N LPC_I2C0->I2CONSET=(1<<6)

#define I2C_AAC LPC_I2C0->I2CONCLR=(1<<2)
#define I2C_SIC LPC_I2C0->I2CONCLR=(1<<3)
#define I2C_STAC LPC_I2C0->I2CONCLR=(1<<5)
#define I2C_I2NC LPC_I2C0->I2CONCLR=(1<<6)

extern i2c_transaction_t t;

void I2C0_IRQHandler(void){

	switch(LPC_I2C0->I2STAT){

		case I2C_START:
		case I2C_RESTART:
			if(t.data_write_len > 0)
				LPC_I2C0->I2DAT=((t.slave_addr<<1) &~ 1);
			else
				LPC_I2C0->I2DAT=((t.slave_addr<<1) | 1);
			I2C_STAC;
			break;

		case I2C_MASTER_W:
			if(t.data_read_len>1)
				LPC_I2C0->I2DAT=t.data[t.data_ptr++]|0x80;
			else
				LPC_I2C0->I2DAT=t.data[t.data_ptr++];
			t.data_write_len--;
			break;

		case I2C_SLAVE_NACK:
			t.transaction_done=1;
			I2C_STO;
			break;

		case I2C_SLAVE_ACK_RECEIVE:
			if(t.data_write_len>0){
				LPC_I2C0->I2DAT=t.data[t.data_ptr++];
				t.data_write_len--;
			}else{
				if(t.data_read_len<1){
					t.transaction_done=1;
					I2C_STO;
				}else{
					I2C_STA;
				}
			}
			break;

		case I2C_SLAVE_NACK_RECEIVE:
			t.transaction_done=1;
			I2C_STO;
			break;

		case I2C_SLAVE_READY_TO_SEND:
			if(t.data_read_len<=1)
				I2C_AAC;
			else
				I2C_AA;
			break;

		case I2C_SLAVE_NOT_READY_TO_SEND:
			t.transaction_done=1;
			I2C_STO;
			break;

		case I2C_MASTER_ACK_RECEIVE:
			if(t.data_read_len<=0){
				I2C_AAC;
			}
			else{
				t.data[t.data_ptr++]=LPC_I2C0->I2DAT;
				t.data_read_len--;
			}
			break;

		case I2C_MASTER_NACK_RECEIVE:
			t.transaction_done=1;
			I2C_STO;
			break;
	}
	I2C_SIC;
}

void i2c_config(){
	LPC_SC->PCONP|=(1<<7);

	LPC_SC->PCLKSEL0&=~(0b11<<14);
	LPC_SC->PCLKSEL0|=(0b01<<14);

	LPC_PINCON->PINSEL1&=~((0b11<<22)|(0b11<<24));
	LPC_PINCON->PINSEL1|=((0b01<<22)|(0b01<<24));

	LPC_I2C0->I2SCLH=125;
	LPC_I2C0->I2SCLL=125;

	LPC_I2C0->I2CONCLR=(1<<2)|(1<<3)|(1<<5)|(1<<6);
	NVIC_EnableIRQ(I2C0_IRQn);

	LPC_I2C0->I2CONSET=(1<<6);
}

void i2c_start_transaction(){
	t.data_ptr=0;
	t.transaction_done=0;
	LPC_I2C0->I2CONSET=(1<<5);
	while(!t.transaction_done);
}


