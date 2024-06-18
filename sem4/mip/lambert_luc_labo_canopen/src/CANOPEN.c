/*
 * CANOPEN.c
 *
 *  Created on: Apr 14, 2022
 *      Author: luclaptop
 */

#include "CANOPEN.h"

static dic_object_t d[13];

void canopen_pdo_send(uint8_t src_address, uint8_t length, uint8_t data[]){

	can_msg_t msg;
	msg.id=((CANOPEN_TRANSMIT_PDO1<<CANOPEN_PDO_FUNCTION_CODE) | (src_address));
	msg.rtr=0;
	msg.type=0;
	msg.dlc=length;
	msg.error_msg=0;
	for(int i=0; i<length;i++){
		msg.data[i]=data[i];
	}

	can_send(&msg);
}

void canopen_nmt_master_send(uint8_t nmt_function, uint8_t slave_address){
	can_msg_t msg;
	msg.id=0;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=2;
	msg.error_msg=0;
	msg.data[0]=nmt_function;
	msg.data[1]=slave_address;

	can_send(&msg);
}

void canopen_nmt_slave_send(uint8_t nmt_state, uint8_t src_address){
	can_msg_t msg;
	msg.id= 0x700+src_address;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=1;
	msg.error_msg=0;
	msg.data[0]=nmt_state;

	can_send(&msg);
}

void canopen_sdo_update_dic(dic_object_t dic[]){
	for(int i=0; i < 13; i++){
		d[i]=dic[i];
	}
}

void canopen_sdo_expedited_read_dictionary_object_request(uint8_t node_address, uint16_t index, uint8_t sub_index){
	can_msg_t msg;
	msg.id= 0x600+node_address;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=8;
	msg.error_msg=0;
	msg.data[0]=CANOPEN_READ_DIC_REQUEST_CMD;
	msg.data[1]=(index>>8);
	msg.data[2]=(index&0xFF);
	msg.data[3]=sub_index;

	for(int i=4; i<8; i++){
		msg.data[i]=0;
	}

	can_send(&msg);
}

void canopen_sdo_expedited_read_dictionary_object_response(uint8_t node_address, uint8_t read_response_cmd_code, uint16_t index, uint8_t sub_index, uint8_t data[]){
	can_msg_t msg;
	msg.id= 0x580+node_address;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=8;
	msg.error_msg=0;
	msg.data[0]=read_response_cmd_code;
	msg.data[1]=(index>>8);
	msg.data[2]=(index&0xFF);
	msg.data[3]=sub_index;

	uint8_t data_size=0;
	switch(read_response_cmd_code){
		case CANOPEN_READ_DIC_RESPONSE_CMD_4BYTES:
			data_size=4;
			break;
		case CANOPEN_READ_DIC_RESPONSE_CMD_3BYTES:
			data_size=3;
			break;
		case CANOPEN_READ_DIC_RESPONSE_CMD_2BYTES:
			data_size=2;
			break;
		case CANOPEN_READ_DIC_RESPONSE_CMD_1BYTES:
			data_size=1;
			break;
	}
	for(int i=4; i<(4+data_size); i++){
		msg.data[i]=data[i-4];
	}

	can_send(&msg);
}

void canopen_sdo_expedited_write_dictionary_object_request(uint8_t node_address, uint8_t write_request_cmd_code, uint16_t index, uint8_t sub_index, uint8_t data[]){
	can_msg_t msg;
	msg.id= 0x600+node_address;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=8;
	msg.error_msg=0;
	msg.data[0]=write_request_cmd_code;
	msg.data[1]=(index>>8);
	msg.data[2]=(index&0xFF);
	msg.data[3]=sub_index;

	uint8_t data_size=0;
	switch(write_request_cmd_code){
		case CANOPEN_WRITE_DIC_REQUEST_CMD_4BYTES:
			data_size=4;
			break;
		case CANOPEN_WRITE_DIC_REQUEST_CMD_3BYTES:
			data_size=3;
			break;
		case CANOPEN_WRITE_DIC_REQUEST_CMD_2BYTES:
			data_size=2;
			break;
		case CANOPEN_WRITE_DIC_REQUEST_CMD_1BYTES:
			data_size=1;
			break;
	}
	for(int i=4; i<(4+data_size); i++){
		msg.data[i]=data[i-4];
	}

	can_send(&msg);
}

void canopen_sdo_expedited_write_dictionary_object_response(uint8_t node_address, uint16_t index, uint8_t sub_index){
	can_msg_t msg;
	msg.id= 0x580+node_address;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=8;
	msg.error_msg=0;
	msg.data[0]=CANOPEN_WRITE_DIC_RESPONSE_CMD;
	msg.data[1]=(index>>8);
	msg.data[2]=(index&0xFF);
	msg.data[3]=sub_index;

	for(int i=4; i<8; i++){
		msg.data[i]=0;
	}

	can_send(&msg);
}

void canopen_sdo_server_abort(uint8_t node_address, uint16_t index, uint8_t sub_index,uint8_t error_code, uint8_t error_class){
	can_msg_t msg;
	msg.id= 0x600+node_address;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=8;
	msg.error_msg=0;
	msg.data[0]=error_code;
	msg.data[1]=(index>>8);
	msg.data[2]=(index&0xFF);
	msg.data[3]=sub_index;
	msg.data[4]=0;
	msg.data[5]=0;
	msg.data[6]=error_code;
	msg.data[7]=error_class;

	can_send(&msg);
}

void canopen_sdo_client_abort(uint8_t node_address, uint16_t index, uint8_t sub_index,uint8_t error_code, uint8_t error_class){
	can_msg_t msg;
	msg.id= 0x580+node_address;
	msg.rtr=0;
	msg.type=0;
	msg.dlc=8;
	msg.error_msg=0;
	msg.data[0]=error_code;
	msg.data[1]=(index>>8);
	msg.data[2]=(index&0xFF);
	msg.data[3]=sub_index;
	msg.data[4]=0;
	msg.data[5]=0;
	msg.data[6]=error_code;
	msg.data[7]=error_class;

	can_send(&msg);
}
