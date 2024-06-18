/*
 * circular_buffer.c
 *
 *  Created on: May 5, 2022
 *      Author: luclaptop
 */

#include "circular_buffer.h"

void circbuf_put(volatile circbuf_struct *buf, uint8_t elem){
	buf->data[buf->ptr_write]=elem;
	buf->ptr_write=(buf->ptr_write+1)%BUFSIZE;
}

uint8_t circbuf_get(volatile circbuf_struct *buf){
	uint8_t v = buf->data[buf->ptr_read];
	buf->ptr_read=(buf->ptr_read+1)%BUFSIZE;
	return v;
}

void circbuf_clear(volatile circbuf_struct *buf){
	buf->ptr_read=buf->ptr_write;
}
