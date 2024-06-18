/*
===============================================================================
 Name        : hepia_tanks.c
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
#include "LCD.h"
#include "stdio.h"
#include "ACCEL.h"
#include "I2C.h"

// TODO: insert other definitions and declarations here
typedef struct{
	uint16_t x;
	uint16_t y;
}vec;

typedef struct{
	vec pos;
	vec speed;
	vec size;
}tank;

void handle_tank_movement(tank* t){
	if(!(LPC_GPIO1->FIOPIN>>20 & 1)){ // NORTH
		t->pos.y -= t->speed.y;
	}else if(!(LPC_GPIO1->FIOPIN>>21 & 1)){ // EAST
		t->pos.x += t->speed.x;
	}else if(!(LPC_GPIO1->FIOPIN>>22 & 1)){ // SOUTH
		t->pos.y += t->speed.y;
	}else if(!(LPC_GPIO1->FIOPIN>>23 & 1)){ // WEST
		t->pos.x -= t->speed.x;
	}
}

void display_tank(tank t){
	draw_rect(t.pos.x,t.pos.y,t.size.x,t.size.y,RGB(255,0,255));
}

int main(void) {

    // TODO: insert code here
	ssp_config();
	init_LCD();
	i2c_config();
	accel_config();
	accel_data_t a;

	tank t = {{10,10},{1,1},{25,25}};
	uint16_t x=0;
	uint16_t y=0;
	vec t_center = {t.pos.x + t.size.x/2, t.pos.y+t.size.y/2};
    while(1) {
    	accel_get_value(&a);
    	draw_rect(t.pos.x,t.pos.y,t.size.x,t.size.y,RGB(0,0,0));
    	draw_line(t_center.x, x, t_center.y, y,RGB(0,0,0));
    	set_pix(t_center.x, t_center.y, RGB(0,0,0));
    	set_pix(x, y, RGB(0,0,0));
    	handle_tank_movement(&t);
    	t_center.x = t.pos.x+t.size.x/2;
    	t_center.y = t.pos.y+t.size.y/2;
    	x = (uint16_t)(t_center.x + -8.0*a.y*t.size.x/0x7fff);
    	y = (uint16_t)(t_center.y + 8.0*a.x*t.size.y/0x7fff);
    	draw_line(t_center.x, x, t_center.y, y,RGB(255,255,255));
    	set_pix(t_center.x, t_center.y, RGB(255,0,0));
    	set_pix(x, y, RGB(0,255,0));
    	display_tank(t);
    }

    return 0 ;
}
