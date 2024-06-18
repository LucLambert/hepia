#include "LCD.h"

void Delay(int ms){
	uint32_t stop = LPC_TIM0->TC + 100000*ms;
	while(LPC_TIM0->TC < stop);
}

void Write_Cmd(uint8_t cmd){
	LPC_GPIO1->FIOCLR=1<<30;
	ssp_send_char(cmd);
}

void Write_Cmd_Data(uint8_t cmd){
	LPC_GPIO1->FIOSET=1<<30;
	ssp_send_char(cmd);
}

void Write_Cmd_Data16(uint16_t cmd){
	LPC_GPIO1->FIOSET=1<<30;
	ssp_send_char(cmd>>8);
	ssp_send_char(cmd&0xff);
}

void ILI9341_Initial(void)
{
	Write_Cmd(0x01); //software reset
	Delay(5);

	Write_Cmd(0x11);
	Delay(120);

 	Write_Cmd(0xCF);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x83);
	Write_Cmd_Data(0X30);

 	Write_Cmd(0xED);
	Write_Cmd_Data(0x64);
	Write_Cmd_Data(0x03);
	Write_Cmd_Data(0X12);
	Write_Cmd_Data(0X81);

 	Write_Cmd(0xE8);
	Write_Cmd_Data(0x85);
	Write_Cmd_Data(0x01);
	Write_Cmd_Data(0x79);

 	Write_Cmd(0xCB);
	Write_Cmd_Data(0x39);
	Write_Cmd_Data(0x2C);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x34);
	Write_Cmd_Data(0x02);

 	Write_Cmd(0xF7);
	Write_Cmd_Data(0x20);

 	Write_Cmd(0xEA);
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x00);


 	Write_Cmd(0xC1);    //Power control
	Write_Cmd_Data(0x11);   //SAP[2:0];BT[3:0]

 	Write_Cmd(0xC5);    //VCM control 1
	Write_Cmd_Data(0x34);
	Write_Cmd_Data(0x3D);

 	Write_Cmd(0xC7);    //VCM control 2
	Write_Cmd_Data(0xC0);

 	Write_Cmd(0x36);    // Memory Access Control
	Write_Cmd_Data(0x08);

 	Write_Cmd(0x3A);   	 // Pixel format
	Write_Cmd_Data(0x55);  //16bit

 	Write_Cmd(0xB1);   	   // Frame rate
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x1D);  //65Hz

 	Write_Cmd(0xB6);    // Display Function Control
	Write_Cmd_Data(0x0A);
	Write_Cmd_Data(0xA2);
	Write_Cmd_Data(0x27);
	Write_Cmd_Data(0x00);

	Write_Cmd(0xb7); //Entry mode
	Write_Cmd_Data(0x07);


 	Write_Cmd(0xF2);    // 3Gamma Function Disable
	Write_Cmd_Data(0x08);

 	Write_Cmd(0x26);    //Gamma curve selected
	Write_Cmd_Data(0x01);


	Write_Cmd(0xE0); //positive gamma correction
	Write_Cmd_Data(0x1f);
	Write_Cmd_Data(0x1a);
	Write_Cmd_Data(0x18);
	Write_Cmd_Data(0x0a);
	Write_Cmd_Data(0x0f);
	Write_Cmd_Data(0x06);
	Write_Cmd_Data(0x45);
	Write_Cmd_Data(0x87);
	Write_Cmd_Data(0x32);
	Write_Cmd_Data(0x0a);
	Write_Cmd_Data(0x07);
	Write_Cmd_Data(0x02);
	Write_Cmd_Data(0x07);
	Write_Cmd_Data(0x05);
	Write_Cmd_Data(0x00);

	Write_Cmd(0xE1); //negamma correction
	Write_Cmd_Data(0x00);
	Write_Cmd_Data(0x25);
	Write_Cmd_Data(0x27);
	Write_Cmd_Data(0x05);
	Write_Cmd_Data(0x10);
	Write_Cmd_Data(0x09);
	Write_Cmd_Data(0x3a);
	Write_Cmd_Data(0x78);
	Write_Cmd_Data(0x4d);
	Write_Cmd_Data(0x05);
	Write_Cmd_Data(0x18);
	Write_Cmd_Data(0x0d);
	Write_Cmd_Data(0x38);
	Write_Cmd_Data(0x3a);
	Write_Cmd_Data(0x1f);

 	Write_Cmd(0x11);    //Exit Sleep
 	Delay(120);
 	Write_Cmd(0x29);    //Display on
 	Delay(50);
}


void set_window(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1){
	Write_Cmd(0x2A);
	Write_Cmd_Data16(x0%240);
	Write_Cmd_Data16(x1%240);

	Write_Cmd(0x2B);
	Write_Cmd_Data16(y0%320);
	Write_Cmd_Data16(y1%320);
}

void fill_area(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color){

	set_window(x0,x1,y0,y1);

	Write_Cmd(0x2C);
	for(int x=(x0%240); x<(x1%240)+1;x++){
		for(int y=(y0%320); y<(y1%320)+1; y++){
			Write_Cmd_Data16(color);
		}
	}
}


void fill_screen(uint16_t color){
	fill_area(0, 239, 0, 319, color);
}

