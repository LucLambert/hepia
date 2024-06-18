/*
 * bootloader_protocol.c
 *
 *  Created on: May 5, 2022
 *      Author: luclaptop
 */
#include "bootloader_protocol.h"

uint8_t is_GETID(char cmd[]){
	char s[5]={'G','E','T','I','D'};
	for(int i=0; i<5;i++){
		if(s[i]!=cmd[i])
			return 0;
	}
	return 1;
}

uint8_t is_GETSERIAL(char cmd[]){
	char s[9]={'G','E','T','S','E','R','I','A','L'};
	for(int i=0; i<9;i++){
		if(s[i]!=cmd[i])
			return 0;
	}
	return 1;
}

uint8_t is_DATA(char cmd[]){
	char s[4]={'D','A','T','A'};
	for(int i=0; i<4;i++){
		if(s[i]!=cmd[i])
			return 0;
	}
	return 1;
}

uint8_t is_PROG(char cmd[]){
	char s[4]={'P','R','O','G'};
	for(int i=0; i<4;i++){
		if(s[i]!=cmd[i])
			return 0;
	}
	return 1;
}

uint8_t is_CHECK(char cmd[]){
	char s[5]={'C','H','E','C','K'};
	for(int i=0; i<5;i++){
		if(s[i]!=cmd[i])
			return 0;
	}
	return 1;
}

void send_OK(){
	char s[4]="OK\r\n";
	uart_send_str(s,4);
}

void send_ERR(char type_error){
	char s[7]="ERR,0\r\n";
	s[4]=type_error;
	uart_send_str(s,7);
}

void parse_cmd(cmd_t* c){
	char buff[256];
	uint16_t idx_buff=0;

	do{
		buff[idx_buff++]=uart_receive();
		if(buff[idx_buff-1]=='\n')
			if(idx_buff>=2)
				if(buff[idx_buff-2]=='\r')
					break;
	}while(1);

	if(is_GETID(buff)){
		strcpy(c->cmd,buff);
	}else if(is_GETSERIAL(buff)){
		strcpy(c->cmd,buff);
	}else if(is_PROG(buff)){
		   const char s[2] = ",";
		   char *token;
		   token = strtok(buff,s);
		   strcpy(c->cmd,token);
		   int cpt=0;
		   while( token != NULL ) {
		      token = strtok(NULL, s);
		      sscanf(token, "%x", &c->arg[cpt++]);
		   }
	}else if(is_DATA(buff)){
		   const char s[2] = ",";
		   char *token;
		   /* get the first token */
		   token = strtok(buff,s);
		   strcpy(c->cmd,token);
		   int cpt=0;
		   while( token != NULL ) {
		      token = strtok(NULL, s);
		      sscanf(token, "%x", &c->arg[cpt++]);
		   }

	}else if(is_CHECK(buff)){
		strcpy(c->cmd,buff);
	}
}

