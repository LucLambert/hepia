/*
 * circ_buff.c
 *
 *  Created on: Mar 15, 2022
 *      Author: luclaptop
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "circ_buff.h"


void push(circ_buff_t* c, trace_t val){
	c->buff[c->write++%c->size]=val;
}

trace_t pop(circ_buff_t* c){
	return c->buff[c->read++%c->size];
}

void clear(circ_buff_t* c){
	c->read=0;
	c->write=0;
}

