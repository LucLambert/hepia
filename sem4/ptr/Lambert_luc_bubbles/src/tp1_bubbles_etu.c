/**
 * Name        : tp1_bubbles_etu.c
 * Created on  : 2021
 * Author	   : VP
 * Description : Template of bubbles game. FreeRTOS in cooperative mode.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cr_section_macros.h>
#include <stdio.h>
#include "traces_ref.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "ethmac.h"
#include "ethernet_mgt.h"
#include "lcd.h"
#include "custom_rand.h"
#include "sprites.h"
#include "display.h"
#include "collisions.h"
#include "bubbles.h"

#define BOUTON_A (LPC_GPIO2->FIOPIN & (1<<10))==0 ? 1 : 0
#define BOUTON_B (LPC_GPIO0->FIOPIN & (1<<19))==0 ? 1 : 0
#define JOYSTICK_E (LPC_GPIO1->FIOPIN & (1<<21))==0 ? 1 : 0
#define JOYSTICK_O (LPC_GPIO1->FIOPIN & (1<<23))==0 ? 1 : 0


master_tx_t master_tx[2];
slave_rx_t slave_rx[2];
master_tx_t *master_tx_ptr;	// MUST BE global

const sprite_t bubble_sprite_template={{LCD_MAX_WIDTH/2,LCD_MAX_HEIGHT/2-1},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT/2-1},{0,0}, BUBBLE_SIZE, BUBBLE_SIZE,
		18, 0, {bubble1a, bubble1a, bubble1b, bubble1a, bubble1c, bubble1a, bubble1d, bubble1a, bubble1e,
				bubble1a, bubble2, bubble3, bubble4, bubble5, bubble6, bubble7, bubble8, bubble9},
		NONE, BUBBLE_DELAY, 0, SCORE_HEIGHT, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-1, true};
const sprite_t racket_sprite_template={{LCD_MAX_WIDTH/2,LCD_MAX_HEIGHT-RACKET_HEIGHT-1},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT-RACKET_HEIGHT-1},{0,0}, RACKET_WIDTH, RACKET_HEIGHT,
		 1, 0, {racket_sprite}, NONE, RACKET_DELAY,	0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT, true};

sprite_t my_bubble={{LCD_MAX_WIDTH/2,LCD_MAX_HEIGHT/2-1},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT/2-1},{1,1}, BUBBLE_SIZE, BUBBLE_SIZE,
		18, 0, {bubble1a, bubble1a, bubble1b, bubble1a, bubble1c, bubble1a, bubble1d, bubble1a, bubble1e,
				bubble1a, bubble2, bubble3, bubble4, bubble5, bubble6, bubble7, bubble8, bubble9},
		NONE, BUBBLE_DELAY, 0, SCORE_HEIGHT, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-1, true};

sprite_t my_bubble2={{100,50},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT/2-1},{1,1}, BUBBLE_SIZE, BUBBLE_SIZE,
		18, 0, {bubble1a, bubble1a, bubble1b, bubble1a, bubble1c, bubble1a, bubble1d, bubble1a, bubble1e,
				bubble1a, bubble2, bubble3, bubble4, bubble5, bubble6, bubble7, bubble8, bubble9},
		NONE, BUBBLE_DELAY, 0, SCORE_HEIGHT, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-1, true};

sprite_t my_bubble3={{50,100},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT/2-1},{1,-1}, BUBBLE_SIZE, BUBBLE_SIZE,
		18, 0, {bubble1a, bubble1a, bubble1b, bubble1a, bubble1c, bubble1a, bubble1d, bubble1a, bubble1e,
				bubble1a, bubble2, bubble3, bubble4, bubble5, bubble6, bubble7, bubble8, bubble9},
		GREEN, BUBBLE_DELAY, 0, SCORE_HEIGHT+13, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-13, true};

sprite_t my_bubble4={{200,10},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT/2-1},{-1,1}, BUBBLE_SIZE, BUBBLE_SIZE,
		18, 0, {bubble1a, bubble1a, bubble1b, bubble1a, bubble1c, bubble1a, bubble1d, bubble1a, bubble1e,
				bubble1a, bubble2, bubble3, bubble4, bubble5, bubble6, bubble7, bubble8, bubble9},
		NONE, BUBBLE_DELAY, 0, SCORE_HEIGHT, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-1, true};

sprite_t my_bubble5={{200,300},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT/2-1},{-1,-1}, BUBBLE_SIZE, BUBBLE_SIZE,
		18, 0, {bubble1a, bubble1a, bubble1b, bubble1a, bubble1c, bubble1a, bubble1d, bubble1a, bubble1e,
				bubble1a, bubble2, bubble3, bubble4, bubble5, bubble6, bubble7, bubble8, bubble9},
		NONE, BUBBLE_DELAY, 0, SCORE_HEIGHT, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-1, true};

sprite_t my_bubble6={{150,150},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT/2-1},{-1,1}, BUBBLE_SIZE, BUBBLE_SIZE,
		18, 0, {bubble1a, bubble1a, bubble1b, bubble1a, bubble1c, bubble1a, bubble1d, bubble1a, bubble1e,
				bubble1a, bubble2, bubble3, bubble4, bubble5, bubble6, bubble7, bubble8, bubble9},
		NONE, BUBBLE_DELAY, 0, SCORE_HEIGHT, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-1, true};

sprite_t my_racket={{LCD_MAX_WIDTH/2,LCD_MAX_HEIGHT-RACKET_HEIGHT-1},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT-RACKET_HEIGHT-1},{4,0}, RACKET_WIDTH, RACKET_HEIGHT,
		 1, 0, {racket_sprite}, NONE, RACKET_DELAY,	0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT, true};

sprite_t my_racket2={{LCD_MAX_WIDTH/2,12},{LCD_MAX_WIDTH/2-1,LCD_MAX_HEIGHT-RACKET_HEIGHT-1},{4,0}, RACKET_WIDTH, RACKET_HEIGHT,
		 1, 0, {racket_sprite}, NONE, RACKET_DELAY,	0, 0, LCD_MAX_WIDTH, LCD_MAX_HEIGHT, true};

sprite_t sprites[NB_SPRITES];	// 2 rackets, 6 bubbles. The third bubble boosts the speed of the others in case of collision

int time_b_pressed=0;
int score[2];
xSemaphoreHandle sem;
slave_rx_t* packet_r;

void send_info_to_slave(sprite_t *sprite, int sprite_idx)
{
	//...
	master_tx_ptr->bmp_idx=sprite->bmp_idx;
	master_tx_ptr->color=sprite->color;
	if(score[0] != 3 && score[1] != 3)
		master_tx_ptr->game_started=1;
	else
		master_tx_ptr->game_started=0;
	master_tx_ptr->scores[0]=score[0];
	master_tx_ptr->scores[1]=score[1];
	master_tx_ptr->sprite_active=sprite->active;
	master_tx_ptr->sprite_idx=sprite_idx;
	master_tx_ptr->sprite_pos.x=sprite->pos.x;
	master_tx_ptr->sprite_pos.y=sprite->pos.y;
	master_tx_ptr=(master_tx_t *)send_eth(sizeof(master_tx_t), true);
}


/* Description: Callback of ethernet module. This function is called when a message is received
 * Parameters: data: pointer on data received
 *             len: length of the data [bytes]
 */
