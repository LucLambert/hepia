/*
 * collisions.c
 *
 *  Created on: 3 avr. 2019
 *  Author: V. Pilloux
 */
#include "sprites.h"
#include "collisions.h"

int test_collision(int sprite_id, sprite_t *sprite_array, int min_idx, int max_idx)
{
	int i, x, y;
	bool col_right, col_left, col_up, col_down;

	x=sprite_array[sprite_id].pos.x + sprite_array[sprite_id].speed.x;
	y=sprite_array[sprite_id].pos.y + sprite_array[sprite_id].speed.y;
	if (x<sprite_array[sprite_id].x_min)
		return WEST_COLLISION;
	if (x+sprite_array[sprite_id].width-1 > sprite_array[sprite_id].x_max)
		return EAST_COLLISION;
	if (y<sprite_array[sprite_id].y_min)
		return NORTH_COLLISION;
	if (y+sprite_array[sprite_id].height-1 > sprite_array[sprite_id].y_max)
		return SOUTH_COLLISION;
	for (i=min_idx; i<=max_idx; i++)		// search only collisions with ghosts (never with ball)
		if (i!=sprite_id && sprite_array[i].active)
		{
			col_right=(sprite_array[i].pos.x >= x) && (sprite_array[i].pos.x < x + sprite_array[sprite_id].width);
			col_left=(sprite_array[i].pos.x <= x) && (x < sprite_array[i].pos.x + sprite_array[i].width);
			col_down=(sprite_array[i].pos.y >= y) && (sprite_array[i].pos.y < y + sprite_array[sprite_id].height);
			col_up  =(sprite_array[i].pos.y <= y) && (y < sprite_array[i].pos.y + sprite_array[i].height);
			if ((col_right || col_left) && (col_down || col_up))
				return i;		// return (one of) the ID of the sprite creating the collision
		}
	return NO_COLLISION;
}