void init_LCD(){

	// init timer for delay
	LPC_SC->PCLKSEL0&=~0b11<<2;
	LPC_SC->PCLKSEL0|=0b01<<2;
	LPC_TIM0->TCR=1;

	// init pin cmd/data
	LPC_GPIO1->FIODIR&=~1<<30;
	LPC_GPIO1->FIODIR|=1<<30;

	ILI9341_Initial();

	//backlight pin on
	 LPC_GPIO1->FIODIR|=1<<18;
	 LPC_GPIO1->FIOSET=1<<18;

	 fill_screen(RGB(0,0,0));
}

void set_pix(uint16_t x, uint16_t y, uint16_t color){
	if(x > 239 ||  y > 319)
		return;
	set_window(x,x,y,y);
	Write_Cmd(0x2C);
	Write_Cmd_Data16(color);
}

void draw_line(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color){
	if(x0 > 239 || x1 > 239 || y0 > 319 || y1 > 319)
		return;
	if(x0==x1 && y0==y1)
		return;
	if(x0==x1){
		if(y0<y1){
			for(int y=y0; y<y1; y++){
				set_pix(x0, y, color);
			}
		}else{
			draw_line(x0,x1,y1,y0,color);
		}
	}else if(y0==y1){
		if(x0<x1){
			for(int x=x0; x<x1; x++){
					set_pix(x, y0, color);
				}
			}else{
				draw_line(x1,x0,y0,y1,color);
			}
	}else{
		float a = 1.0*(y1-y0)/(x1-x0);
		uint16_t b = y1 - x1*a;
		for(int x=x0; x<x1;x++){
			uint16_t y = (uint16_t)(a*x) + b;
			set_pix(x,y,color);
		}
	}
}

void draw_circle(uint16_t c_x, uint16_t c_y, uint16_t r, uint16_t color){
	if(((c_x-r)>0) && ((c_x+r)<239) && ((c_y-r)>0) && ((c_y+r)<319)){
		//set_window(c_x-r,c_x+r,c_y-r,c_y+r);
		int x,y,m;
		x = 0;
		y = (int)r;
		m = 5 - 4*(int)r;
		while(x <= y){
			set_pix(x + c_x, y + c_y, color);
			set_pix(y + c_x, x + c_y, color);
			set_pix(c_x-x, y + c_y, color);
			set_pix(c_x-y, x + c_y, color);
			set_pix(x + c_x, c_y-y, color);
			set_pix(y + c_x, c_y-x, color);
			set_pix(c_x-x, c_y-y, color);
			set_pix(c_x-y,c_y-x, color);
			if (m > 0)
			{
				y = y - 1;
				m = m - 8*y;
			}
			x = x + 1;
			m = m + 8*x + 4;
		}
	}
}

void draw_circle2(uint16_t c_x, uint16_t c_y, uint16_t r, uint16_t color){
	for(uint16_t i=c_x-r; i<c_x+r;i++){
		uint16_t y=(uint16_t)sqrt(fabs(((float)r*(float)r-(float)i*(float)i)));
		printf(" %d-%d ",i, y);
		set_pix(i, y, color);
	}
}

void draw_circle3(uint16_t c_x, uint16_t c_y, uint16_t r, uint16_t color){
	for(int x=0; x<240;x++){
		for(int y=0; y<320;y++){
			uint16_t dist=(uint16_t)sqrt(pow(x-c_x,2)+pow(y-c_y,2));
			if(dist>r)
				set_pix(x,y,color);
		}
	}
}

void draw_cross(uint16_t x, uint16_t y, uint16_t size, uint16_t color){
	draw_line(x, x, y-size, y+size, color);
	draw_line(x-size, x+size, y, y, color);
}

void draw_rect(uint16_t x, uint16_t y, uint16_t size_x, uint16_t size_y, uint16_t color){
	draw_line(x, x+size_x, y, y, color);
	draw_line(x, x+size_x, y+size_y, y+size_y, color);
	draw_line(x, x, y, y+size_y, color);
	draw_line(x+size_x, x+size_x, y, y+size_y, color);
}

void fill_square(uint16_t x_c, uint16_t y_c, uint16_t size, uint16_t color){
	fill_area(x_c-size/2, x_c+size/2, y_c-size/2, y_c+size/2,color);
}

//void print_char(uint16_t x, uint16_t y, char c, uint16_t color){
//	uint8_t width_c = SmallFont[0];
//	uint8_t height_c = SmallFont[1];
//	uint8_t offset_ascii = SmallFont[2];
//
//	uint8_t line =0;
//	for(int i=0; i<height_c;i++){
//		line = SmallFont[4+(c-offset_ascii)*height_c+i];
//		for(int j=0; j<width_c; j++){
//			if((line & 1<<(7-j)) > 0){
//				set_pix(x+j,y+i,color);
//			}
//		}
//	}
//}

void lcd_scroll(uint16_t line){
	Write_Cmd(0x33);
	Write_Cmd_Data16(0x0);
	Write_Cmd_Data16(320);
	Write_Cmd_Data16(0x0);

	Write_Cmd(0x37);
	Write_Cmd_Data16(line);
}