void slave_info_rx(void *data, int len)
{
	packet_r=(slave_rx_t*)data;
}

void random_movement_bubble(sprite_t* s){
	uint8_t other_case=1;
	if(rnd32()%32==1){
		if(s->speed.x > 4){
			other_case=0;
			s->speed.x-=1;
		}
		else if (s->speed.x < -4){
			other_case=0;
			s->speed.x+=1;
		}

		if(s->speed.y > 4){
			other_case=0;
			s->speed.y-=1;
		}
		else if (s->speed.y < -4){
			other_case=0;
			s->speed.y+=1;
		}

		if(other_case){
			do{
				if(rnd32()%2){
					s->speed.x+=rnd32()%3-1;
				}else{
					s->speed.y+=rnd32()%3-1;
				}
				if(s->speed.x > 4){
					s->speed.x=4;
				}
				else if (s->speed.x < -4){
					s->speed.x=-4;
				}

				if(s->speed.y > 4){
					s->speed.y=4;
				}
				else if (s->speed.y < -4){
					s->speed.y=-4;
				}
			}while(s->speed.y==0 && s->speed.x==0);
		}
	}
}

void collision_handle(sprite_t* s,int id, int* p){
	int collision = test_collision(id, sprites, 0, 8);
	sprite_t* s1;
	if(s->active){

	switch(collision){
			case 0:
			case 1:
				s1=&sprites[collision];
				if(s1->color==RED){
					s->speed.x= s->speed.x>0 ? -6 : 6;
					s->speed.y= s->speed.y>0 ? -6 : 6;
				}else{
					s->speed.y=-s->speed.y;
				}
				break;
			case WEST_COLLISION:
			case EAST_COLLISION:
				s->speed.x=-s->speed.x;
				break;
			case 4:
				s->speed.y =-(2*s->speed.y);
				s->speed.y = s->speed.y > 6 ? 6 : s->speed.y;
				s->speed.y = s->speed.y < -6 ? -6 : s->speed.y;
				s->speed.x =-(2*s->speed.x);
				s->speed.x = s->speed.x > 6 ? 6 : s->speed.x;
				s->speed.x = s->speed.x < -6 ? -6 : s->speed.x;
				break;
			case 2:
			case 3:
			case 5:
			case 6:
			case 7:
				s->speed.x=-s->speed.x;
				s->speed.y=-s->speed.y;
				break;
			case NO_COLLISION:
				random_movement_bubble(s);
				break;
			case NORTH_COLLISION:
			case SOUTH_COLLISION:
				if(id!=4){
					*p=2;
					if(NORTH_COLLISION==collision)
						score[0]++;
					else
						score[1]++;
					s->speed.x=0;
					s->speed.y=0;
					s->bmp_idx=10;
					s->active=0;
				}else{
					s->speed.x=-s->speed.x;
					s->speed.y=-s->speed.y;
				}
				break;
		}
	}
}

