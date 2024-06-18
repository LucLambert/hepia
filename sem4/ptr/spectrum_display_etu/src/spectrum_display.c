/**
 * Name        : spectrum_display.c
 * Date        : 10.10.2018
 * Description : template of real time spectrum display of microphone sound
 */

#include <cr_section_macros.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LPC17xx.h"
#include "ethmac.h"
#include "lcd.h"
#include "adc.h"
#include "debug.h"
#include "dma_handler.h"

#define BUF_SIZE 4032							// 63*64 samples
#define NB_OF_FREQ 32
#define FS 16000
#define PI 3.14159265359
#define BAR_WIDTH (LCD_MAX_WIDTH/NB_OF_FREQ)
#define BAR_HEIGHT 240							// maximum display bar height (from screen bottom)

volatile int flag=0, buf_idx=0;
__DATA(RAM2) uint16_t buffer[2*BUF_SIZE];       // acquisition double buffer

extern uint16_t sig_ref[];						// this signal can be used for TFD debugging instead of real time acquisition

static int32_t pre_c_cos[64];					// tableau cos pre calc for faster TFD
static int32_t pre_c_sin[64];					// tableau sin pre calc for faster TFD

static void setup_peripherals(void)
{
	ethernet_power_down();						// limit sound noise
	init_lcd();
	clear_screen(LCD_BLACK);
}

// Display the spectrum (to be filled)
// Parameter: spectrum_max_value: current maximum spectrum value to be considered for display
void display(uint32_t spectrum_max_value, uint32_t* X, int len)
{
	for(int i=0; i<len; i++){
		int x = i*BAR_WIDTH;
		int y = (X[i]/10000)*BAR_HEIGHT/(spectrum_max_value/10000);
		int y1 = LCD_MAX_HEIGHT-1-y;
		int x2 = x+BAR_WIDTH-1;
		int y2 = LCD_MAX_HEIGHT-1;
		lcd_filled_rectangle(x, y1, x2, y2, LCD_RED);
	}
}

// callback function called at the end of BUF_SIZE sample acquisition
// Parameter: buf_index: 0 or 1, indicating the buffer that as been just filled
void buffer_filled(int buf_index)
{
	buf_idx=buf_index;
	//LPC_GPDMACH1->DMACCConfig=0;   // stop sample acquisition (DMA 1): line to be removed !
	flag++;
}

/**
 * cette fonction calcule la tfd avec :
 * X resultat du calcul tfd doit être de taille N/2-1
 * signal tableau des echantillons
 * len nombres d'échantillons
 * N nombres de bandes de fréquences
 * M diviseur du signal pour tfd plus précise
 */

void compute_tfd(uint32_t* X, uint16_t* signal, int len, int N, int M){

    // perform tfd
    for (int i=0; i<(len/M); i++) {
        uint32_t tmp_X[N/2 -1];
        for (int n=1; n<(N/2); n++) {
            int32_t im=0;
            int32_t res=0;
            for (int l=M*i; l<(M*i+M); l++) {
                res+=signal[l]*pre_c_cos[(l*n)%64];
                im+=signal[l]*pre_c_sin[(l*n)%64];
            }
            tmp_X[n-1] = abs(res) + abs(im);
        }

        for (int j=0; j<(N/2 -1); j++) {
        	if(i==0)
        		X[j] = tmp_X[j];
        	else
        		X[j] += tmp_X[j];
        }
    }
}

void compute_pre_cos_sin(int N){
    for (int i=0; i<N; i++) {
    	//*10000 car (2^31) - ((2^16) * 10000) = 1492123648 > 0
    	pre_c_cos[i]=cos(2*PI*i/N)*10000;
        pre_c_sin[i]=sin(2*PI*i/N)*10000;
    }
}

uint32_t max_array(uint32_t* tab, int len){
	int32_t max=0;
	for(int i=0; i<len;i++){
		if(max<tab[i]){
			max=tab[i];
		}
	}
	return max;
}

uint32_t maximum(uint32_t a, uint32_t b){
	return a>=b ? a : b;
}

int main(void)
{
	setup_peripherals();
	lcd_print(10,10,BIGFONT, LCD_WHITE, LCD_BLACK, "Sound spectrum");

	uint8_t N=64;
	compute_pre_cos_sin(N);
	init_adc_dma(0, FS, buffer, BUF_SIZE, buffer_filled);				// launch microphone samples acquisition
	uint32_t X[NB_OF_FREQ - 1];
	uint32_t max, pre_max=0;

	int pre_flag=0;
	while(1){
		if(pre_flag!=flag){
			pre_max = max;
			compute_tfd(X, &(buffer[buf_idx*BUF_SIZE]), BUF_SIZE, N, N);
			max = max_array(X, (NB_OF_FREQ - 1));
			max = maximum(max,pre_max*80/100);
			lcd_filled_rectangle(0, LCD_MAX_HEIGHT-1-BAR_HEIGHT, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-1, LCD_BLACK);
			display(max, X, (NB_OF_FREQ - 1));
			pre_flag=flag;
		}
	}

//	int2file("sig.txt", buffer, BUF_SIZE, sizeof(uint16_t), false);		// save signal received (DMA 1 must be stopped to do that)

	return 0;
}



