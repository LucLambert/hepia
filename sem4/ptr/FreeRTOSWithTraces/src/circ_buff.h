/*
 * circ_buff.h
 *
 *  Created on: Mar 15, 2022
 *      Author: luclaptop
 */

#ifndef CIRC_BUFF_H_
#define CIRC_BUFF_H_

	typedef struct {
		uint8_t synchro; /* always set to 0x55 */
		uint8_t trace_id; /* bit 8 indicates other traces than VCD */
		short value;
		uint32_t time;
	} trace_t;

	typedef struct circ_buff{
		trace_t* buff;
		uint32_t read;
		uint32_t write;
		uint32_t size;
	}circ_buff_t;

	void push(circ_buff_t* c, trace_t val);
	trace_t pop(circ_buff_t* c);
	void clear(circ_buff_t* c);

#endif /* CIRC_BUFF_H_ */