void display_bubble(void* args){
	int* id_p = (int*)args;
	int id=*id_p;
	int periode=0;
	sprite_t* s = &sprites[id];
	while(1){
		if(score[0]==3 || score[1]==3){
			xSemaphoreTake(sem,portMAX_DELAY);
		}
		s->old_pos.x=s->pos.x;
		s->old_pos.y=s->pos.y;
		s->pos.x+=s->speed.x;
		s->pos.y+=s->speed.y;

		int x_erase, y_erase;

		if(s->old_pos.x + s->width < 0)
			x_erase=0;
		else if(s->old_pos.x+ s->width >= LCD_MAX_WIDTH)
			x_erase=LCD_MAX_WIDTH-1;
		else
			x_erase=s->old_pos.x+s->width;

		if(s->old_pos.y + s->height < 0)
			y_erase=0;
		else if(s->old_pos.y+ s->height >= LCD_MAX_HEIGHT)
			y_erase=LCD_MAX_HEIGHT-1;
		else
			y_erase=s->old_pos.y+s->height;

		if(!s->active){
			if(periode%3==0)
				s->bmp_idx++;
			if(s->bmp_idx>=18){
				lcd_print(0, 0, SMALLFONT, LCD_WHITE, LCD_BLACK, "Player 1: %d Player 2: %d", score[0],score[1]);
				lcd_filled_rectangle(s->pos.x, s->pos.y, x_erase, y_erase, LCD_BLACK);
				xSemaphoreTake(sem,portMAX_DELAY);
				s->bmp_idx=0;
			}
		}else{
			collision_handle(s,id,&periode);
			if(periode%3==0){
				s->bmp_idx=(s->bmp_idx+1)%10;
			}
			if(id != 4){
				if(s->speed.x>4 || s->speed.x<-4 || s->speed.y>4 || s->speed.y<-4){
					s->color=RED;
				}else{
					s->color=NONE;
				}
			}
			lcd_filled_rectangle(s->old_pos.x, s->old_pos.y, x_erase, y_erase, LCD_BLACK);
		}
		display_bitmap16_special(s->bmp[s->bmp_idx], s->pos.x, s->pos.y, s->width, s->height, s->color);
		int cpt=0;
		for(int i=2; i<8;i++){
			if(!sprites[i].active)
				cpt++;
		}
		send_info_to_slave(s, id);
		vTaskDelay(s->period-cpt);
		periode++;
	}
}


