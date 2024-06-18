/*
===============================================================================
 Name        : cmsis.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

#include "LCD.h"
#include "SSP.h"
#include "UART.h"
#include "I2C.h"
#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

// TODO: insert other definitions and declarations here
#define ACCEL 0x1D
#define WHO_AM_I 0x0F
#define CTRL_1 0x20
#define CTRL_2 0x21

#define CONFIG_ACCEL 0b01010111

#define OUT_X_L_A 0x28
#define OUT_X_H_A 0x29
#define OUT_Y_L_A 0x2A
#define OUT_Y_H_A 0x2B
#define OUT_Z_L_A 0x2C
#define OUT_Z_H_A 0x2D

i2c_transaction_t t;
int main(void) {

//    // TODO: insert code here
//	i2c_config();
//	t.slave_addr=ACCEL;
//	t.data_write_len=2;
//	t.data_read_len=0;
//	t.data_ptr=0;
//	t.transaction_done=0;
//	t.data[0]=CTRL_1;
//	t.data[1]=CONFIG_ACCEL;
//	i2c_start_transaction();
//
//	int16_t x,y,z=0;
//	double x_u,y_u,z_u=0;
//
//	uint16_t x_disp,y_disp,x_last,y_last=0;
//
//	ssp_config();
//	init_LCD();
//	fill_screen(RGB(0,0,0));
//
//
//	uart_config(115200, WORD_LENGTH_8, PARITY_DISABLE, STOP_BIT_1);
	ssp_config();
	init_LCD();
	fill_screen(RGB(255,255,255));

	print_char(70, 120, 'G', RGB(0,0,255));
	print_char(90, 120, 'O', RGB(255,0,0));
	print_char(110, 120, 'O', RGB(255,255,0));
	print_char(130, 120, 'G', RGB(0,0,255));
	print_char(150, 120, 'L', RGB(0,255,0));
	print_char(170, 120, 'E', RGB(255,0,0));
    while(1) {
//    	t.slave_addr=ACCEL;
//    	t.data_write_len=1;
//    	t.data_read_len=6;
//    	t.data_ptr=0;
//    	t.transaction_done=0;
//    	t.data[0]=OUT_X_L_A;
//    	i2c_start_transaction();
//    	x = t.data[1] | t.data[2]<<8;
//    	y = t.data[3] | t.data[4]<<8;
//    	z = t.data[5] | t.data[6]<<8;
//
//    	x_disp= 120 + y*239/0x8CCC; //normalize to 1.1G
//    	y_disp= 160 + (-x)*239/0x8CCC; //normalize to 1.1G
//
//    	x_u = ((double)x+0x7FFF)/0x3FFF -2;
//    	y_u = ((double)y+0x7FFF)/0x3FFF -2;
//    	z_u = ((double)z+0x7FFF)/0x3FFF -2;
//
//    	draw_line(120, 120, 0, 319, RGB(255,255,0));
//    	draw_line(0, 239, 160, 160, RGB(255,255,0));
//    	draw_circle(120, 160, 50, RGB(0,0,255));
//    	draw_circle(120, 160, 80, RGB(255,255,255));
//    	draw_circle(120, 160, 110, RGB(255,0,0));
//
//    	fill_square(x_last, y_last, 6, RGB(0,0,0));
//    	fill_square(x_disp, y_disp, 6, RGB(127,0,125));
//
//    	print_char(215, 140, '1', RGB(255,0,0));
//    	print_char(220, 140, 'g', RGB(255,0,0));
//
//    	x_last=x_disp;
//    	y_last=y_disp;
//    	char str[25];
//    	sprintf(str, "x:%*.2f y:%*.2f z:%*.2f %c",5,x_u,5,y_u,5,z_u,13);
//    	uart_send_str(str,sizeof(str));
    }
    return 0 ;
}
