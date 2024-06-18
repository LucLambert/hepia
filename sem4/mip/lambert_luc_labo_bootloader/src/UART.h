/*
 * UART.h
 *
 *  Created on: Mar 15, 2022
 *      Author: luclaptop
 */

#ifndef UART_H_
#define UART_H_

	#define PARITY_EVEN	(1<<3) | (1<<4)
	#define PARITY_ODD (1<<3)
	#define PARITY_DISABLE 0

	#define WORD_LENGTH_5 0b00
	#define WORD_LENGTH_6 0b01
	#define WORD_LENGTH_7 0b10
	#define WORD_LENGTH_8 0b11

	#define STOP_BIT_1 0
	#define STOP_BIT_2 (1<<2)

	void uart_config(uint32_t baudrate, uint8_t word_length, uint8_t parity, uint8_t stop_bit);
	void uart_send(uint8_t c);
	uint8_t uart_receive();
	uint16_t uart_receive_msg(uint8_t buff[]);
//	void uart_read_buff(uint8_t* buff, uint16_t length);
	void uart_receive_size(uint8_t buff[], uint16_t length);
	void uart_send_str(char* data, uint32_t length);

#endif


