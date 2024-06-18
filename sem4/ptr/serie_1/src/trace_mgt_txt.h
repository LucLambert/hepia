/*
 * trace_mgt.h
 *
 *  Created on: 30 oct. 2013
 *      Author: VP
 */

#ifndef TRACE_MGT_TXT_H_
#define TRACE_MGT_TXT_H_

#include <stdio.h>
#include <stdbool.h>

/* Description: create a text header file in VCD format
 * Parameters:
 *   filename: filename of the file created
 *   init_sig: pointer on an array containing the initial values of the signals
 *   nb_signals: number of signals to be logged
 *   timescale: "1 ms" or "1 us"
 *   unit_ticks: number of timer0 clock ticks in the considered unit (1 ms or 1 us)
 * Return: 0 if no error, -1 otherwise
 */
int create_vcd_header(char *filename, bool *init_sig, int nb_signals, char *timescale, unsigned unit_ticks);

/* Description: close a file opened with create_vcd_header()
 */
void close_trace();

/* Description: add a new trace input in the VCD file opened with create_vcd_header()
 * Parameters:
 *   sig_idx: signal ID of the signal to add
 *   val: value of the curent trace (0 or 1)
 */
void send_trace_to_file(int sig_idx, short val);

#endif /* TRACE_MGT_TXT_H_ */
