#include <stdint.h>
#include <math.h>
#include <stdio.h>

#define MOD_SIG_SIZE 1424

const int8_t mod_sig[MOD_SIG_SIZE]={
		-14,-19,6,11,-7,-8,-9,9,-19,
		1,-8,11,3,-3,20,46,23,0,-15,
		-28,-14,19,-9,10,-50,-9,38,91,55,
		-40,-58,-29,49,85,13,-15,-69,-35,54,
		79,27,-43,-76,-53,9,87,35,-32,-89,
		-32,27,77,35,-36,-69,-67,63,80,44,
		-35,-33,-13,-20,-5,21,-15,-12,-13,24,
		31,-14,-18,-51,-6,1,25,-10,19,33,
		45,-8,-30,-28,2,-28,-12,40,95,48,
		-33,-83,-41,47,68,34,-21,-72,-47,20,
		72,38,-61,-84,-57,38,77,40,-41,-64,
		-22,-11,-22,5,-6,-32,-32,24,1,22,
		-18,-28,-5,13,10,1,24,52,-22,-30,
		-51,-21,15,-42,-35,37,75,39,-78,-116,
		-34,34,61,11,-26,-54,-63,23,36,36,
		-59,-89,-80,27,70,49,-24,-108,-41,28,
		63,34,-25,-87,-27,19,83,21,-35,-40,
		-28,15,2,-5,-15,-12,-39,32,34,8,
		-8,19,23,-31,-61,-58,61,115,43,-47,
		-84,-14,26,26,10,10,8,7,-13,25,
		-17,-3,-47,-43,31,-15,-27,-1,64,52,
		-54,-84,-39,62,85,27,-29,-27,-10,-1,
		-5,-7,-16,-2,-16,19,18,29,-23,-41,
		-20,-4,1,10,27,48,30,-3,-17,5,
		3,-1,-32,19,86,23,-58,-97,-25,36,
		49,8,-26,-73,-66,36,77,55,-50,-81,
		-28,57,74,36,-39,-92,-48,42,37,-4,
		-41,-93,-64,64,96,33,-34,-17,-5,-8,
		15,-24,-9,-12,-11,-2,21,20,-32,-54,
		-13,8,-15,-26,7,36,-12,9,-20,-10,
		25,29,3,3,5,4,-22,-31,-6,-11,
		40,8,-10,-35,1,-2,19,20,23,56,
		42,-17,-24,-48,-2,0,18,54,82,50,
		-39,-92,-50,46,50,33,-11,-15,-13,29,
		-8,-7,-14,-41,-31,1,45,14,-3,7,
		6,-13,-95,-45,50,83,46,-48,-81,-40,
		-19,26,-3,6,5,-8,-29,38,33,-34,
		-53,0,-6,18,-5,36,75,40,-35,-110,
		-41,38,72,15,-41,-79,-46,14,47,24,
		-25,-80,-48,54,67,12,-29,-39,3,4,
		-37,2,11,-26,-27,33,56,19,-4,-12,
		7,-63,-88,-53,42,83,34,-57,-42,-43,
		23,57,22,-29,-69,-21,40,106,78,-34,
		-98,-22,35,37,15,12,15,-7,-14,32,
		-1,-49,-41,-21,-3,11,-4,-9,17,-1,
		-15,-3,-6,41,3,20,-11,-33,-13,4,
		-2,-41,9,40,32,-18,-46,-33,11,-18,
		-28,8,50,76,-22,-96,-62,41,40,14,
		-27,-70,-53,29,80,30,-13,-61,-10,32,
		64,55,-33,-78,-27,26,68,45,-24,-70,
		-36,49,82,48,-14,-49,-15,4,14,-8,
		-3,12,-26,6,15,32,-22,-26,6,-12,
		0,-15,-9,51,16,-27,-60,-1,10,9,
		-31,38,47,43,-37,-116,-43,62,90,35,
		-29,-38,-13,24,4,-23,-1,-36,-9,1,
		52,37,-2,-42,2,8,2,-19,30,33,
		20,-21,-33,-6,21,24,14,1,-3,24,
		-22,9,-40,34,28,-3,-10,-17,-9,5,
		5,-20,46,33,-3,-3,-16,5,29,54,
		16,-21,15,6,-14,-49,-13,30,19,-15,
		3,-19,-18,1,14,-7,-1,42,-8,-13,
		-45,-5,18,32,10,53,81,20,-64,-110,
		-38,47,96,34,4,-29,2,19,1,-4,
		10,-4,7,5,8,-7,-5,-49,-11,8,
		-1,16,15,21,-8,2,-16,-8,7,17,
		23,-7,-12,26,-25,-61,-12,9,43,17,
		-10,22,17,-21,-68,-36,50,94,53,-26,
		-82,-27,23,24,14,-7,-15,23,-13,6,
		1,8,-44,-33,1,52,43,-27,11,-7,
		-37,-33,-27,34,29,11,2,27,3,-29,
		-52,-38,40,119,66,-23,-76,-43,18,44,
		-1,0,6,15,4,25,31,-16,-49,-50,
		19,-9,-24,55,100,43,-62,-95,-53,49,
		89,35,-47,-71,-35,56,89,30,-38,-91,
		-31,37,105,65,-25,-41,2,6,-9,-8,
		24,-32,5,-8,46,38,-20,-20,31,-21,
		-80,-43,45,112,81,-24,-95,-65,21,44,
		11,17,-8,-17,5,22,-10,-12,-19,-14,
		2,19,26,30,-4,-1,9,-8,0,7,
		31,12,-24,-39,-10,-8,8,-10,9,24,
		-4,9,-49,-4,7,43,8,5,1,-14,
		-10,-53,-34,4,49,14,4,10,12,-36,
		-67,-53,25,70,51,-33,-50,-31,48,72,
		56,-27,-66,-24,54,110,39,-36,-85,-40,
		22,57,13,5,12,8,35,8,40,-46,
		-14,-36,16,-13,-28,35,61,46,-41,-114,
		-54,66,83,28,-14,-42,10,-7,-10,12,
		-17,-19,-14,29,62,29,-16,20,33,-38,
		-77,-52,37,90,47,-46,-62,-35,29,74,
		60,-33,-64,-45,17,61,38,-40,-71,-30,
		14,85,26,-33,-71,-47,19,75,45,-38,
		-61,-25,50,79,73,-38,-56,-33,38,101,
		64,-49,-89,-9,44,56,17,-9,-14,-18,
		22,31,33,10,-28,-12,5,-4,-47,21,
		103,50,-47,-88,-47,39,72,43,-29,-75,
		-56,41,78,26,-44,-64,-13,29,76,45,
		-40,-70,-36,45,56,36,-52,-85,-37,38,
		88,32,-30,-34,-11,-3,-2,-6,-8,-37,
		-19,1,71,21,-25,-10,-39,0,5,-18,
		31,38,30,-33,0,7,25,-20,-12,34,
		75,43,-47,-116,-39,37,57,30,-33,-67,
		-21,39,53,35,-29,-127,-10,32,92,50,
		-32,-69,-6,25,-10,16,-12,-25,-3,39,
		20,26,-32,-23,33,-13,-79,-33,49,81,
		46,-27,-58,-42,17,25,-3,13,-3,-3,
		3,34,31,-32,-24,4,-10,13,-14,21,
		84,45,-43,-105,-57,54,78,41,-31,-33,
		6,21,28,19,-27,0,-4,30,26,-15,
		-41,-9,-6,-3,-39,-10,-4,26,16,-20,
		-30,-22,16,25,-2,5,22,39,-14,-40,
		22,13,7,9,-15,-30,-17,16,-17,3,
		31,25,28,-23,-33,-28,14,-16,-1,25,
		100,32,-45,-96,-70,54,74,48,-25,-14,
		-12,-8,-1,-15,16,-71,-24,20,41,30,
		-27,22,22,-45,-72,-28,68,85,41,-54,
		-97,-7,36,54,55,-48,-65,-18,37,110,
		47,-32,-113,-51,29,48,27,-5,14,-5,
		7,33,21,-17,-51,-1,11,31,21,-20,
		38,5,-7,-10,-33,-7,32,0,-16,-24,
		-50,12,9,18,26,21,24,-44,-36,-29,
		3,-10,-19,25,54,39,-41,-114,-54,67,
		53,39,-27,-52,5,-13,9,-24,-4,-16,
		5,7,48,11,6,-15,-21,-9,-42,-10,
		-9,35,5,-17,-25,-3,2,27,22,22,
		7,4,-9,-19,-33,17,28,33,-23,-10,
		-6,-4,2,6,8,30,19,10,-12,-7,
		14,14,16,-26,13,20,-5,-10,-16,-1,
		40,16,-20,9,38,-34,-35,-36,49,103,
		35,-35,-96,-35,26,29,21,16,-34,-22,
		-5,1,11,1,-55,-22,-14,29,9,20,
		-17,6,4,-24,-6,45,56,30,-29,-22,
		16,-27,-111,-56,61,102,67,-40,-112,-51,
		5,28,7,2,-14,-22,-24,1,23,-6,
		-49,-26,26,38,-3,-14,-3,7,23,-20,
		-31,22,28,7,7,-24,-6,4,-15,-28,
		-2,2,-14,-8,-26,9,6,0,30,-7,
		-2,-19,-8,-28,-38,33,49,6,16,6,
		40,-27,-58,-58,52,88,42,-28,-54,-31,
		30,84,34,-18,-91,-44,34,90,62,-29,
		-92,-20,57,84,52,-9,-19,-25,32,22,
		22,-45,-63,-11,16,22,-18,-3,-18,14,
		-11,-18,-17,-2,-29,4,-2,3,19,-5,
		2,-6,4,21,13};