void display_racket_master(void* args){
	int* id_p = (int*)args;
	int id=*id_p;
	sprite_t* s = &sprites[id];
	while(1){
		s->old_pos.x=s->pos.x;
		s->old_pos.y=s->pos.y;
		if(JOYSTICK_E){
			s->pos.x+=s->speed.x;
			if(s->pos.x>LCD_MAX_WIDTH-1-s->width)
				s->pos.x=LCD_MAX_WIDTH-1-s->width;
		}else if(JOYSTICK_O){
			s->pos.x-=s->speed.x;
			if(s->pos.x<0)
				s->pos.x=0;
		}
		if(BOUTON_B){
			s->color=RED;
			time_b_pressed=xTaskGetTickCount();
		}else{
			if(time_b_pressed+300<=xTaskGetTickCount()){
				s->color=NONE;
			}
		}
		int x_erase, y_erase;
		if(s->old_pos.x + s->width < 0)
			x_erase=0;
		else if(s->old_pos.x+ s->width >= LCD_MAX_WIDTH)
			x_erase=LCD_MAX_WIDTH-1;
		else
			x_erase=s->old_pos.x+s->width;

		if(s->old_pos.y + s->height < 0)
			y_erase=0;
		else if(s->old_pos.y+ s->height >= LCD_MAX_HEIGHT)
			y_erase=LCD_MAX_HEIGHT-1;
		else
			y_erase=s->old_pos.y+s->height;

		if(score[0]==3 || score[1]==3){
			lcd_filled_rectangle(0, 120, 239, 200, LCD_BLACK);
			lcd_filled_rectangle(0, 0, 239, 12, LCD_BLACK);
			if(score[0]==3){
				lcd_print(80, 140, SMALLFONT, LCD_WHITE, LCD_BLACK, "Player 1 win");
			}
			else if(score[1]==3){
				lcd_print(80, 140, SMALLFONT, LCD_WHITE, LCD_BLACK, "Player 2 win");
			}
			lcd_print(60,160,SMALLFONT, LCD_WHITE,LCD_BLACK,"press A to rematch");
			while(!BOUTON_A);
			lcd_filled_rectangle(0, 0, LCD_MAX_WIDTH-1, LCD_MAX_HEIGHT-1, LCD_BLACK);
			score[0]=0;
			score[1]=0;
			lcd_print(0, 0, SMALLFONT, LCD_WHITE, LCD_BLACK, "Player 1: %d Player 2: %d", 0,0);
			for(int i=2;i<8;i++){
				sprites[i].bmp_idx=0;
				sprites[i].speed.x=rnd32()%3-1;
				sprites[i].speed.y=rnd32()%3-1;
				sprites[i].active=1;
				sprites[i].pos.x=(i-2)*240/6;
				sprites[i].pos.y=(uint16_t)(140+((double)rnd32()*40/0xFFFFFFFF));
			}
			for(int i=0;i<6;i++){
				xSemaphoreGive(sem);
			}
		}

		lcd_filled_rectangle(s->old_pos.x, s->old_pos.y, x_erase, y_erase, LCD_BLACK);
		display_bitmap16_special(s->bmp[0], s->pos.x, s->pos.y, s->width, s->height, s->color);
		send_info_to_slave(s, id);
		vTaskDelay(s->period);
	}
}

void display_racket_slave(void* args){
	int* id_p = (int*)args;
	int id=*id_p;
	sprite_t* s = &sprites[id];
	while(1){
		s->old_pos.x=s->pos.x;
		s->old_pos.y=s->pos.y;
		if((packet_r->gpio1 & (1<<21))==0){
			s->pos.x+=s->speed.x;
			if(s->pos.x>LCD_MAX_WIDTH-1-s->width)
				s->pos.x=LCD_MAX_WIDTH-1-s->width;
		}else if((packet_r->gpio1 & (1<<23))==0){
			s->pos.x-=s->speed.x;
			if(s->pos.x<0)
				s->pos.x=0;
		}
		if(packet_r->button_b){
			s->color=RED;
			time_b_pressed=xTaskGetTickCount();
		}else{
			if(time_b_pressed+300<=xTaskGetTickCount()){
				s->color=NONE;
			}
		}
		int x_erase, y_erase;
		if(s->old_pos.x + s->width < 0)
			x_erase=0;
		else if(s->old_pos.x+ s->width >= LCD_MAX_WIDTH)
			x_erase=LCD_MAX_WIDTH-1;
		else
			x_erase=s->old_pos.x+s->width;

		if(s->old_pos.y + s->height < 0)
			y_erase=0;
		else if(s->old_pos.y+ s->height >= LCD_MAX_HEIGHT)
			y_erase=LCD_MAX_HEIGHT-1;
		else
			y_erase=s->old_pos.y+s->height;

		lcd_filled_rectangle(s->old_pos.x, s->old_pos.y, x_erase, y_erase, LCD_BLACK);
		display_bitmap16_special(s->bmp[0], s->pos.x, s->pos.y, s->width, s->height, s->color);
		send_info_to_slave(s, id);
		vTaskDelay(s->period);
	}
}

