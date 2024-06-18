/*
 * CANOPEN.h
 *
 *  Created on: Apr 14, 2022
 *      Author: luclaptop
 */

#ifndef CANOPEN_H_
#define CANOPEN_H_

#include "CAN.h"

#define CANOPEN_NMT_FUNCTION_ENTER_OP 0x01
#define CANOPEN_NMT_FUNCTION_STOP 0x02
#define CANOPEN_NMT_FUNCTION_ENTER_PREOP 0x80

#define CANOPEN_NMT_STATE_OPE 0x05
#define CANOPEN_NMT_STATE_STOP 0x04
#define CANOPEN_NMT_STATE_PREOP 0x7F

#define CANOPEN_TRANSMIT_PDO1 0b0011
#define CANOPEN_PDO_FUNCTION_CODE 7

#define CANOPEN_READ_DIC_REQUEST_CMD 0x40

#define CANOPEN_READ_DIC_RESPONSE_CMD_4BYTES 0x43
#define CANOPEN_READ_DIC_RESPONSE_CMD_3BYTES 0x47
#define CANOPEN_READ_DIC_RESPONSE_CMD_2BYTES 0x4B
#define CANOPEN_READ_DIC_RESPONSE_CMD_1BYTES 0x4F

#define CANOPEN_WRITE_DIC_REQUEST_CMD_4BYTES 0x23
#define CANOPEN_WRITE_DIC_REQUEST_CMD_3BYTES 0x27
#define CANOPEN_WRITE_DIC_REQUEST_CMD_2BYTES 0x2B
#define CANOPEN_WRITE_DIC_REQUEST_CMD_1BYTES 0x2F

#define CANOPEN_WRITE_DIC_RESPONSE_CMD 0x60

#define CANOPEN_SERVICE_ERROR_CLASS 0x05
#define CANOPEN_ACCESS_ERROR_CLASS 0x06
#define CANOPEN_OTHER_ERROR_CLASS 0x08

#define CANOPEN_INCONSISTENT_PARAMS_ERROR_CODE 0x03
#define CANOPEN_ILLEGAL_PARAM_ERROR_CODE 0x04
#define CANOPEN_OBJ_INEXISTANT_ERROR_CODE 0x02
#define CANOPEN_OBJ_ACCESS_DENIED_ERROR_CODE 0x01
#define CANOPEN_HARDFAULT_ERROR_CODE 0x06

enum type {type_uint8, type_uint16, type_uint32, type_int16, type_array, type_string4};
enum access {access_const, access_RO, access_RW};

typedef struct {
	uint16_t index;
	uint8_t sub_index;
	char* name;
	enum type t;
	enum access a;
	void* default_value;
} dic_object_t;


void canopen_pdo_send(uint8_t src_address, uint8_t length, uint8_t data[]);
void canopen_nmt_master_send(uint8_t nmt_function, uint8_t slave_address);
void canopen_nmt_slave_send(uint8_t nmt_state, uint8_t src_address);
void canopen_sdo_expedited_read_dictionary_object_request(uint8_t node_address, uint16_t index, uint8_t sub_index);
void canopen_sdo_expedited_read_dictionary_object_response(uint8_t node_address, uint8_t read_response_cmd_code, uint16_t index, uint8_t sub_index, uint8_t data[]);
void canopen_sdo_expedited_write_dictionary_object_request(uint8_t node_address, uint8_t write_request_cmd_code, uint16_t index, uint8_t sub_index, uint8_t data[]);
void canopen_sdo_expedited_write_dictionary_object_response(uint8_t node_address, uint16_t index, uint8_t sub_index);
void canopen_sdo_server_abort(uint8_t node_address, uint16_t index, uint8_t sub_index,uint8_t error_code, uint8_t error_class);
void canopen_sdo_client_abort(uint8_t node_address, uint16_t index, uint8_t sub_index,uint8_t error_code, uint8_t error_class);

#endif /* CANOPEN_H_ */
