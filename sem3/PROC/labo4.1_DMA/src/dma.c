/****************************************************************************
 DMA driver
****************************************************************************/

#include "config_LPC1769.h"
#include "dma.h"

/* to be incremented when terminal count reached */
volatile uint32_t DMATCCount = 0;
/* to be incremented if an error occurred during transfer */
volatile uint32_t DMAErrCount = 0;

/******************************************************************************
* Descriptions:		DMA interrupt handler
******************************************************************************/
void DMA_IRQHandler (void) 
{
	/*...*/
	DMACINTTCCLR = (1 << 0); /*clear interrupt*/
	DMACINTERRCLR = (1 << 0); /*clear interrupt*/
	DMATCCount++;
}


/******************************************************************************
* Function name:  DMA_Init
*
* Description:	initialise DMA 0 channel for 32 bits access with increment on
*               source and destination addresses
*
* parameters:
*   src: source address
*   dest: destination address
*   len: number of words to transfer
*   LLI: pointer on LLI structure if used or 0
*
******************************************************************************/
void DMA_Init(uint32_t *src, uint32_t *dest, uint32_t len, uint32_t LLI)
{
  PCONP |= (1 << 29);	/* Enable GPDMA clock */

  DMACINTTCCLR = (1 << 0); /*clear interrupt*/
  DMACINTERRCLR = (1 << 0); /*clear interrupt*/
  ISER0=(1<<26);


  DMACC0SRCADDR = src;
  DMACC0DESTADDR = dest;

  DMACC0LLI = (LLI<<2); /* last block of linked list dma */

  DMACC0CONTROL = (DMA_CFG|len);/*set len */
  DMACCONFIG = (1<<0);/*set little endian*/

  DMACC0CONFIG = ((1<<0)|(1<<15)); /* Enable DMACC0config and set mask interrupt to 1*/
  /*...*/
}
