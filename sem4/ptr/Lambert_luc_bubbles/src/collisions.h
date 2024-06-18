/*
 * collisions.h
 *
 *  Created on: 3 avr. 2019
 *  Author: VP
 */

#ifndef COLLISIONS_H_
#define COLLISIONS_H_

// Bound collision enum
enum {
	NO_COLLISION=-1,
	NORTH_COLLISION=-2,
	EAST_COLLISION=-3,
	SOUTH_COLLISION=-4,
	WEST_COLLISION=-5
};

/* The function looks at the collision in the direction of the speed vector of the sprite referenced as "object_id".
 * It detects all collisions among all objects of 'sprite_array' indexes between min_idx and max_idx (skipping object_id itself).
 * The collision is anticipated, since the detection is based on the current speed and position of the sprite.
 * Parameters:
 * 		sprite_id: index of the moving sprite trying to detect a collision
 * 		sprite_array: array of all objects
 * 		min_idx:   lower index of the array of sprites to test for collision (included)
 * 		max_idx:   higher index of the array of sprites to test for collision (included)
 * Return: NO_COLLISION if no collision. Otherwise: index of the sprite provoking the collision or
 *         NORTH_COLLISION,	EAST_COLLISION,	SOUTH_COLLISION, WEST_COLLISION if the screen border is reached
 */
int test_collision(int sprite_id, sprite_t *sprite_array, int min_idx, int max_idx);

#endif /* COLLISIONS_H_ */
