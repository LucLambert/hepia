/****************************************************************************
 DMA constants definition
****************************************************************************/
#ifndef __DMA_H 
#define __DMA_H

#define DMA_SRC			0x2007C000
#define DMA_DST			0x20080000
#define DMA_SIZE		0x1000

#define M2M				0x00
#define M2P				0x01
#define P2M				0x02
#define P2P				0x03

#define BURST4 0x04
#define WORD32_TRANSFER 0x2
#define INCREMENT 1
#define TERMINAL_INTERRUPT 0x80000000

#define DMA_CFG ((BURST4 << 12) | (BURST4 << 15) \
		| (WORD32_TRANSFER << 18) | (WORD32_TRANSFER << 21) | (INCREMENT << 26) | (INCREMENT << 27) | \
		TERMINAL_INTERRUPT)

void DMA_Init(uint32_t *src, uint32_t *dest, uint32_t len, uint32_t LLI);

#endif

