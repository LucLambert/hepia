/*
 * sprites.h
 *
 *  Created on: 4 févr. 2020
 *  Author: VP
 */

#ifndef SPRITES_H_
#define SPRITES_H_

#include <stdint.h>
#include <stdbool.h>

#define BUBBLE_SIZE 28
#define RACKET_HEIGHT 8
#define RACKET_WIDTH 32

// reference on sprites (in flash):
extern const unsigned short bubble1a[], bubble1b[], bubble1c[], bubble1d[], bubble1e[], bubble2[], bubble3[], bubble4[], bubble5[], bubble6[], bubble7[], bubble8[], bubble9[];
//extern const unsigned short gift1[], gift2[], gift3[], gift4[], gift5[], gift6[], gift7[], gift8[], gift9[];
extern unsigned short racket_width, racket_height;
extern unsigned short racket_sprite[];

typedef struct
{
	int x;
	int y;
} coord_t;

typedef enum {
	NONE,						// no color modifier
	BLUE,						// strengthen blue component
	RED,						// strengthen red component
	GREEN						// strengthen green component
} color_t;

// defines a "squared" object. "pos" defines the position of the center of the object
// and radius is the number of pixels considered around pos in x and y directions
typedef struct
{
	coord_t pos;				// current sprite position (top left)
	coord_t old_pos;			// position before last move
	coord_t speed;				// used to calculate next position (or determine collisions)
	int16_t width;				// sprite width
	int16_t height;				// sprite height
	int16_t sprites_nb;			// number of sprite bitmaps available (max 5)
	int16_t bmp_idx;			// index of the sprite to display
	const unsigned short *bmp[18];	// sprite bitmap(s) for animation
	color_t color;				// color modifier of the sprite
	uint16_t period;			// display period [ms]
	int16_t x_min;				// minimum x coordinate which can be reached by a pixel of the matrix
	int16_t y_min;				// idem for y
	int16_t x_max;				// maximum x coordinate which can be reached by a pixel of the matrix
	int16_t y_max;				// idem for y
	bool active;				// true if the sprite is active (must be displayed)
} sprite_t;

#endif /* SPRITES_H_ */
