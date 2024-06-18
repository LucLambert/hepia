//---------------------------------------------------------------------------

#ifndef custom_randH
#define custom_randH
//---------------------------------------------------------------------------

#include <stdint.h>

/* Pseudo-random generator intialisation.
 * Parameter: seed: random-generator starting point
 */
void init_rnd32(uint32_t seed);

/* Generate a new random sample based on the last call of this function
 * Return: random value
 * */
uint32_t rnd32(void);


#endif
