/*
 * display.h
 *
 *  Created on: 10 march 2020
 *  Author: V.P.
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include "sprites.h"


// Adaptation of display_bitmap16() function. The 'color' given as parameter
// modifies the original one, turning green component to BLUE or RED. If color=NONE,
// the bitmap original colors are not modified.
// The coordinates of the image to display could be located outside
// the screen. In this case, only the visible part of the picture will be
// displayed.
void display_bitmap16_special(const unsigned short *bitmap, int x, int y, uint16_t width, uint16_t height, color_t color);



#endif /* DISPLAY_H_ */
