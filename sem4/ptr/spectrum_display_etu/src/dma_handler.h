/*
 * dma_handler.h
 *
 *  Description: This header MUST be included only ONCE in the main of a project using DMA transfers, with
 *               one of the following modules:
 *               - SSP (ssp.h, sdcard.h)
 *               - ADC (adc.h)
 *               The reason of this "scheming" is that DMA_IRQHandler() is declared as __weak and must be
 *               overloaded somewhere in the code but NOT in a library (where it is ignored!).
 *
 *  Created on: 8 sept. 2020
 *  Author: VP
 */

#ifndef DMA_HANDLER_H_
#define DMA_HANDLER_H_

void mylab_DMA_IRQHandler();

// this code must be unique (=included only once in a project)
void DMA_IRQHandler(void)
{
	mylab_DMA_IRQHandler();
}

#endif /* DMA_HANDLER_H_ */
