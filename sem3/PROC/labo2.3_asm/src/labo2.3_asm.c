/*
===============================================================================
 Name        : labo2.3.c
 Author      : V. Pilloux, F. Vannel
 Copyright   : HES-SO hepia
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

void funcexo1(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t *);
uint32_t funcexo2(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
int funcexo3(numbers_t s);

/* global variables */
int exo = 3;    // change this number with the exercise number you want to test;

int main(void)
{
	static uint32_t res, res_ref;
	numbers_t s;

	switch(exo)      // select the function corresponding to the exercise to test
	{
	case 1:
		funcexo1(0xffffffff, 0xffffffff, 0xaaaa5555, 0xbaba6565, &res);
		break;
	case 2:
		res=funcexo2(3, 2, 6,7);					// doit retourner 48
		res=funcexo2(0x10000, 0x10005, 6,7);    	// doit retourner 0
		res=funcexo2(0xF000, 0x8805, 0x8700,0xF760); // doit retourner 0
		break;
	default:
		s.a=5; s.b=-3; s.c=-1; s.d=10; s.e=3;
		res_ref=s.a+s.b+s.c+s.d+s.e;
		res=funcexo3(s);
		if (res!=res_ref)
			while(1);			// error
		break;
	}

	return 0;
}
