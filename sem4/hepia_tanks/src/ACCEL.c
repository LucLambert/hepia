/*
 * ACCEL.c
 *
 *  Created on: Apr 14, 2022
 *      Author: luclaptop
 */

#include "ACCEL.h"

void accel_config(){
	i2c_write_register(ACCEL_ADDR, ACCEL_CTRL_1, ACCEL_CONFIG_CTRL_1);
}

void accel_get_value(accel_data_t* accel){
	uint8_t data[6];
	i2c_read_registers(ACCEL_ADDR,ACCEL_OUT_X_L_A,data,6);
	accel->x=(data[0]|(data[1]<<8));
	accel->y=(data[2]|(data[3]<<8));
	accel->z=(data[4]|(data[5]<<8));
}

uint8_t accel_get_who_am_i(){
	uint8_t data[1];
	i2c_read_registers(ACCEL_ADDR,ACCEL_WHO_AM_I,data,1);
	return data[0];
}

void accel_set_frequency(uint8_t f){
	i2c_write_register(ACCEL_ADDR, ACCEL_CTRL_1, ((f<<4)|0b0111));
}
