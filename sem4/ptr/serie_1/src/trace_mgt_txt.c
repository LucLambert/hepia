
/*
 *  Description : trace management using semi-hosting
 *  Created on  : 30 sept. 2013
 *  Author      : VP
 */
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdlib.h>
#include <stdint.h>
#include "trace_mgt_txt.h"

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

void send_trace_to_file(int sig_idx, short val)
{
	fprintf(pf,"#%d\n%dsig_%03d\n", LPC_TIM0->TC/u_ticks, val, sig_idx);
}

void close_trace()
{
	fclose(pf);
}