void print_tab(float* t, int len){
	for (int i=0; i<len; i++) {
		printf("%1.f ",t[i]);
	}
	printf("\n");
}

void convolve_valid(float* conv, float* f, float* g, int len_f, int len_g){
	float res;
	int cpt;
	for (int i=0; i<len_f; i++){
		res=0;
		cpt=0;
		for (int j=len_g-1; j>=0; j--) {
			if (i+cpt < len_f) {
				// printf("%f += %fx%f\n",res,g[j],f[i+cpt]);
				res += g[j]*f[i+cpt];
				cpt++;
			}
		}
		conv[i]=res;
	}
	
}

void convolve(float* conv, float* f, float* g, int len_conv, int len_f, int len_g){
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

void load_filter(char* pathname,float* buff, int size){
	FILE* fd = fopen(pathname,"r");
	int16_t f;
	for (int i=0; i<size; i++) {
		fscanf(fd, "%hd", &f);
		buff[i]=(float)f;
	}
	fclose(fd);
}

void tab_to_file(char* pathname, float* tab, int size){
	FILE* fd = fopen(pathname,"w");

	for (int i=0; i<size; i++) {
		fprintf(fd, "%f\n", tab[i]);
	}
	fclose(fd);
}

int main(){
    int fc = 23000;
    int fs = 138000;

// # DEMODULATION

// s_mod_n_cfr = np.zeros(s_mod_n.shape)
    float s_mod_n_cfr[MOD_SIG_SIZE]; 
// for k in range(s_mod_n.shape[0]):
	for(int k=0; k<MOD_SIG_SIZE; k++){
//     s_mod_n_cfr[k]=s_mod_n[k]*np.cos(2*np.pi*fc/fs*k)
		s_mod_n_cfr[k]=mod_sig[k]*cos(2*M_PI*fc/fs*k);
	}
	

// rrc=np.loadtxt("rrc_filter.txt")
	float rrc_filter[35];
	load_filter("rrc_filter.txt", rrc_filter, 35);

// #filtering...

    // filter with rrc
    float s_mod_n_lpf_tmp[MOD_SIG_SIZE+34];
    convolve(s_mod_n_lpf_tmp, s_mod_n_cfr, rrc_filter, MOD_SIG_SIZE+34, MOD_SIG_SIZE, 35);
	
	
	float s_mod_n_lpf[MOD_SIG_SIZE];
	int cpt=0;
	for (int i=0; i<MOD_SIG_SIZE+34; i++) {
		if (i>16 && i<MOD_SIG_SIZE+34-16) {
			s_mod_n_lpf[cpt++] = s_mod_n_lpf_tmp[i];
		}
	}

	// filter with wiener
	float wiener_filter[45];
	load_filter("wiener_filter_h2_echo_snr7.txt", wiener_filter, 45);
	float s_mod_n_w[MOD_SIG_SIZE];
	convolve_valid(s_mod_n_w,s_mod_n_lpf,wiener_filter,MOD_SIG_SIZE,45);

	// soft_dec = np.zeros(s_mod_n_w.shape[0]//6)
	float soft_dec[(MOD_SIG_SIZE-44)/6];
    // cpt=0
    // for i in range(0,s_mod_n_w.shape[0],6):
    //     soft_dec[cpt]=s_mod_n_w[i]
    //     cpt+=1
	cpt=0;
	for (int i=0; i<(MOD_SIG_SIZE-44); i+=6) {
		soft_dec[cpt++]=s_mod_n_w[i];
	}

    // soft_dec_bin = np.where(soft_dec > 0, 1 , 0)
	float soft_dec_bin[(MOD_SIG_SIZE-44)/6];
	for(int i=0; i<((MOD_SIG_SIZE-44)/6); i++) {
		if(soft_dec[i]>0)
			soft_dec_bin[i]=1;
		else
			soft_dec_bin[i]=0;
	}
    // bits = np.zeros(soft_dec_bin.shape[0]//2)
	float bits[(MOD_SIG_SIZE-44)/12];
    // for k in range(bits.shape[0]):
    //     bits[k] = s_mod_n_w[12*k] + s_mod_n_w[12*k+6] > 0

	for(int i=0; i<((MOD_SIG_SIZE-44)/12);i++){
		bits[i] = (s_mod_n_w[12*i] + s_mod_n_w[12*i+6]) > 0;
	}

    // rgb = np.zeros(bits.shape[0]//5,dtype=np.uint8)
	float rgb[(MOD_SIG_SIZE-44)/60];
    // c = 0
	cpt = 0;
    // for b in range(0,bits.shape[0],5):
    //     bit_0 = int(bits[b])
    //     bit_1 = int(bits[b+1])
    //     bit_2 = int(bits[b+2])
    //     bit_3 = int(bits[b+3])
    //     bit_4 = int(bits[b+4])
    //     rgb[c]=bit_0<<4 | (bit_1<<3) | (bit_2<<2) | (bit_3<<1) | bit_4 
    //     c+=1
	for(int i=0; i<(MOD_SIG_SIZE-44)/12; i+=5){
		rgb[cpt++]=(((int)bits[i]<<4) | ((int)bits[i+1]<<3) | ((int)bits[i+2]<<2) | ((int)bits[i+3]<<1) | ((int)bits[i+4]));
	}

	printf("res : ");
	print_tab(rgb,(MOD_SIG_SIZE-44)/60);
}
