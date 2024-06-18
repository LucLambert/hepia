/*
 * I2C.c
 *
 *  Created on: Mar 19, 2022
 *      Author: luclaptop
 */
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

#define I2C_AA (1<<2)
#define I2C_SI (1<<3)
#define I2C_STO (1<<4)
#define I2C_STA (1<<5)
#define I2C_I2N (1<<6)

static i2c_transaction_t t;

void I2C0_IRQHandler(void){

	switch(LPC_I2C0->I2STAT){

		case I2C_START:
		case I2C_RESTART:
			if(t.data_write_len > 0)
				LPC_I2C0->I2DAT=((t.slave_addr<<1) &~ 1);
			else
				LPC_I2C0->I2DAT=((t.slave_addr<<1) | 1);
			t.data_ptr=0;
			LPC_I2C0->I2CONCLR=I2C_STA;
			break;

		case I2C_MASTER_W:
			if(t.data_read_len>1)
				LPC_I2C0->I2DAT=(t.data[t.data_ptr++]|0x80);
			else
				LPC_I2C0->I2DAT=t.data[t.data_ptr++];
			t.data_write_len--;
			break;

		case I2C_SLAVE_NACK:
			t.transaction_done=1;
			LPC_I2C0->I2CONSET=I2C_STO;
			break;

		case I2C_SLAVE_ACK_RECEIVE:
			if(t.data_write_len>0){
				LPC_I2C0->I2DAT=t.data[t.data_ptr++];
				t.data_write_len--;
			}else{
				t.data_ptr=0;
				if(t.data_read_len<1){
					t.transaction_done=1;
					LPC_I2C0->I2CONSET=I2C_STO;
				}else{
					LPC_I2C0->I2CONSET=I2C_STA;
				}
			}
			break;

		case I2C_SLAVE_NACK_RECEIVE:
			t.transaction_done=1;
			LPC_I2C0->I2CONSET=I2C_STO;
			break;

		case I2C_SLAVE_READY_TO_SEND:
			if(t.data_read_len<=1)
				LPC_I2C0->I2CONCLR=I2C_AA;
			else
				LPC_I2C0->I2CONSET=I2C_AA;
			break;

		case I2C_SLAVE_NOT_READY_TO_SEND:
			t.transaction_done=1;
			LPC_I2C0->I2CONSET=I2C_STO;
			break;

		case I2C_MASTER_ACK_RECEIVE:
			if(t.data_read_len<=0){
				LPC_I2C0->I2CONCLR=I2C_AA;
			}
			else{
				t.data[t.data_ptr++]=LPC_I2C0->I2DAT;
				t.data_read_len--;
			}
			break;

		case I2C_MASTER_NACK_RECEIVE:
			if(t.data_read_len==1){
				t.data[t.data_ptr++]=LPC_I2C0->I2DAT;
				t.data_read_len--;
			}
			t.transaction_done=1;
			LPC_I2C0->I2CONSET=I2C_STO;
			break;
	}
	LPC_I2C0->I2CONCLR=I2C_SI;
}

void i2c_config(){
	LPC_SC->PCONP|=(1<<7);

	LPC_SC->PCLKSEL0&=~(0b11<<14);
	LPC_SC->PCLKSEL0|=(0b01<<14);

	LPC_PINCON->PINSEL1&=~((0b11<<22)|(0b11<<24));
	LPC_PINCON->PINSEL1|=((0b01<<22)|(0b01<<24));

	LPC_I2C0->I2SCLH=125;
	LPC_I2C0->I2SCLL=125;

	LPC_I2C0->I2CONCLR=I2C_AA|I2C_SI|I2C_STA|I2C_I2N;
	NVIC_EnableIRQ(I2C0_IRQn);

	LPC_I2C0->I2CONSET=I2C_I2N;
}

void i2c_start_transaction(){
	t.data_ptr=0;
	t.transaction_done=0;
	LPC_I2C0->I2CONSET=I2C_STA;
	while(!t.transaction_done);
}

void i2c_write_register(uint8_t slave_addr, uint8_t reg_addr, uint8_t data){
	t.slave_addr=slave_addr;
	t.data[0]=reg_addr;
	t.data[1]=data;
	t.data_read_len=0;
	t.data_write_len=2;

	i2c_start_transaction();
}

void i2c_read_registers(uint8_t slave_addr, uint8_t reg_addr, uint8_t data[], uint8_t length){
	t.slave_addr=slave_addr;
	t.data[0]=reg_addr;
	t.data_read_len=length;
	t.data_write_len=1;

	i2c_start_transaction();

	for(int i=0; i<length;i++){
		data[i]=t.data[i];
	}
}


