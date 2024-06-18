/*
 * adc.h
 *
 *  ADC control with or without DMA. A callback is available if DMA used.
 *  DMA channel 1 is used.
 *
 *  WARNING: please add #include "dma_handler.h" ONLY ONCE somewhere in your code
 *           to use DMA features. This way a the unique ISR for DMA will be declared
 *           by Mylab library and be usable.
 *
 *  Created on: Mar 26, 2014
 *  Author: V. Pilloux
 */
#ifndef __ADC_H 
#define __ADC_H

#include <stdint.h>

#define ADC_OFFSET          0x10
#define ADC_INDEX           4

#define ADC_DONE            0x80000000
#define ADC_OVERRUN         0x40000000
#define ADC_ADINT           0x00010000

#define ADC_NUM				1			// for LPCxxxx
#define ADC_CLK				1000000		// set to 1Mhz


/* Prototype of callback function called when one of both reception buffers
 * are filled.
 * Parameter: buffer_index: index of the buffer just filled
 */
typedef void (*func_t)(int buffer_index) ;


/* Description: Create a double buffer (size of 2*single_buf_length) to store data provided by ADC 0, 1, 2 or 3.
 * On Mylab2, ADC0 is connected to the microphone, ADC1 and 2 on left and right wires of the audio input.
 * The sampling frequency is specified in freq_hz. NOTE that the timer 1 is used to impose this sampling
 * frequency. The specified ADC is then read with GPDMA channel 1 until one of both buffer is filled.
 * If the callback function (func) is be specified, this function will be called each time a buffer has
 * been filled by the DMA. The parameter buffer_index is the index of the buffer filled.
 *
 * NOTES:
 * - the buffer should be allocated in RAM2 to allow the use of WFI and DMA (otherwise the DMA can
 *   fail copying data)
 *  - Note: Bluetooth chip is reset to avoid noise generated on power supply on Mylab2 2020!
 *
 * Parameters:
 *   adc_idx: ADC index to be used (and read by the DMA)
 *   freq_hz: sampling frequency
 *   buffer: pointer on the allocated buffer which size is 2*single_buf_length
 *   single_buf_length: single buffer size (max: 4095)
 *   func: callback function called after a buffer completion or NULL if not used
  */
void init_adc_dma(int adc_idx, uint32_t freq_hz, uint16_t *buffer, int16_t single_buf_length, func_t func);

/* Description: initialise an ADC
 * Note: Bluetooth chip is reset to avoid noise generated on power supply on Mylab2 2020!
 * Parameter: adc_idx: ADC index (0 to 7)
 */
void adc_init(int adc_idx);

/* Description: read a value on an ADC
 * Parameter: adc_idx: ADC index (0 to 7)
 */
short adc_read(int adc_idx);


#endif /* end __ADC_H */
