#include "lcd_20x4.h"

#define  clear_lcd  0x01
#define  return_home  0x02
#define  set_function  0x38
#define  set_entry  0x06
#define  set_display  0x0C

#define	 RS_PIN  GPIO_PIN_8
#define  RW_PIN  GPIO_PIN_9
#define  E  GPIO_PIN_10
#define  D4  GPIO_PIN_4
#define  D5  GPIO_PIN_5
#define  D6  GPIO_PIN_6
#define  D7  GPIO_PIN_7

void lcd_init(void){
	//function set
	lcd_write_cmd(set_function);
	//lcd clear
	lcd_write_cmd(clear_lcd);
	//lcd return home
	lcd_write_cmd(return_home);
	//set entry mode
	lcd_write_cmd(set_entry);
	//set display
	lcd_write_cmd(set_display);
}


void lcd_write_data(uint8_t Data){
	HAL_GPIO_WritePin(GPIOA, RS_PIN, 1);
	HAL_GPIO_WritePin(GPIOA, RW_PIN, 0);
	//Gui 4 bit dau
	HAL_GPIO_WritePin(GPIOA, D4, (Data>>4) & 0x01);
	HAL_GPIO_WritePin(GPIOA, D5, (Data>>4) & 0x02);
	HAL_GPIO_WritePin(GPIOA, D6, (Data>>4) & 0x04);
	HAL_GPIO_WritePin(GPIOA, D7, (Data>>4) & 0x08);
	HAL_GPIO_WritePin(GPIOA, E, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, E, 0);
	//Gui 4 bit sau
	HAL_GPIO_WritePin(GPIOA, D4, Data & 0x01);
	HAL_GPIO_WritePin(GPIOA, D5, Data & 0x02);
	HAL_GPIO_WritePin(GPIOA, D6, Data & 0x04);
	HAL_GPIO_WritePin(GPIOA, D7, Data & 0x08);
	HAL_GPIO_WritePin(GPIOA, E, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, E, 0);
}

void lcd_write_cmd(uint8_t Data){
	HAL_GPIO_WritePin(GPIOA, RS_PIN, 0);
	HAL_GPIO_WritePin(GPIOA, RW_PIN, 0);
	//Gui 4 bit dau
	HAL_GPIO_WritePin(GPIOA, D4, (Data>>4) & 0x01);
	HAL_GPIO_WritePin(GPIOA, D5, (Data>>4) & 0x02);
	HAL_GPIO_WritePin(GPIOA, D6, (Data>>4) & 0x04);
	HAL_GPIO_WritePin(GPIOA, D7, (Data>>4) & 0x08);
	
	HAL_GPIO_WritePin(GPIOA, E, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, E, 0);
	//Gui 4 bit sau
	HAL_GPIO_WritePin(GPIOA, D4, Data & 0x01);
	HAL_GPIO_WritePin(GPIOA, D5, Data & 0x02);
	HAL_GPIO_WritePin(GPIOA, D6, Data & 0x04);
	HAL_GPIO_WritePin(GPIOA, D7, Data & 0x08);
	
	HAL_GPIO_WritePin(GPIOA, E, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA, E, 0);
}

void lcd_clear(void){
	lcd_write_cmd(0x01);
}

void lcd_write_string(char * string){
	for(uint8_t i = 0; i < strlen(string); i++)
	{
		lcd_write_data( string[i]);
	}
}

void lcd_location(uint8_t row, uint8_t column){
	uint8_t location;
	switch(row){
		case 1:
			location = 0x00 + column;
			break;
		case 2:
			location = 0x40 + column;
			break;
		case 3:
			location = 0x14 + column;
			break;
		case 4:
			location = 0x54 + column;
			break;
		default:
			break;
	}
	lcd_write_cmd(0x80|location);
}

void Lcd_creat_customchar(char * custom_data, uint8_t location){
	lcd_write_cmd(0x40 + (location*8));
	for(int i = 0; i<8; i++)
	{
		lcd_write_data(custom_data[i]);
	}
}

void Lcd_writ_customchar(uint8_t row, uint8_t column, uint8_t location){
	lcd_location(row, column);
	lcd_write_data(location);
}


