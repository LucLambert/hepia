/*
 * display.c
 *
 *  Created on: 10.3.2020
 *  Author: VP
 */
#include "display.h"
#include "lcd.h"

// taken from MyLab_lib:
void LCD_SetPos(unsigned char x0, unsigned int y0, unsigned char x1, unsigned int y1);
void Write_Data(unsigned char DH,unsigned char DL);
void Write_Data_U16(unsigned int y);


void display_bitmap16_special(const unsigned short *bitmap, int x, int y, uint16_t width, uint16_t height, color_t color)
{
	int i, x1=x, x2=x+width-1, y1=y, y2=y+height-1, x_offset=0, y_offset=0, real_width=width;
	int bmp_idx;
	uint16_t pixel, green_cpt, red_cpt, blue_cpt;

	if (x<0)
	{
		x1=0;
		x_offset=x1-x;
		real_width=width-x_offset;
	}
	if (y<0)
	{
		y1=0;
		y_offset=y1-y;
	}
	if (x+width-1>LCD_MAX_WIDTH-1)
	{
		x2=LCD_MAX_WIDTH-1;
		real_width=width-(x+width-LCD_MAX_WIDTH);
	}
	if (y+height-1>LCD_MAX_HEIGHT-1)
	{
		y2=LCD_MAX_HEIGHT-1;
	}

	LCD_SetPos(x1, y1, x2, y2);
	for(i = 0; i<(x2-x1+1)*(y2-y1+1); i++)
	{
		bmp_idx=y_offset*width+x_offset + (i/real_width)*width + (i%real_width);
		green_cpt=(bitmap[bmp_idx]&0x7E0)>>5;
		red_cpt=(bitmap[bmp_idx]&0xF800)>>11;
		blue_cpt=bitmap[bmp_idx]&0x1F;
		switch(color)
		{
		case RED:				// remove green and push it to red component
			pixel=(((red_cpt<<1/*+green_cpt>>1*/)&0x1f)<<11) | ((green_cpt>>1)<<5) | (blue_cpt);
			break;
		case GREEN:				// remove red and push it to blue component (bubble appears to be green in this case)
			pixel=((red_cpt>>2)<<11) | (green_cpt<<5) | (blue_cpt>>1);
			break;
		default:
			pixel=bitmap[bmp_idx];
		}

		Write_Data_U16(pixel);
	}
}



