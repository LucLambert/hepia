/*
 *  sdcard.h
 *
 *  Description: SD card driver. This driver only works with SDHC flash cards. Only blocks
 *               of 512 bytes can be addressed in this preliminary version.
 *               If the DMA functions are used, a callback function must be given to init_sd_card().
 *               In this case, DMA channels 2 and 3 are used on SSP.
 *  Created on: sept. 2020
 *  Author: VP
 */

#ifndef SDCARD_H_
#define SDCARD_H_

#include "LPC17xx.h"
#include "ssp.h"

// error codes:
#define NO_ANSWER   0xFFFFFFFF
#define READ_ERROR  0xFFFFFFFE
#define WRITE_ERROR 0xFFFFFFFD
#define ERASE_ERROR 0xFFFFFFFC
#define ADDR_ERROR  0xFFFFFFFB
#define CALLBACK_ERROR 0xFFFFFFFA
#define NO_ERROR 0

#define SDHC_BLOCK_SIZE	512

/* Description: setup a SSP port, and send initialisation sequence on SD card. If sd_dma_read() or sd_dma_read512()
 *              will be used, a callback must be defined. It will be called at the end of the DMA transfers.
 *              During the initialisation, the clock rate is 400 kHz. Atfer the initialisation, it is 16.6 MHz.
 * Parameters: spi_port: LPC_SSP0 or LPC_SSP1
 *                       callback: callback function called when a DMA transfer is finished
 *                                 NULL otherwise.
 * Return: error code
 */
uint32_t init_sd_card(LPC_SSP_TypeDef *spi_port, ssp_dma_callback_t callback);

// write one single 512 bytes block on SD flash. The given address must be a multiple of 512.
// error returned in case of failure
uint32_t sd_write512(uint64_t sd_address, uint8_t *data);

// read one single 512 bytes block. The given address must be a multiple of 512.
// error returned in case of failure
uint32_t sd_read512(uint64_t sd_address, uint8_t *data);

// read one multiple 512 bytes blocks. The given address and length must be a multiple of 512.
// Calling this function is faster than calling several times sd_read512().
// error returned in case of failure
uint32_t sd_read(uint64_t sd_address, uint8_t *data, uint32_t length);

// read one single 512 bytes block using DMA from SD to memory.
// The given address must be a multiple of 512.
// At the end of the transfer, the callback given in init_sd_card() is called.
// error returned in case of failure
uint32_t sd_dma_read512(uint64_t sd_address, uint8_t *data);

// read multiple 512 bytes blocks using DMA from SD to memory.
// The given address and length must be a multiple of 512.
// At the end of the transfer, the callback given in init_sd_card() is called.
// error returned in case of failure
uint32_t sd_dma_read(uint64_t sd_address, uint8_t *data, uint32_t length);

// read multiple 512 bytes blocks using DMA, directly from SD to the LCD.
// The given address and length must be a multiple of 512.
// At the end of the transfer, the callback given in init_sd_card() is called.
// error returned in case of failure
uint32_t sd_dma_to_lcd(uint64_t sd_address, uint32_t length);

#endif /* SDCARD_H_ */
