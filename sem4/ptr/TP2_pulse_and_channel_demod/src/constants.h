#ifndef CONSTANTS_H
#define CONSTANTS_H

#define ETH_RX_EN	0		// must be set to 1 to enable Ethernet RX, 0 otherwise

#define FRAME_SIZE 1380		// pure modulated data
#define TOT_FRAME_SIZE (FRAME_SIZE+44)	// data+transcient
#define FRAME_NB 360		// for full image
#define UPSAMPLING 6

#endif
