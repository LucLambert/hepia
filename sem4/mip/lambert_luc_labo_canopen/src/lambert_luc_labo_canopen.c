/*
===============================================================================
 Name        : lambert_luc_labo_canopen.c
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
#include "CANOPEN.h"
#include "I2C.h"
#include "ACCEL.h"
#include "UART.h"
#include "LCD.h"
#include "SSP.h"
#include <stdio.h>

// TODO: insert other definitions and declarations here
#define SLAVE_ADDR 0x42
#define MASTER_ADDR 0x00

static uint32_t ms_tick=0;
static uint8_t flag_1_sec=0;

void SysTick_Handler(){
	ms_tick++;
	if((ms_tick%1000)==0)
		flag_1_sec=1;
}

void init_sdo_dic(dic_object_t dic[]){

	//item 0
	dic[0].index=0x1000;
	dic[0].sub_index=0x00;
	dic[0].name="Type device";
	dic[0].t=type_uint32;
	dic[0].a=access_const;
	dic[0].default_value=(void*)0x303D1769;

	//item 1
	dic[1].index=0x1001;
	dic[1].sub_index=0x00;
	dic[1].name="Registre erreur";
	dic[1].t=type_uint8;
	dic[1].a=1;
	dic[1].default_value=(void*)0x00;

	//item 2
	dic[2].index=0x1008;
	dic[2].sub_index=0x00;
	dic[2].name="Nom du device";
	dic[2].t=type_string4;
	dic[2].a=access_const;
	dic[2].default_value=(void*)"LL";

	//item 3
	dic[3].index=0x1009;
	dic[3].sub_index=0x00;
	dic[3].name="Version Hardware";
	dic[3].t=type_string4;
	dic[3].a=access_const;
	dic[3].default_value=(void*)"1.3";

	//item 4
	dic[4].index=0x100A;
	dic[4].sub_index=0x00;
	dic[4].name="Version Logiciel";
	dic[4].t=type_string4;
	dic[4].a=access_const;
	dic[4].default_value=(void*)"0.1";

	//item 5
	dic[5].index=0x1017;
	dic[5].sub_index=0x00;
	dic[5].name="Intervalle temps heartbeat (ms)";
	dic[5].t=type_uint16;
	dic[5].a=access_RW;
	dic[5].default_value=(void*)1000;

	//item 6
	dic[6].index=0x2000;
	dic[6].sub_index=0x00;
	dic[6].name="Identifiant nœud";
	dic[6].t=type_uint8;
	dic[6].a=access_RW;
	dic[6].default_value=(void*)0x42;

	//item 7
	dic[7].index=0x2001;
	dic[7].sub_index=0x00;
	dic[7].name="Baudrate CAN";
	dic[7].t=type_uint8;
	dic[7].a=access_RW;
	dic[7].default_value=(void*)0x03;

	//item 8
	dic[8].index=0x5000;
	dic[8].sub_index=0x00;
	dic[8].name="Intervalle temps accéléromètre (ms)";
	dic[8].t=type_uint16;
	dic[8].a=access_RW;
	dic[8].default_value=(void*)32;

	//item 9
	dic[9].index=0x5E00;
	dic[9].sub_index=0x00;
	dic[9].name="Mesure courantes de l'accéléromètre";
	dic[9].t=type_array;
	dic[9].a=access_RO;

	//item 10
	dic[10].index=0x5E00;
	dic[10].sub_index=0x01;
	dic[10].name="- Axe X (0.001g / bit)";
	dic[10].t=type_int16;
	dic[10].a=access_RO;

	//item 11
	dic[11].index=0x5E00;
	dic[11].sub_index=0x02;
	dic[11].name="- Axe Y";
	dic[11].t=type_int16;
	dic[11].a=access_RO;

	//item 12
	dic[12].index=0x5E00;
	dic[12].sub_index=0x03;
	dic[12].name="- Axe Z";
	dic[12].t=type_int16;
	dic[12].a=access_RO;
}

static uint16_t cpt_lines=319;
void display_scroll_accel_values(int16_t x_a, int16_t y_a, int16_t z_a){
	int16_t x_u,y_u,z_u=0;
	x_u=(x_a+1000)*240/2000;
	y_u=(y_a+1000)*240/2000;
	z_u=(z_a+1000)*240/2000;
	x_u=x_u > 239 ? 239 : x_u;
	x_u=x_u < 0 ? 0 : x_u;
	y_u=y_u > 239 ? 239 : y_u;
	y_u=y_u < 0 ? 0 : y_u;
	z_u=z_u > 239 ? 239 : z_u;
	z_u=z_u < 0 ? 0 : z_u;

	draw_line(0, 239, cpt_lines+319, cpt_lines+319, RGB(0,0,0));
	set_pix(120,cpt_lines+319,RGB(255,255,255));
	set_pix(x_u,cpt_lines+319,RGB(255,0,0));
	set_pix(y_u,cpt_lines+319,RGB(0,255,0));
	set_pix(z_u,cpt_lines+319,RGB(0,0,255));
	lcd_scroll(cpt_lines);
	cpt_lines= (cpt_lines + 1)% 320;
}

void set_accel_frequency(uint16_t p){ //periode en ms
	switch(p){
		case 1:
			accel_set_frequency(AODR_1600HZ);
			break;
		case 2:
			accel_set_frequency(AODR_800HZ);
			break;
		case 4:
			accel_set_frequency(AODR_400HZ);
			break;
		case 8:
			accel_set_frequency(AODR_200HZ);
			break;
		case 16:
			accel_set_frequency(AODR_100HZ);
			break;
		case 32:
			accel_set_frequency(AODR_50HZ);
			break;
		case 64:
			accel_set_frequency(AODR_25HZ);
			break;
		case 128:
			accel_set_frequency(AODR_12HZ);
			break;
		case 256:
			accel_set_frequency(AODR_6HZ);
			break;
		case 512:
			accel_set_frequency(AODR_3HZ);
			break;
	}
}

int main(void) {

    // TODO: insert code here
	uint8_t first_step_master=1;
	uint8_t first_step_slave=1;
	uint32_t timestamp, timestamp2=0;

	can_config();

	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000); // execute systick handler every 1ms

	uint8_t data[6];
	int16_t x,y,z=0;
	accel_data_t accel_data;
	uint8_t slave_state=CANOPEN_NMT_STATE_PREOP;

	const uint8_t dic_len = 13;
	dic_object_t dic[dic_len];
	init_sdo_dic(dic);

	uint32_t receive_timed_msg;
	uint8_t lock_A=1;
	uint32_t lock_A_time=0;
	uint8_t lock_B=1;
	uint32_t lock_B_time=0;
	uint32_t display_time=0;

    while(1) {

    	while(!(LPC_GPIO2->FIOPIN & 1)){ // master
    		if(first_step_master){
    			ssp_config();
    			init_LCD();
    			fill_screen(RGB(0,0,0));
    			LPC_GPIO2->FIODIR=(1<<7); // set gpio 2.7 output
    			first_step_master=0;
    		}
    		if((display_time + (uint16_t)dic[8].default_value)<ms_tick && slave_state==CANOPEN_NMT_STATE_OPE){
    			display_time=ms_tick;
    			display_scroll_accel_values(x, y, z);
    		}

    		if(can_flag_receive){
    			receive_timed_msg=ms_tick;
    			LPC_GPIO2->FIOCLR=(1<<7);
    			can_msg_t msg;
    			can_receive(&msg);
    			switch(msg.id){
    				case (0x700 + SLAVE_ADDR): // heartbeat slave
    					slave_state=msg.data[0];
    					switch(slave_state){
    							case CANOPEN_NMT_STATE_PREOP:
    								canopen_nmt_master_send(CANOPEN_NMT_FUNCTION_ENTER_OP, SLAVE_ADDR);
    								break;
    							case CANOPEN_NMT_STATE_OPE:
    								break;
    							}
    					break;
    				case((CANOPEN_TRANSMIT_PDO1<<CANOPEN_PDO_FUNCTION_CODE) | (SLAVE_ADDR)): //pdo
    					x=(msg.data[0]|(msg.data[1]<<8));
    					y=(msg.data[2]|(msg.data[3]<<8));
    					z=(msg.data[4]|(msg.data[5]<<8));
    					break;
    			}
    		}else if((receive_timed_msg + (uint16_t)dic[5].default_value) < ms_tick){
    			LPC_GPIO2->FIOSET=(1<<7);
    			slave_state=CANOPEN_NMT_STATE_PREOP;
    		}
    		if(!(LPC_GPIO2->FIOPIN & (1<<10))&&lock_A){ //btn A
    			uint8_t data[2];
    			uint16_t a = (uint16_t)dic[8].default_value;
    			a=(a>>1);
    			a = a == 0 ? 1 : a;
    			dic[8].default_value=(void*)a;
    			data[0]=(a&0xFF);
    			data[1]=((a>>8)&0xFF);
    			canopen_sdo_expedited_write_dictionary_object_request(SLAVE_ADDR, CANOPEN_WRITE_DIC_REQUEST_CMD_2BYTES, 0x5000, 0x00, data);
    			lock_A=0;
    			lock_A_time=ms_tick;
    		}
    		if(lock_A_time + 250 < ms_tick){
    			lock_A=1;
    		}
    		if(!(LPC_GPIO0->FIOPIN & (1<<19))&&lock_B){ //btn B
    			uint8_t data[2];
    			uint16_t a = (uint16_t)dic[8].default_value;
    			a = a >= 0xFF ? 0x200 : (a<<1);
    			dic[8].default_value=(void*)a;
    			data[0]=(a&0xFF);
    			data[1]=((a>>8)&0xFF);
    			canopen_sdo_expedited_write_dictionary_object_request(SLAVE_ADDR, CANOPEN_WRITE_DIC_REQUEST_CMD_2BYTES, 0x5000, 0x00, data);
    			lock_B=0;
    			lock_B_time=ms_tick;
    		}
    		if(lock_B_time + 250 < ms_tick){
    		    lock_B=1;
    		}
    	}

/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/

    	while((LPC_GPIO2->FIOPIN & 1)){ // slave
    		if(first_step_slave){
    			timestamp=ms_tick;
    			timestamp2=ms_tick;
    			i2c_config();
    			accel_config();
    			first_step_slave=0;
    		}

			if(slave_state==CANOPEN_NMT_STATE_OPE){
				if((timestamp2 + (uint16_t)dic[8].default_value) <= ms_tick){
					timestamp2=ms_tick;
//					printf("%d\n",timestamp2);
					accel_get_value(&accel_data);
					x = (int16_t)((1.0*(accel_data.x+0x7FFF)/0x3FFF -2)*1000);
					y = (int16_t)((1.0*(accel_data.y+0x7FFF)/0x3FFF -2)*1000);
					z = (int16_t)((1.0*(accel_data.z+0x7FFF)/0x3FFF -2)*1000);
					data[0]=(x&0xFF);
					data[1]=(x>>8);
					data[2]=(y&0xFF);
					data[3]=(y>>8);
					data[4]=(z&0xFF);
					data[5]=(z>>8);
					canopen_pdo_send(SLAVE_ADDR, 6, data);
				}
			}

			if(can_flag_receive){
				can_msg_t msg;
				can_receive(&msg);
				uint8_t function=0;
				switch(msg.id){
					case 0: // master send nmt
				    	function=msg.data[0];
				    	switch(function){
				    		case CANOPEN_NMT_FUNCTION_ENTER_OP:
				    			slave_state=CANOPEN_NMT_STATE_OPE;
				    			break;
				    		case CANOPEN_NMT_FUNCTION_ENTER_PREOP:
				    			break;
				    	}
				    	break;
				    case 0x642: //sdo receive
				    	if(msg.data[0]==CANOPEN_WRITE_DIC_REQUEST_CMD_2BYTES){
				    	    canopen_sdo_expedited_write_dictionary_object_response(SLAVE_ADDR, 0x5000, 0x00);
				    	    uint16_t p=(msg.data[4]|(msg.data[5]<<8));
				    	    dic[8].default_value=(void*)p;
				    	    set_accel_frequency(p);
				    	 }
				    	break;
				}
			}

			if((timestamp + (uint16_t)dic[5].default_value) < ms_tick){
				timestamp=ms_tick;
				canopen_nmt_slave_send(slave_state, SLAVE_ADDR);
			}
    	}
    }
    return 0;
}
