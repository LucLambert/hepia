/*
 * LCD.h
 *
 *  Created on: Feb 22, 2022
 *      Author: luclaptop
 */

#ifndef LCD_H_
#define LCD_H_

#include "ppm.h"

#define COL8TO5(x) (x >> 3)
#define COL8TO6(x) (x >> 2)

#define RGB(r,g,b) ((COL8TO5(r)<<11)|(COL8TO6(g)<<5)|(COL8TO5(b)))

void init_LCD();
void fill_screen(uint16_t color);
void fill_area(uint16_t x0, uint16_t x1, uint16_t y1, uint16_t y2, uint16_t color);
void set_pix(uint16_t x, uint16_t y, uint16_t color);
void draw_line(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color);
void draw_circle(uint16_t c_x, uint16_t c_y, uint16_t r, uint16_t color);
void draw_cross(uint16_t x, uint16_t y, uint16_t size, uint16_t color);
void fill_square(uint16_t x_c, uint16_t y_c, uint16_t size, uint16_t color);
void print_char(uint16_t x, uint16_t y, char c, uint16_t color);
void disp_img(img_t* img);

#endif /* LCD_H_ */
