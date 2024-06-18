/*
 * circ_buff.h
 *
 *  Created on: Mar 15, 2022
 *      Author: luclaptop
 */

#ifndef CIRC_BUFF_H_
#define CIRC_BUFF_H_

#define BUFSIZE	512

	typedef struct circ_buff{
		uint8_t buff[BUFSIZE];
		uint32_t read;
		uint32_t write;
		uint32_t size;
	}circ_buff_t;

	void circ_buff_push(circ_buff_t* c, uint8_t val);
	uint8_t circ_buff_pop(circ_buff_t* c);
	uint16_t circ_buff_count(circ_buff_t* c);
	void  circ_buff_clear(circ_buff_t* c);

#endif /* CIRC_BUFF_H_ */
