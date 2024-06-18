/*
===============================================================================
 Name        : Labo_DMA_RGB.c
 Authors     : Fabien Vannel, Vincent Pilloux
 Description : template of labo RGB DMA
===============================================================================
*/

#include <stdint.h>
#include "config_LPC1769.h"

static uint8_t ws2812_color[24*3*2]; // 24 bits * 4 phases (max) (for 2 leds)


void timers_init(void)
{
	T0TCR=(1<<0); //Counter enable and reset
	T0TC=0;
	T0MR0=0;
	while(T0TC < 500){

	}
	T0TC=0;
	T0TCR=0;
	T0MCR=(0b11<<0);
	T0MR0=40-1;
}

/******************************************************************************
* Descriptions:		DMA interrupt handler
******************************************************************************/
void DMA_IRQHandler (void)
{
	DMACIntTCClear = (1 << 0); /*clear interrupt*/
	T0TCR=0;
}

void DMA_SetUp_and_Start(int frame_length)
{
	PCONP |= 1<<29; 				// Power-ON GPDMA
	DMACConfig = 1; 				// DMA enable
	ISER0=(1<<26);
	DMACC0SrcAddr = (unsigned long) ws2812_color;
	DMACC0DestAddr = (unsigned long) &FIO2PIN1;
	DMAREQSEL |= (1<<0); // set dma and timer link interrupt
	DMACC0Control = (frame_length & 0xFFF) | (1<<26) | (1<<31);
	DMACC0Config = (1<<0) | (1<<15) | (1<<11) | (8<<6);
	T0TCR|=(1<<0); //Counter enable
}

void RGB_tab (uint8_t R, uint8_t G, uint8_t B)
{
	// fill ws2812_color[] with the required color
	int j=7;
	for(int i=0; i<24*3*2; i++){
		if(i%3==0){
			ws2812_color[i]=0;
		}else if (i%3==1){
//			if(i/24*3==0 || i/24*3==3){
//				ws2812_color[i]=G&~(1<<j--);
//			}else if (i/24*3==1 || i/24*3==4){
//				ws2812_color[i]=R&~(1<<j--);
//			}else if (i/24*3==2 || i/24*3==5){
//				ws2812_color[i]=B&~(1<<j--);
//			}
//			if(j<0){
//				j = 7;
//			}
			ws2812_color[i]=1;
		}else if (i%3==2){
			ws2812_color[i]=1;
		}

	}
	// send color to led by DMA
	DMA_SetUp_and_Start(24*3*2);
}

void sleep (void)
{
	__asm__("wfi");				// wait for interrupt (any!)
}

int main(void)
{
	PCLKSEL0 = (1<<2) | (1<<4); // Setup PCLK TIMER0 et TIMER1 à CLK (100 MHz) (other peripherals to 25 MHz)
	FIO2DIR |= 1<<8; 			// set P2.8 as output (RGB LED)
	FIO2SET =1<<8;				// default value (1 -> 0 V on leds)

	timers_init();

    	// choose next color
    	RGB_tab(255, 0, 0);

    	// wait 20 ms
    	int tmp = T0TC;
    	while(tmp + 200 < T0TC){

    	}
    return 0;
}
