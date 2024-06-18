/**
 * Name        : pulse_demod_etu.c
 * Date        : 2022
 * Description : Template of a RRC pulse shape and amplitude demodulator with air channel
 * 				 effect and white noise
 */

#include <cr_section_macros.h>
#include "LPC17xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "ethmac.h"
#include "lcd.h"
#include "debug.h"
#include "ethernet_mgt.h"
#include "constants.h"

#define RRC_FILTER_LEN 35
#define WIENER_FILTER_LEN 45
#define M_PI 3.14159265359

const float rrc_filter[RRC_FILTER_LEN]={-183,1141,2387,3088,2855,1530,-709,-3331,-5541,
		-6451,-5320,-1772,4053,11463,19322,26280,31063,32767,31063,
		26280,19322,11463,4053,-1772,-5320,-6451,-5541,-3331,-709,
		1530,2855,3088,2387,1141,-183};

// Wiener filter coefficients for SNR=7 and h=[.4 0 -.3 0 0 0 0 0 0 0 .3] :
const float wiener_filter[WIENER_FILTER_LEN]={-739,-1411,-1968,-2152,-1764,-768,650,2089,386,
		-2136,-1426,-436,684,1762,2636,3184,3344,3125,2592,
		1850,1028,263,-324,-652,-694,-481,-89,374,788,
		1047,1074,841,367,-282,-1013,-1714,-136,767,954,
		622,90,-313,-363,-2,-1476};

extern int8_t mod_sig[]; 	// direct read of ROM signal (for development)

// Ethernet frame buffer
__DATA(RAM2) int8_t rx_buf[2*TOT_FRAME_SIZE], *rx_ptr;
uint16_t demod_data[FRAME_SIZE/2/UPSAMPLING/5];				// 23 words of 5 bits by frame

void lcd_set_pos(unsigned char x0, unsigned int y0, unsigned char x1, unsigned int y1);
void Write_Data_U16(unsigned int y);
#define display_rgb_pixel(x) Write_Data_U16(x)

#define MOD_SIG_SIZE 1424

int j;

void convolve_valid(float* conv, float* f,const float* g, int len_f, int len_g){
	float res;
	int cpt;
	for (int i=0; i<len_f; i++){
		res=0;
		cpt=0;
		for (j=len_g-1; j>=0; j--) {
			if (i+cpt < len_f) {
				res += g[j]*f[i+cpt];
				cpt++;
			}
		}
		conv[i]=res;
	}

}

int j;

void convolve(float* conv, float* f,const float* g, int len_conv, int len_f, int len_g){
	if (len_conv != (len_f+len_g-1)) {
		return;
	}
	int cpt=0;
	float tmp_zeros[len_f+2*(len_g-1)];
	for (int i=0; i<len_f+2*(len_g-1); i++) {
		if((i>=(len_g-1)) && (i<(len_f+2*(len_g-1) - (len_g-1)))){
			tmp_zeros[i]=f[cpt++];
		}
		else{
			tmp_zeros[i]=0;
		}
	}
	float tmp_conv[len_f+2*(len_g-1)];
	convolve_valid(tmp_conv, tmp_zeros, g, len_f+2*(len_g-1), len_g);
	for (int i=0; i<len_conv; i++) {
		conv[i]=tmp_conv[i];
	}
}

void demod(int8_t* mod_sig, uint16_t mod_sig_size, float* res, int len){
    int fc = 23000;
    int fs = 138000;

// # DEMODULATION
    float s_mod_n_cfr[MOD_SIG_SIZE];
	for(int k=0; k<MOD_SIG_SIZE; k++){
		s_mod_n_cfr[k]=mod_sig[k]*cos(2*M_PI*fc/fs*k);
	}

// #filtering...

    // filter with rrc
    float s_mod_n_lpf_tmp[MOD_SIG_SIZE+RRC_FILTER_LEN-1];
    convolve(s_mod_n_lpf_tmp, s_mod_n_cfr, rrc_filter, MOD_SIG_SIZE+RRC_FILTER_LEN-1, MOD_SIG_SIZE, RRC_FILTER_LEN);


	float s_mod_n_lpf[MOD_SIG_SIZE];
	int cpt=0;
	for (int i=0; i<MOD_SIG_SIZE+RRC_FILTER_LEN-1; i++) {
		if (i>16 && i<MOD_SIG_SIZE+RRC_FILTER_LEN-17) {
			s_mod_n_lpf[cpt++] = s_mod_n_lpf_tmp[i];
		}
	}

	// filter with wiener
	float s_mod_n_w[MOD_SIG_SIZE];
	convolve_valid(s_mod_n_w,s_mod_n_lpf,wiener_filter,MOD_SIG_SIZE,WIENER_FILTER_LEN);

	float bits[(MOD_SIG_SIZE-WIENER_FILTER_LEN-1)/12];
	for(int i=0; i<((MOD_SIG_SIZE-WIENER_FILTER_LEN-1)/12);i++){
		bits[i] = (s_mod_n_w[12*i] + s_mod_n_w[12*i+6]) > 0;
	}

	cpt = 0;
	for(int i=0; i<(MOD_SIG_SIZE-WIENER_FILTER_LEN-1)/12; i+=5){
		res[cpt++]=(((int)bits[i]<<4) | ((int)bits[i+1]<<3) | ((int)bits[i+2]<<2) | ((int)bits[i+3]<<1) | ((int)bits[i+4]));
	}
}

int main(void)
{
	int j;

	init_lcd();

	memset(rx_buf, 0, 2*TOT_FRAME_SIZE);
#if ETH_RX_EN==1
	rx_ptr=(int8_t *)ethernet_init(NULL, 0, (unsigned char *)rx_buf, 2*TOT_FRAME_SIZE, NULL);
#endif
	LPC_EMAC->RxFilterCtrl = 0x1F;		// let all MAC frames pass

	while(1)
	{
		clear_screen(0);
		lcd_print(0,290,SMALLFONT, LCD_WHITE, LCD_BLACK,"Ready to receive frames...");
		lcd_set_pos(100, 100, 189, 191);

		float res[(MOD_SIG_SIZE-WIENER_FILTER_LEN-1)/60];
		demod(mod_sig,MOD_SIG_SIZE,res,(MOD_SIG_SIZE-WIENER_FILTER_LEN-1)/60);
		for(int i=0; i<((MOD_SIG_SIZE-WIENER_FILTER_LEN-1)/60); i++){
			printf("%1.f ", res[i]);
		}

		for (j=0; j<FRAME_NB; j++)			// 360 frames expected of 23 words of 5 bits
		{
#if ETH_RX_EN==1
			rx_ptr=(int8_t *)rec_eth(&len);	// Ethernet acquisition of one frame (blocking call)
			//LPC_GPDMA->DMACConfig = 0;	// stop DMA: could be useful to focus on first frame only
#else
			rx_ptr=mod_sig;					// input signal is one frame containing a reference signal (in flash).
#endif
			// warning: the following function can be used for debugging purpose, but it takes time!
			// int2file("rec_signal.txt", rx_ptr, TOT_FRAME_SIZE, sizeof(int8_t), true);

			// demodulation...


			// display_rgb_pixel();
		}
		lcd_print(0,290,SMALLFONT, LCD_WHITE, LCD_BLACK, "Press 'A' to start again...");
		//...
	}
	return 1;
}


