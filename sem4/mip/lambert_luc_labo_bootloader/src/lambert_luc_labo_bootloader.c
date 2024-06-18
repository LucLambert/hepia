/*
===============================================================================
 Name        : lambert_luc_labo_bootloader.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "bootloader_protocol.h"
#include "IAP.h"
#include "crc.h"

// TODO: insert other definitions and declarations here
#define LED_7 (1<<7)
#define LED_0 1
#define BTN_B 19
#define APP_INFO_ADDR 0x3000

static uint32_t app_addr = 0;

void init(){

	//btn b entrée
	LPC_GPIO0->FIODIR&=~(1<<BTN_B);
	// leds en sortie
	LPC_GPIO2->FIODIR=0xFF;
	//eteinds toutes les leds
	LPC_GPIO2->FIOCLR=0xFF;

}

void launch_app(int* sp, int* pc){
	//SP should take value of start address
	//PC should take value of start address + 4
	SCB->VTOR+=(int)sp;
	__asm("ldr r0, [r0]");
	__asm("ldr r1, [r1]");
	__asm("str r0, [sp]");
	__asm("bx r1");
}

uint8_t checksum(const void* data, size_t data_len, crc_t crc){
	crc_t c = crc_init();
	c = crc_update(c, data, data_len);
	c = crc_finalize(c);

	if(c != crc)
		return 0;
	return 1;
}


static unsigned int last_sector = 0;
static uint32_t total_received = 0;

void handle_bootloader(){
	cmd_t c;
	parse_cmd(&c);

	if(is_GETID(c.cmd)){
		char s[12+4]={'O','K','\r','\n','0','x','2','6','1','1','3','f','3','7','\r','\n'};
		uart_send_str(s, 12+4);
	}else if(is_GETSERIAL(c.cmd)){
		char s[35+4]={'O','K','\r','\n','0','x','c','0','0','e','0','0','e','a','e','a','b','9','4','a','8','5','5','1','f','0','9','1','1','f','5','0','0','2','0','c','0','\r','\n'};
		uart_send_str(s, 35+4);
	}else if(is_PROG(c.cmd)){

		//write this to flash
		unsigned int start_address = (unsigned int)c.arg;
		volatile iap_status_code code;

		unsigned int sector = iap_get_sector(APP_INFO_ADDR);
		code = iap_prepare_sector(sector,sector);
		if(code != IAP_CMD_SUCCESS){
			send_ERR('6');
		}
		code = iap_erase_sector(sector, sector, SystemCoreClock/1000);
		if(code != IAP_CMD_SUCCESS){
			send_ERR('6');
		}

		code = iap_prepare_sector(sector,sector);
		if(code != IAP_CMD_SUCCESS){
			send_ERR('6');
		}
		code = iap_copy_ram_to_flash(APP_INFO_ADDR, start_address, 3*sizeof(int), SystemCoreClock/1000);


		if(code != IAP_CMD_SUCCESS){
			send_ERR('6');
		}
		else{
			app_addr = c.arg[0];
			send_OK();
		}
	}else if(is_DATA(c.cmd)){

		uint8_t data[4096];
		uart_receive_size(data, c.arg[0]);

		//chekcsum on data
		if(!checksum((void*)data, c.arg[0], c.arg[1])){
			send_ERR('4');
		}else{
			//write data to flash

			volatile iap_status_code code;
			unsigned int dst = app_addr + total_received;
			unsigned int sector = iap_get_sector(dst);

			if(last_sector != sector){
				code = iap_prepare_sector(sector,sector);
				if(code != IAP_CMD_SUCCESS){
					send_ERR('6');
				}
				code = iap_erase_sector(sector, sector, SystemCoreClock/1000);
				if(code != IAP_CMD_SUCCESS){
					send_ERR('6');
				}
			}

			code = iap_prepare_sector(sector,sector);
			if(code != IAP_CMD_SUCCESS){
				send_ERR('6');
			}
			code = iap_copy_ram_to_flash(dst, (int)data, c.arg[0], SystemCoreClock/1000);

			if(code != IAP_CMD_SUCCESS){
				send_ERR('6');
			}else{
				total_received += c.arg[0];
				last_sector = sector;
				send_OK();
			}
		}
	}else if(is_CHECK(c.cmd)){
		//chekcsum all app
		if(checksum((int*)app_addr, *(int*)(APP_INFO_ADDR+4), *(int*)(APP_INFO_ADDR+8))){
			send_OK();
			//reset
			NVIC_SystemReset();
		}else{
			LPC_GPIO2->FIOPIN|=LED_7;
			send_ERR('3');
		}
	}
}

int main(void) {
	init();

	if(!((LPC_GPIO0->FIOPIN>>BTN_B)&1)){ // si btn b
		LPC_GPIO2->FIOPIN|=LED_0;
		uart_config(115200, WORD_LENGTH_8, PARITY_DISABLE, STOP_BIT_1);
	}else{
		app_addr = *(int*)APP_INFO_ADDR;
		if(checksum((int*)app_addr, *(int*)(APP_INFO_ADDR+4), *(int*)(APP_INFO_ADDR+8))){
			launch_app((int*)app_addr,(int*)(app_addr+4));
		}else{
			LPC_GPIO2->FIOPIN|=LED_0;
			uart_config(115200, WORD_LENGTH_8, PARITY_DISABLE, STOP_BIT_1);
		}
	}
	while(1){
		handle_bootloader();
	}
}
