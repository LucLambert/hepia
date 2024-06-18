/*
 * sd_card_read.h
 *
 *  Created on: 21 oct. 2020
 *  Author: VP
 */

#ifndef SD_CARD_READ_H_
#define SD_CARD_READ_H_

// generic initialization of DMA for SSP1 "reading", common to both functions below.
void init_ssp1_dma();

// Copy data from SD to memory.
// DMA channel 2 is used to
// transmit "dummy" data and channel 3 copies data from SSP1 to memory.
uint32_t sd_to_mem(uint64_t sd_address, uint8_t *data_mem, uint32_t length);

// Copy data from SD to LCD.
// DMA channel 2 is used to
// transmit "dummy" data and channel 3 copies data from SSP1 to LCD.
uint32_t sd_to_lcd(uint64_t sd_address, uint32_t length);

#endif /* SD_CARD_READ_H_ */
