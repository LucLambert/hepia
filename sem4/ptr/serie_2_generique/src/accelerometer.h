/*****************************************************************************

This software is released under the LGPL-3.0 license: http://www.opensource.org/licenses/lgpl-3.0.html

Copyright (c) 2013, hepia (ITI) http://www.hepialight.ch

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3.0 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*****************************************************************************/


#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <stdint.h>

#define accel_addr_X  0x00
#define accel_addr_Y  0x01
#define accel_addr_Z  0x02
#define accel_mode_reg 0x07

#define ACCEL_INT_PIN 11
#define ACCEL_I2C_ADDR 0x1D<<1

#define LSM303D_REG_WHOAMI 0x0F
#define LSM303D_REG_CTRL0 0x1F
#define LSM303D_REG_CTRL1 0x20
#define LSM303D_REG_CTRL2 0x21
#define LSM303D_REG_CTRL3 0x22
#define LSM303D_REG_CTRL4 0x23
#define LSM303D_REG_CTRL5 0x24
#define LSM303D_REG_CTRL6 0x25
#define LSM303D_REG_CTRL7 0x26
#define LSM303D_REG_TEMP_OUT_L 0x05
#define LSM303D_REG_TEMP_OUT_H 0x06
#define LSM303D_REG_STATUS_M 0x07
#define LSM303D_REG_OUT_X_L_M 0x08
#define LSM303D_REG_OUT_X_H_M 0x09
#define LSM303D_REG_OUT_Y_L_M 0x0a
#define LSM303D_REG_OUT_Y_H_M 0x0b
#define LSM303D_REG_OUT_Z_L_M 0x0c
#define LSM303D_REG_OUT_Z_H_M 0x0d
#define LSM303D_REG_STATUS_A 0x27
#define LSM303D_REG_OUT_X_L_A 0x28
#define LSM303D_REG_OUT_X_H_A 0x29
#define LSM303D_REG_OUT_Y_L_A 0x2a
#define LSM303D_REG_OUT_Y_H_A 0x2b
#define LSM303D_REG_OUT_Z_L_A 0x2c
#define LSM303D_REG_OUT_Z_H_A 0x2d

#define ACC_NOT_INITIALISED -21
#define ACC_INIT_I2C_FAILED -22
#define ACC_NOERROR          0


typedef struct
{
	float accel_x;
	float accel_y;
	float accel_z;
	int16_t magneto_x;
	int16_t magneto_y;
	int16_t magneto_z;
	int16_t temperature;
} accel_t;

int accel_init(void);

/*
 * Accelerometer reading. each component read has a value in the range [-1, 1]
 * Parameter: accel: pointer on (x,y,z) acceleration to be returned
 * Return: ACC_NOERROR if no error or error code
 */
int accel_read(accel_t *accel);


#endif /* ACCELEROMETER_H_ */
