/*
 * CAN.c
 *
 *  Created on: Mar 31, 2022
 *      Author: luclaptop
 */
#include "CAN.h"
#include "LPC17xx.h"

volatile int can_flag_receive;

void CAN_IRQHandler(void){
	uint32_t interrupt=LPC_CAN1->ICR;
	LPC_CAN1->CMR=(1<<2);
	if(interrupt & 1)
		can_flag_receive=1;
}


void can_config(){
	LPC_SC->PCONP|=(1<<13); //power CAN1

	LPC_SC->PCLKSEL0&=~(0b11<<26); // set clock to 25Mhz

	LPC_SC->CLKSRCSEL=1; //select clcsrc 100Mhz

	LPC_PINCON->PINSEL1|=((0b11<<10)|(0b11<<12)); // sel pin can

	LPC_CAN1->BTR=(4|(13<<16)|(4<<20)); //Config tq

	LPC_CAN1->IER=1;
	volatile uint32_t interrupt=LPC_CAN1->ICR;
	LPC_CAN1->CMR=(1<<2);
	NVIC_EnableIRQ(CAN_IRQn);
	LPC_CANAF->AFMR=(1<<1);

	LPC_CAN1->MOD&=~1; // enable can
}


void can_send(can_msg_t* msg){
	LPC_CAN1->TFI1=(((msg->dlc&0b1111)<<16)|(msg->rtr<<30)|(msg->type<<31));
	LPC_CAN1->TID1=msg->id;
	LPC_CAN1->TDA1=(msg->data[0]|msg->data[1]<<8|msg->data[2]<<16|msg->data[3]<<24);
	LPC_CAN1->TDB1=(msg->data[4]|msg->data[5]<<8|msg->data[6]<<16|msg->data[7]<<24);
	LPC_CAN1->CMR=1;
	LPC_CAN1->CMR=(1<<2);
}

void can_receive(can_msg_t* msg){
	uint32_t buffRFS=LPC_CAN1->RFS;
	uint8_t dlc=(buffRFS & (0b1111<<16))>>16;
	uint8_t type=(buffRFS & (1<<31))>>31;
	uint32_t buffA=LPC_CAN1->RDA;
	uint32_t buffB=LPC_CAN1->RDB;
	uint32_t buffRID=LPC_CAN1->RID;

	msg->dlc=dlc;
	msg->id=buffRID;
	msg->type=type;

	for(int i=0;i<dlc;i++){
		if(i<4){
			msg->data[i]=((buffA&(0xff<<(8*i)))>>(8*i));
		}else{
			msg->data[i]=((buffB&(0xff<<(8*(i-4))))>>(8*(i-4)));
		}
	}
	can_flag_receive=0;
	LPC_CAN1->CMR=(1<<2);
}
