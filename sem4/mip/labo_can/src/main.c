/*
===============================================================================
 Name        : cmsis.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include "CAN.h"
#include "UART.h"
#include <stdio.h>
#include "/home/luclaptop/embedded_linux_lambert/projet/ppm.h"

// TODO: insert other definitions and declarations here

int main(void) {

    // TODO: insert code here
	can_config();
	uint8_t data[8]= {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
	can_msg_t msg;
	msg.id=1;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=8;
	msg.error_msg=3;
	for(int i=0; i<8;i++){
		msg.data[i]=data[i];
	}

	can_send(&msg);
	volatile int i=0;

    while(1) {
    	if(flag_receive==1){
			can_receive(&msg);
			can_send(&msg);
    	}
    	i++;
    }
    return 0 ;
}
