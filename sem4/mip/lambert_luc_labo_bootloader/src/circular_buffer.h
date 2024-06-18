/*****************************************************************************
 *   circular_buffer.h:  Header file for a simple circular buffer
 *
 *   Christian Abegg, HEPIA
******************************************************************************/

#ifndef __CIRCULAR_BUFFER_H
#define __CIRCULAR_BUFFER_H

#include <stdint.h>

#define BUFSIZE	1024

typedef struct {
	uint8_t data[BUFSIZE];
	uint16_t ptr_write;
	uint16_t ptr_read;
} circbuf_struct;

void circbuf_put(volatile circbuf_struct *buf, uint8_t elem);

uint8_t circbuf_get(volatile circbuf_struct *buf);

void circbuf_clear(volatile circbuf_struct *buf);

#endif /* end __CIRCULAR_BUFFER_H  */
