/*
 * bubbles.h
 *
 *  Created on: 16 juin 2021
 *  Author: vincent.pilloux
 */

#ifndef BUBBLES_H_
#define BUBBLES_H_

#include "sprites.h"

#define EXIT(t) {printf("%s", t); exit(1);}
#define ABS(x)  (((x)<0)?-(x):(x))

#define RACKET_SPEED 4
#define RACKET_DELAY 10
#define RACKET_BOOST_TIME 300		// time duration [ms] the racket becomes RED after having pressed joystick
#define BUBBLE_NB 6
#define MAX_STD_BUBBLE_SPEED 4		// max speed reachable by random speed increase/decrease
#define ABS_MAX_BUBBLE_SPEED 6		// absolute max speed, reached when the racket is in boost mode or if a ball collides with booster ball
#define BUBBLE_DELAY 30
#define BUBLE_EXPLOSION_DELAY 900	// [ms]
#define BOOSTER_BUBBLE_IDX 4
#define NB_SPRITES (2+BUBBLE_NB)

#define SCORE_HEIGHT 12


typedef struct {
	bool game_started;				// winner is true if the game ends
	int scores[2];
	int sprite_idx;
	bool sprite_active;				// true if the sprite must be displayed
	coord_t sprite_pos;				// coordinates of all sprites: master racket, slave racket, 6 bubbles
	color_t color;
	int bmp_idx;					// used only for bubbles
} master_tx_t;

typedef struct {
	int gpio1;								// slave state of GPIO1 (containing joystick information)
	bool button_b;							// true if slave B button pressed
} slave_rx_t;

extern sprite_t sprites[NB_SPRITES];
extern master_tx_t master_tx[2];
extern slave_rx_t slave_rx[2];
extern master_tx_t *master_tx_ptr;

#endif /* BUBBLES_H_ */
