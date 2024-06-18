/*
 * CAN.h
 *
 *  Created on: Mar 31, 2022
 *      Author: luclaptop
 */

#ifndef CAN_H_
#define CAN_H_

#include <stdint.h>

extern volatile int flag_receive;

typedef struct can_msg{
	uint32_t id;
	uint8_t rtr;
	uint8_t type; /* Ext/Std frame */
	uint8_t dlc;
	uint8_t error_msg;
	uint8_t data[8];
}can_msg_t;

void can_config();
void can_send(can_msg_t* msg);
void can_receive(can_msg_t* msg);

#endif /* CAN_H_ */
