/*
===============================================================================
 Name        : labo3.c
 Author      : D. Bechevet, F. Vannel, A. Lescourt
 Copyright   : HES-SO hepia
 Year        : 2013-2014
===============================================================================
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>

typedef struct  {
	int32_t a;
	int8_t b;
	int16_t c;
	int8_t d;
	int32_t e;
} numbers_t;

uint32_t funcexo1(uint32_t *, uint32_t *);
uint32_t funcexo2(uint32_t *, uint32_t *, uint32_t);
void majuscule(char *s);

/* global variables */
int exo = 4;    // change this number with the exercise number you want to test;

int main(void)
{
	uint32_t valeurs_test[] = {1,23,17,4,0xFFFFFFF0,100};
	uint32_t *a;
	uint32_t *b;
	static uint32_t res, res_ref;
	uint32_t A1_vect[10] = {5,2,3,4,6,10,0x256,800,256,0x1234};
	uint32_t A2_vect[10] = {5,2,3,4,6,10,256,0xFEDCBA98,256,0x12345678};
	uint32_t B_vect[10];
	static uint32_t ok;
	char string[]="Hepia";

	switch(exo)      // select the function corresponding to the exercise to test
	{
		case 1 :
			a = &valeurs_test[0];       /* point our pointer at the first integer in our array */
			b = &valeurs_test[1];		/* point our pointer at the second integer in our array */
			res = funcexo1(a, b);
			a = &valeurs_test[2];       /* point our pointer at the third integer in our array */
			b = &valeurs_test[4];		/* point our pointer at the fifth integer in our array */
			res = funcexo1(a, b);
			break;
		case 2 :
			ok = funcexo2(A1_vect, B_vect, 10);          // B_vect = 2* A1_vect
			ok = funcexo2(A2_vect, B_vect, 10);          // B_vect = 2* A2_vect
			break;
		default:
			majuscule(string);
			break;
	}

	return 0;
}
