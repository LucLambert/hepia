/*
 * I2C.h
 *
 *  Created on: Mar 19, 2022
 *      Author: luclaptop
 */

#ifndef I2C_H_
#define I2C_H_

#include "LPC17xx.h"

typedef struct i2c_transaction {
	uint8_t slave_addr;
	uint8_t data_write_len;
	uint8_t data_read_len;
	uint8_t data_ptr;
	uint8_t transaction_done;
	uint8_t data[32];
} i2c_transaction_t;

void i2c_config();
void I2C0_IRQHandler(void);
void i2c_start_transaction();
void i2c_write_register(uint8_t slave_addr, uint8_t reg_addr, uint8_t data);
void i2c_read_registers(uint8_t slave_addr, uint8_t reg_addr, uint8_t data[], uint8_t length);

#endif /* I2C_H_ */
