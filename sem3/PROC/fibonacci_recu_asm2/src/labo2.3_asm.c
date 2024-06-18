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

uint32_t funcexo1(uint32_t);

int main(void)
{
	static uint32_t res;
	res=funcexo1(10);
	return 0;
}
