/*
 * ACCEL.h
 *
 *  Created on: Apr 14, 2022
 *      Author: luclaptop
 */

#ifndef ACCEL_H_
#define ACCEL_H_

#include "I2C.h"

#define ACCEL_ADDR 0x1D
#define ACCEL_WHO_AM_I 0x0F
#define ACCEL_CTRL_1 0x20
#define ACCEL_CTRL_2 0x21

#define ACCEL_CONFIG_CTRL_1 0b01010111

#define ACCEL_OUT_X_L_A 0x28

#define AODR_3HZ 1
#define AODR_6HZ 2
#define AODR_12HZ 3
#define AODR_25HZ 4
#define AODR_50HZ 5
#define AODR_100HZ 6
#define AODR_200HZ 7
#define AODR_400HZ 8
#define AODR_800HZ 9
#define AODR_1600HZ 10

typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
} accel_data_t;

void accel_config();
void accel_get_value(accel_data_t* accel);
uint8_t accel_get_who_am_i();
void accel_set_frequency(uint8_t f);

#endif /* ACCEL_H_ */
