/*
===============================================================================
 Name        : labo2.c
 Author      : D. Bechevet, F. Vannel, A. Lescourt, V. Pilloux
 Copyright   : HES-SO hepia
 Year        : 2013-2014
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>

// assembly functions prototypes
uint32_t funcexo1(uint32_t, uint32_t);
uint32_t funcexo2(uint32_t);
uint32_t funcexo3(uint32_t);
long long funcexo4(long long, uint32_t);


/* global variables */
uint8_t exo;		// change this variable with the exercise number you want to test


/***********************************
 * function     : function1_bonus
 * arguments    : Unsigned Int 32, Unsigned Int 32
 * return value : Unsigned Int 32
 * Bonus - Code in C for the function 1
 ***********************************/
uint32_t function1_bonus(uint32_t val1, uint32_t val2)
{
	if(val1 > val2)
		return val1-val2;
	return val2-val1;
}

/***********************************
 * function     : function2_bonus
 * arguments    : Unsigned Int 32
 * return value : Unsigned Int 32
 * Bonus - Code in C for the function 2
 ***********************************/
uint32_t function2_bonus(uint32_t val1)
{
	uint32_t a = 0;
	uint32_t b = 1;
	while(val1 >= a){
		a += b;
		b++;
	}

	return a; // replace 0 by the name of your variable to be returned
}

int main(void)
{
	exo = 4;    // change this number with the exercise number you want to test

	uint32_t a,b,c;
	uint8_t  i;

	unsigned long long B_64;

	while (1)
	{
		switch(exo){					// select the function corresponding to the exercise to test

		case 1 :
			b = funcexo1(128,103);    // try with another values
			c = funcexo1(8,24);       // try with another values

			a = function1_bonus(b,c);	  // Bonus exercise 1

			break;
		case 2 :
			a = funcexo2(9);          // try with another value

			a = function2_bonus(a);   // Bonus exercise 2

			break;

		case 3 :
			a = funcexo3(5);          // try with another value
			break;

		case 4 :
			B_64=0x6000000A50000009;	// try with another value
			for (i=0; i<32; i++)
				B_64=funcexo4(B_64,1);

			B_64=0x7;					// try with another value
			for (i=0; i<32; i++)
				B_64=funcexo4(B_64,0);

			B_64=0xFE00000D40000089;	// try with another value
			B_64=funcexo4(B_64,2);
			break;

		}
	}
	return 0;
}
