/*
 * sd_card_read.c
 *
 *  Created on: 21 oct. 2020
 *  Author: VP
 */

#include <stdint.h>
#include <stdbool.h>
#include "sdcard.h"

extern int ex;

void sd_enable  (void);
void sd_disable (void);
uint32_t send_sd_command(uint8_t commande, uint32_t argument);
uint8_t wait_sd_free();

uint8_t* tab;
void init_ssp1_dma()
{
	LPC_SSP1->DMACR=3;		// enable DMA transfer for Tx/Rx on SSP1
	LPC_SSP0->DMACR=2;		// enable DMA transfer for Tx on SSP0
	// generic initialization of GPDMA channel 2&3 for SSP1
	/* ... */

	//enable and config  gpdma controller
	LPC_SC->PCONP |= 1<<29; // Power-ON GPDMA
	LPC_GPDMA->DMACConfig = 1; 	// DMA config enable
	NVIC_EnableIRQ(DMA_IRQn); // enable interrupt DMA
}


void dma_cpy_ssp1_to_mem(uint8_t *bytes, uint16_t bytes_len)
{
	LPC_SSP1->DR = 0xFF;		// first Tx trigger before DMA transfer
	while ( (LPC_SSP1->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );

	// start GPDMA channel 2 (Tx) & 3 (Rx) on SSP1 to write memory, TC interrupt configured on channel 3
	/* ... */
	//channel 2
	uint8_t data_transmit = 0xFF;
	LPC_GPDMACH2->DMACCSrcAddr=&data_transmit;//read 0xff from source
	LPC_GPDMACH2->DMACCDestAddr=&LPC_SSP1->DR; //send on ssp1 TX
	LPC_GPDMACH2->DMACCControl=(bytes_len&0x7FF); //len

	//channel 3
	LPC_GPDMACH3->DMACCSrcAddr=&LPC_SSP1->DR; //read from source ssp1 RX
	LPC_GPDMACH3->DMACCDestAddr=bytes; //send to bytes
	LPC_GPDMACH3->DMACCControl=((bytes_len&0x7FF) | (1<<27) | (1<<31)) ; // len  + dest increment + interrupt enable

	//enable channel 2 & 3
	LPC_GPDMACH2->DMACCConfig=((1<<0) | (2<<6) | (1<<11)); // enable + dest SSP TX + memory to periph
	LPC_GPDMACH3->DMACCConfig=((1<<0) | (3<<1) | (2<<11)  | (1<<15)); // enable + src SSP RX + periph to memory + interrupt mask

}

void dma_cpy_ssp1_to_ssp0(uint16_t bytes_len)
{
	LPC_SSP1->DR = 0xFF;		// first Tx trigger before DMA transfer
	while ( (LPC_SSP1->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );

	// start GPDMA channel 2 (Tx) & 3 (Rx) on SSP1 to write on SSP0, TC interrupt configured on channel 3
	/* ... */
	//channel 2
	uint8_t data_transmit = 0xFF;
	LPC_GPDMACH2->DMACCSrcAddr=&data_transmit;//read 0xff from source
	LPC_GPDMACH2->DMACCDestAddr=&LPC_SSP1->DR; //send on ssp1 TX
	LPC_GPDMACH2->DMACCControl=(bytes_len&0x7FF); // len

	//channel 3
	LPC_GPDMACH3->DMACCSrcAddr=&LPC_SSP1->DR; //read from source ssp1 RX
	LPC_GPDMACH3->DMACCDestAddr=&LPC_SSP0->DR; //send to ssp0 TX
	LPC_GPDMACH3->DMACCControl=((bytes_len&0x7FF) | (1<<31)) ; // len + interrupt enable

	//enable channel 2 & 3
	LPC_GPDMACH2->DMACCConfig=((1<<0) | (2<<6) | (1<<11)); // enable + dest SSP TX + memory to periph
	LPC_GPDMACH3->DMACCConfig=((1<<0) | (3<<1) | (3<<11)  | (1<<15)); // enable + src SSP RX + periph to periph + interrupt mask
}


int cpt_transfer=0;
void DMA_IRQHandler()
{
	static uint8_t dummy;

	if (LPC_GPDMA->DMACIntTCStat & (1<<3))		// DMA channel 3 (SSP1 reading)
	{
		LPC_GPDMA->DMACIntTCClear = 1<<3;		// DMA channel 3 int. ack.
		while ( (LPC_SSP1->SR & (SSPSR_BSY|SSPSR_RNE)) != SSPSR_RNE );
		dummy=LPC_SSP1->DR;		// catch up the RX value not read after the first Tx (see dma_read). Discard 1st CRC byte
		ssp_receive(LPC_SSP1);	// 2nd CRC byte to discard

		 if (cpt_transfer == 112)// last block read iteration 112= for image transfer 38=For single block transfer
		{
			wait_sd_free();						// waiting end of read operation
			sd_disable();
			cpt_transfer=0;
		}
		else
		{
			cpt_transfer++;
			while(ssp_receive(LPC_SSP1)!=0xFE);		//  wait "read ready" code 0xFE
			tab+=SDHC_BLOCK_SIZE; //increment pointer tab of size of value transfered
			if (ex==1)
				dma_cpy_ssp1_to_mem(tab, SDHC_BLOCK_SIZE);
			else
				dma_cpy_ssp1_to_ssp0(SDHC_BLOCK_SIZE);
		}
	}
}


uint32_t sd_to_mem(uint64_t sd_address, uint8_t *data_mem, uint32_t length)
{
	uint32_t frame_len;			// max length per frame from SD card
	tab=data_mem;
	if ((length&0x1ff) || (sd_address&0x1ff))
		return ADDR_ERROR;
	sd_enable();
	send_sd_command(23, ((length+511)>>9));		// set block count (normally avoid the use of STOP cmd)
	ssp_receive(LPC_SSP1);

	if (send_sd_command(18, sd_address>>9)!=0)			// read multiple blocks
		return READ_ERROR;

	while(ssp_receive(LPC_SSP1)!=0xFE);

	frame_len=(length>=SDHC_BLOCK_SIZE)?SDHC_BLOCK_SIZE:length;
	dma_cpy_ssp1_to_mem(data_mem, frame_len);		// the next blocks are read from TC interrupt
	/* ... */
	return NO_ERROR;
}

uint32_t sd_to_lcd(uint64_t sd_address, uint32_t length)
{
	uint32_t frame_len;		// max length per frame from SD card

	if ((sd_address&0x1ff) || length==0)
		return ADDR_ERROR;
	sd_enable();
	send_sd_command(23, ((length+511)>>9));		// set block count (normally avoid the use of STOP cmd)
	ssp_receive(LPC_SSP1);

	if (send_sd_command(18, sd_address>>9)!=0)		// read multiple blocks
		return READ_ERROR;

	while(ssp_receive(LPC_SSP1)!=0xFE);			// must be 0xFE

	frame_len=(length>=SDHC_BLOCK_SIZE)?SDHC_BLOCK_SIZE:length;
	dma_cpy_ssp1_to_ssp0(frame_len);			// the next blocks are read from TC interrupt
	/* ... */
	return NO_ERROR;
}
