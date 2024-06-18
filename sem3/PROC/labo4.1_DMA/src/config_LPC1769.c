
#include "config_LPC1769.h"

void init(void) {
	SCS |= 1<<5; //enable main oscillator
	while(!((SCS>>6)&1));
	CLKSRCSEL = 1; //select main oscillator
}
