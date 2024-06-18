/*
 * exercice3.c
 *
 *  Created on: Mar 2, 2022
 *      Author: luclaptop
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdint.h>
#include <stdlib.h>
#include "adc.h"

/*short read(){
	while(LPC_ADC->ADDR0 & 1<<31 != 1<<31);
	LPC_ADC->ADCR|=(1<<24);
	return LPC_ADC->ADDR0>>4 & 0x00000FFF;
}

int main(void)
{
	adc_init(0);

	while(1){
		printf("%d\n",read());
	}
	return 0 ;
}*/
