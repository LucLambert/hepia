/**
 * Description: Template of DMA exercises using SD card and LCD.
 *              Notes:
 *              - only works with Mylab2 release 2020!!
 *              - the images must be stored in SD flash in RGB555 big endian format.
 *              - DMA channel 2 is used to transmit dummy data on SSP1 (SD card) in order to receive data
 *              - DMA channel 3 copies the data from SSP1 to SSP0 (LCD)
 *              - there is always a latency of one byte when using the DMA after having done "standard"
 *                transfers on SSP ports. Therefore, the  first byte of each frame must be transmitted in advance
 *                before starting a DMA transfer
 *
 * Author: V. Pilloux
 * Hepia Cores
 * oct. 2020
 */

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "LPC17xx.h"
#include "sdcard.h"
#include "lcd.h"
#include "ssp.h"
#include "sd_card_read.h"

#define IMAGE_SIZE (240*120*sizeof(uint16_t))				// complete size: 240*120 [pixels] (*2 bytes)
#define IMAGE_SIZE_IN_FLASH (((IMAGE_SIZE+511)>>9)<<9)		// padded image size (to 512 bytes blocks)

int ex=2;						// selects the exercise number
uint32_t data[128*40];

void test_data()
{
	int i;

	for (i=0; i<128*40; i++)
		if (data[i]!=i)
		{
			printf("Error while checking data written on SD card! (i: %d)", i);
			exit(1);
		}
}

int main (void)
{
	int k;

	init_lcd();						// also initializes SSP0 @ 10 MHz
	clear_screen(0);

	if (init_sd_card(LPC_SSP1, NULL)!=NO_ERROR)		// clock freq. to 16.66 MHz (but then set to 10 MHz by sd_dma_to_lcd())
	{
		printf("SD card initialization error!");
		return 1;
	}
	init_ssp1_dma();

	if (ex==1)
	{
		memset(data,0,128*40*sizeof(uint32_t));

		sd_to_mem(0, (uint8_t *)data, 40*128*sizeof(uint32_t));

		// wait end of transfer...
		volatile int i = 0;
		while( i++<1600000){}

		test_data();
	}

	if (ex==2)
	{
		uint32_t start=0;
		uint32_t duration=0;
		LPC_TIM0->TCR=2;
		LPC_TIM0->TCR=1;
		start=LPC_TIM0->TC;
		LPC_SSP1->CR0 = (4 << 8) + ((8-1) << 0);		// SSP1 rate adapted to LCD (10 MHz)
		lcd_set_pos(0,0,LCD_MAX_WIDTH-1,120-1);
		// read one buffer of BUFFER_SIZE at beginning of flash (= first image)
		if (sd_to_lcd(0, IMAGE_SIZE)!=NO_ERROR)
		{
			printf("SD card multiple read error!");
			return 1;
		}
		duration=(LPC_TIM0->TC-start)/25; // time elapsed = 400ms
		// wait end of transfer...
		volatile int i = 0;
		while( i++<500000){}

		printf("time elapsed in ms : %d\n",duration);
	}

	if (ex==3)
	{
		LPC_SSP1->CR0 = (4 << 8) + ((8-1) << 0);		// SSP1 rate adapted to LCD (10 MHz)
		lcd_set_pos(0, 0, LCD_MAX_WIDTH-1, 120-1);
		while(1)
		{
			for (k=0; k<1114; k++)		// the surf video has 1114 images
			{
				lcd_set_pos(0, 0, LCD_MAX_WIDTH-1, 120-1); // replace start image at top left
				sd_to_lcd(k*IMAGE_SIZE_IN_FLASH, IMAGE_SIZE);
				//wait end of transfer ...
				volatile int i = 0;
				while( i++<400000){}
			}

		}
	}
	return 0;
}
