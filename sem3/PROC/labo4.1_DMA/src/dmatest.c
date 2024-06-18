/****************************************************************************
 Single DMA tzransfert and DMA with LLI transfer
****************************************************************************/
#include <string.h>
#include <stdint.h>
#include "dma.h"
#include "config_LPC1769.h"

extern volatile uint32_t DMATCCount;

GPDMALLI_t LLI[2];
uint32_t src3[DMA_SIZE/16], i;
uint32_t src1[DMA_SIZE/4], dest[DMA_SIZE/4];
uint32_t src2[DMA_SIZE/16];
uint32_t start, time_elapsed;

// copy 1 source buffers in 1 destination buffer with DMA
void single_copy()
{
	start=T0TC;
	for (i = 0; i < DMA_SIZE/4; i++)
	{
	  src1[i] = i;
	  dest[i] = 0;   // clear destination vector
	}
	time_elapsed=(T0TC-start)/25;
	start=T0TC;
	DMA_Init(src1, dest, DMA_SIZE/4, 0);
	time_elapsed=(T0TC-start)/25;

    while (!DMATCCount);		/* Wait until DMA is done */
}

// copy 3 source buffers in 1 destination buffer with DMA linked lists
void LLI_copy()
{
	DMATCCount = 0;
	for (i = 0; i < DMA_SIZE/8; i++)
	{
		src1[i] = i;
		dest[i] = dest[i+DMA_SIZE/8] = 0;   // clear destination vector
	}
	for (i = 0; i < DMA_SIZE/16; i++)
	{
		src2[i] = i + DMA_SIZE/8;
		src3[i] = i + DMA_SIZE/8 + DMA_SIZE/16;
	}

	/*...*/

	DMA_Init(src1, dest, DMA_SIZE/8, (uint32_t)&LLI[0]);

	while (DMATCCount < 3);		/* Wait until DMA is done (3 interrupts here) */
}

/* Verify copy result */
int check_res()
{
	int i;

	for (i = 0; i < DMA_SIZE/4; i++)
	{
		if (dest[i]!=i)
		{
			return 1;	// error
		}
	}
	return 0;
}


int main (void)
{
	init();
    T0TC = 0;
    T0TCR = (1<<0); // counter enable


	memset(LLI, 0, sizeof(GPDMALLI_t)*2);

	single_copy();
	if (check_res())
		while(1);		// error
	LLI_copy();
	if (check_res())
		while(1);		// error

	while (1);	/* Done here, never exit from main for easier debugging. */
}