void init_gpio(){
	LPC_GPIO0->FIODIR&=~(1<<19);
	LPC_GPIO1->FIODIR&=~((1<<21) | (1<<23));
	LPC_GPIO2->FIODIR&=~(1<<10);
}


int main(void)
{
	init_rnd32(1);
	init_lcd();
	clear_screen(LCD_BLACK);
	init_gpio();

	init_traces(230400, 1, true, true);  // or 256000 bds if Windows collects the traces

	// WARNING: if Ethernet is initialized in the main(), the callback could possibly be called BEFORE
	// the launch of the RTOS. This could be an issue if RTOS primitives are used in the callback.
	master_tx_ptr=(master_tx_t *)ethernet_init((unsigned char *)master_tx, 2*sizeof(master_tx_t), (unsigned char *)&slave_rx, 2*sizeof(slave_rx_t), slave_info_rx);

	static int tab[8] = {0,1,2,3,4,5,6,7};
	static void* args_p[8]={&tab[0], &tab[1], &tab[2],&tab[3],&tab[4],&tab[5],&tab[6],&tab[7]};

	sprites[2]=my_bubble;
	sprites[3]=my_bubble2;
	sprites[4]=my_bubble3;
	sprites[5]=my_bubble4;
	sprites[6]=my_bubble5;
	sprites[7]=my_bubble6;
	for(int i=2;i<8;i++){
		sprites[i].pos.x=(i-2)*240/6;
		sprites[i].pos.y=(uint16_t)(140+((double)rnd32()*40/0xFFFFFFFF));
	}
	sprites[0]=my_racket;
	sprites[1]=my_racket2;

	score[0]=0;
	score[1]=0;
	lcd_print(20, 160, SMALLFONT, LCD_WHITE, LCD_BLACK, "Press A to start the game !", 0,0);

	sem=xSemaphoreCreateCounting(4,0);
	while(!BOUTON_A);
	lcd_filled_rectangle(0, 120, 239, 200, LCD_BLACK);
	lcd_print(0, 0, SMALLFONT, LCD_WHITE, LCD_BLACK, "Player 1: %d Player 2: %d", 0,0);

	if(xTaskCreate(display_racket_master, (signed portCHAR *)"display_racket_master", configMINIMAL_STACK_SIZE, args_p[0], tskIDLE_PRIORITY+2, NULL)!=pdPASS) {return 1;}
	if(xTaskCreate(display_racket_slave, (signed portCHAR *)"display_racket_slave", configMINIMAL_STACK_SIZE, args_p[1], tskIDLE_PRIORITY+2, NULL)!=pdPASS) {return 1;}
	if(xTaskCreate(display_bubble, (signed portCHAR *)"display_sprite", configMINIMAL_STACK_SIZE, args_p[2], tskIDLE_PRIORITY+1, NULL)!=pdPASS) {return 1;}
	if(xTaskCreate(display_bubble, (signed portCHAR *)"display_sprite", configMINIMAL_STACK_SIZE, args_p[3], tskIDLE_PRIORITY+1, NULL)!=pdPASS) {return 1;}
	if(xTaskCreate(display_bubble, (signed portCHAR *)"display_sprite", configMINIMAL_STACK_SIZE, args_p[4], tskIDLE_PRIORITY+1, NULL)!=pdPASS) {return 1;}
	if(xTaskCreate(display_bubble, (signed portCHAR *)"display_sprite", configMINIMAL_STACK_SIZE, args_p[5], tskIDLE_PRIORITY+1, NULL)!=pdPASS) {return 1;}
	if(xTaskCreate(display_bubble, (signed portCHAR *)"display_sprite", configMINIMAL_STACK_SIZE, args_p[6], tskIDLE_PRIORITY+1, NULL)!=pdPASS) {return 1;}
	if(xTaskCreate(display_bubble, (signed portCHAR *)"display_sprite", configMINIMAL_STACK_SIZE, args_p[7], tskIDLE_PRIORITY+1, NULL)!=pdPASS) {return 1;}

	vTaskStartScheduler();

	while(1){}

	return 1;
}

