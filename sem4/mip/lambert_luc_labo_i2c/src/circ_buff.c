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


void circ_buff_push(circ_buff_t* c, uint8_t val){
	c->buff[c->write++%BUFSIZE]=val;
}

uint8_t circ_buff_pop(circ_buff_t* c){
	return c->buff[c->read++%BUFSIZE];
}

uint16_t circ_buff_count(circ_buff_t* c){
	return c->write-c->read;
}

void circ_buff_clear(circ_buff_t* c){
	c->read=0;
	c->write=0;
}

