/*
 * Description: trace management using UART (and FreeRTOS)
 * Created on : 30 sept. 2013
 * Author     : VP
 */
#ifndef TRACES_REF_H_
#define TRACES_REF_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// definition of the synchronisation word defining the start of each trace
#define SYNCHRO_WORD 0x55

/* Description: initialize UART0 and specified timer for traces. If enabled,
 *              the interrupts occur after each trace sending.
 *              DO NOT CALL send_traces_to_uart0() but only write_trace_ref()
 *              if interrupts are enabled.
 * Parameters: baudrate: valid UART baudrate [bit/s]
 *             timer_id: 0 to 3 to identify the timer used as a free running counter
 *             short_traces: if true, enables TX short traces (only 5 bytes instead of 8). The time tick is 5 us.
 *                           if false, long traces are enabled with a tick of 40 ns. See format description below.
 *             interrupt_enabled: enable UART0 interrupt if true
 */
void init_traces(uint32_t baudrate, int timer_id, bool short_traces, bool interrupt_enabled);

/* Description: store a trace in a memory buffer
 *
 * Parameters: trace_id: trace ID. Usually the task number in FreeRTOS.
 *             val: 1 if task becomes active, 0 otherwise
 */
void write_trace_ref(uint8_t trace_id, short val);

/* Description: if new traces are available, send them to UART.
 *              Polling is used here instead of interrupts */
void send_traces_to_uart0(void);

// trace structure
/* if long traces are enabled, time is a 32 bits field containing the number of time ticks elapsed at 40 ns
 * if short traces enabled, the 'time' field is coded as follows:
 *  - bit 0 gives signal activation (0 or 1),
 *  - bits 5:1 signal ID,
 *  - bits 31:6 time ticks of 5 us
 *  'sig_idx' and 'val' are ignored */
typedef struct {
	uint8_t synchro;
	uint8_t sig_idx;	/* bit 8 indicates other traces than VCD */
	short val;
	uint32_t time;		/* see comment above */
} trace_t;

#endif
