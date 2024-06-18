/**
*  Created on  : 19.01.2014
 * Author      : VP
 * Description : exercice 1 of serie 4
 */


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "uart.h"
#include "circ_buff.h"

#define TICKS_IN_MS (SystemCoreClock/1000/4)
#define TICKS_IN_US (SystemCoreClock/1000000/4)

#define UNIT_TICKS TICKS_IN_MS


trace_t buff[256];
circ_buff_t c = {buff, 0, 0, sizeof(buff)};
xSemaphoreHandle sem, mutex;

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
	push(&c,t);
}

FILE *pf=NULL;
unsigned u_ticks=1;

int create_vcd_header(char *filename, bool *sig, int nb_signals, char *timescale,  unsigned unit_ticks)
{
	int i;

	if ( ( pf = fopen(filename,"w")) == NULL) {
      printf("ERROR: File %s could not be opened\n", filename);
      return -1;
   }
   u_ticks=unit_ticks;

   /** \li Write on the VCD file the info relative to the software that collected and converted the traces */
   fprintf(pf,"$version\n   VCD tracing\n");
   fprintf(pf,"	Hepia\n$end\n\n");

   /** \li Write on the VCD file the timescale to use */
   fprintf(pf,"$timescale\n   %s\n$end\n\n", timescale);

   fprintf(pf,"$comment\n$end\n\n");

   /** \li Write on the VCD file the name of the module containing the traces collected */
   fprintf(pf,"$scope module Collected traces $end\n");

   for (i=0; i<nb_signals; i++)
   {
	   fprintf(pf,"$var wire\t 1  sig_%03d sig_%03d $end\n", i, i);
   }
   fprintf(pf,"$upscope $end\n$enddefinitions  $end\n\n$dumpvars\n");
   for (i=0; i<nb_signals; i++)
   {
	   fprintf(pf,"%dsig_%03d\n", sig[i], i);
   }
   fprintf(pf,"$end\n\n\n");

   return 0;
}

void wait_5ms(){
	int stop = LPC_TIM0->TC + 125000;
	while(LPC_TIM0->TC<stop){};
}

void A(){

	while(1){
		wait_5ms();
		xSemaphoreTake(sem, portMAX_DELAY);
	}
}

void B(){
	while(1);
}

void C(){
	while(1){
		for(int i=0; i<8;i++){
			wait_5ms();
		}
		xSemaphoreGive(sem);
	}
}

void vApplicationIdleHook(void){
	for(int i=0; i<c.write;i++){
		trace_t t = pop(&c);
		uart0_send_ref(&t,sizeof(t));
	}
	clear(&c);
}

int main(void)
{
	uart0_init_ref(115200, NULL, NULL);

	LPC_TIM0->TCR = 1;			// start timer 0, default freq. with __USE_CMSIS: 25 MHz

	sem=xSemaphoreCreateCounting(1,0);

	if (xTaskCreate(A, (signed portCHAR *)"A", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL)!=pdPASS) {return 1;}
	//if (xTaskCreate(B, (signed portCHAR *)"B", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL)!=pdPASS) {return 1;}
	if (xTaskCreate(C, (signed portCHAR *)"C", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL)!=pdPASS) {return 1;}

	vTaskStartScheduler();

	return 1;
}
