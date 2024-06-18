/*
 *  ssp.h
 *
 *  SSP driver. DMA can be used with a callback. Channels 2 and 3 are used.
 *
 *  Created on: sept. 2020
 *  Author: VP
 */

#ifndef SSP_H_
#define SSP_H_

#include "LPC17xx.h"

#define SSPSR_TFE               (1 << 0)
#define SSPSR_TNF               (1 << 1)
#define SSPSR_RNE               (1 << 2)
#define SSPSR_RFF               (1 << 3)
#define SSPSR_BSY               (1 << 4)

#define DMA_SSP_BAD_LENGTH 		-10
#define DMA_SSP_OK				0

typedef void (*ssp_dma_callback_t)(int err_stat);

/* Description: setup a SSP port, possibly using DMA if a callback is defined.
 * Parameters: spi_port: LPC_SSP0 or LPC_SSP1
 *                       data_size_select: nb of bits/word of the transfer (example: 8)
 * 						 scr: fix SSP CLK freq as: 50 MHz / (scr+1)
 *                       callback: callback function called when a DMA transfer is finished
 *                                 NULL otherwise.
 */
void ssp_init(LPC_SSP_TypeDef *spi_port, uint8_t data_size_select, uint8_t scr, ssp_dma_callback_t callback);


// standard TX/RX functions with polling (no DMA)
void ssp_send_buf(LPC_SSP_TypeDef *spi_port, uint8_t *buf, uint32_t length);
void ssp_receive_buf(LPC_SSP_TypeDef *spi_port, uint8_t *buf, uint32_t length);
uint8_t ssp_receive(LPC_SSP_TypeDef *spi_port);

// DMA transfer: "callback" is called when the transfer ends
int ssp_DMA_rx(LPC_SSP_TypeDef *spi_port, uint8_t *bytes, uint16_t bytes_len);

#endif /* SSP_H_ */
