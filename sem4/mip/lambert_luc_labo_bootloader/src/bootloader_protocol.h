/*
 * bootloader_protocol.h
 *
 *  Created on: May 5, 2022
 *      Author: luclaptop
 */

#ifndef BOOTLOADER_PROTOCOL_H_
#define BOOTLOADER_PROTOCOL_H_
	#include <stdint.h>
	#include <string.h>
	#include <stdio.h>
	#include "UART.h"

	typedef struct{
		char cmd[10];
		int arg[256];
		uint16_t size;
	}cmd_t;

	void parse_cmd(cmd_t* c);
	uint8_t is_GETID(char cmd[]);
	uint8_t is_GETSERIAL(char cmd[]);
	uint8_t is_DATA(char cmd[]);
	uint8_t is_PROG(char cmd[]);
	uint8_t is_CHECK(char cmd[]);
	void send_OK();
	void send_ERR(char type_error);

#endif /* BOOTLOADER_PROTOCOL_H_ */
