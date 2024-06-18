/*
 * Description : Exercise 1, serie 1, trace management using USB semi-hosting
 * Created on  : 15.01.2014
 * Author      : VP
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <stdio.h>
#include <stdbool.h>
#include "trace_mgt_txt.h"
#include "uart.h"

#define TICKS_IN_MS (SystemCoreClock/1000/4)
#define TICKS_IN_US (SystemCoreClock/1000000/4)

#define UNIT_TICKS TICKS_IN_MS

typedef struct {
	uint8_t synchro; /* always set to 0x55 */
	uint8_t trace_id; /* bit 8 indicates other traces than VCD */
	short value;
	uint32_t time;
} trace_t;

/*
* Description : écrit une trace sur l'UART 0 (une structure trace_t).
* Le temps courant est ajouté à la trace par cette fonction en lisant la
* valeur courante du timer 0.
*
* trace_id: identificateur de la trace
* value: valeur de la trace (seulement 0 ou 1 pour les traces VCD)
*/
void write_trace(uint8_t trace_id, short value){
	trace_t t = {0x55,trace_id,value,LPC_TIM0->TC};
	uart0_send_ref(&t,sizeof(t));
}

int main(void)
{
	uart0_init_ref(115200, NULL, NULL);
	//uart0_send_ref("hello",6);

	bool sig[2]={1, 0};	// signals start values

	create_vcd_header("test.vcd", sig, 2, UNIT_TICKS==TICKS_IN_MS?"1 ms":"1 us", UNIT_TICKS);
	LPC_TIM0->TCR = 1;			// start timer 0, default freq. with __USE_CMSIS: 25 MHz


	// your code producing the required timing traces

	int stop=0;
	for(int i=0; i<400;i++){
		stop = LPC_TIM0->TC + 750000; // 2500
		while(LPC_TIM0->TC<stop){};
		write_trace(0, i%2);
		write_trace(1, (i+1)%2);
	}

	
	close_trace();
	return 0;
}
