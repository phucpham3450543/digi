#include "D1307.h"
#include "main_menu.h"
#include "i2c-lcd.h"
#include "delay_us.h"
#include "encoder.h"
#include "DHT.h"
#include "stdio.h"

char Arrow[] = {0x00, 0x04, 0x1E, 0x1F, 0x1E, 0x04, 0x00, 0x00};
extern char buffer[16];
extern Handle_time time;

void Set_up(void){
	lcd_init();
	Encoder_Setup();
	lcd_send_cmd(0x1C);
	lcd_send_cmd(0x40);
	for(int i = 0; i < 8; i++) lcd_send_data(Arrow[i]);
}

void Print_arrow(int location){

	switch(location){
		default:
			break;
		case 0:
			lcd_send_cmd(0x80|0x15);
			lcd_send_data(0);
			lcd_send_cmd(0x80|0x55);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x1F);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x5F);
			lcd_send_string(" ");
			break;
		case 1:
			lcd_send_cmd(0x80|0x15);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x55);
			lcd_send_data(0);
			lcd_send_cmd(0x80|0x1F);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x5F);
			lcd_send_string(" ");
			break;
		case 2:
			lcd_send_cmd(0x80|0x15);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x55);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x1F);
			lcd_send_data(0);
			lcd_send_cmd(0x80|0x5F);
			lcd_send_string(" ");
			break;
		case 3:
			lcd_send_cmd(0x80|0x15);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x55);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x1F);
			lcd_send_string(" ");
			lcd_send_cmd(0x80|0x5F);
			lcd_send_data(0);
			break;
	}
}

void Setting_menu_1(void){
	lcd_send_cmd(0x80|0x03);
	lcd_send_string("SETTING TIME");
	Set_time(Change_seconds(), Change_minutes(), Change_hour(), Change_day(), Change_date(), Change_month(), Change_year());
	Get_time();
	sprintf (buffer, "%02d:%02d:%02d", time.hour, time.minutes, time.seconds);
	lcd_send_cmd(0x80|0x45);
	lcd_send_string(buffer);
	lcd_send_cmd(0x80|0x16);
	lcd_send_string("HOUR");
	lcd_send_cmd(0x80|0x56);
	lcd_send_string("MINUTES");
	lcd_send_cmd(0x80|0x20);
	lcd_send_string("SECONDS");
	lcd_send_cmd(0x80|0x60);
	lcd_send_string("CONFIRM");
}
void Setting_menu_2(void){
	lcd_send_cmd(0x80|0x03);
	lcd_send_string("SETTING DATE");
	Set_time(Change_seconds(), Change_minutes(), Change_hour(), Change_day(), Change_date(), Change_month(), Change_year());
	Get_time();
	sprintf (buffer, "%02d-%02d-20%02d", time.date, time.month, time.year);
	lcd_send_cmd(0x80|0x44);
	lcd_send_string(buffer);
	lcd_send_cmd(0x80|0x16);
	lcd_send_string("DATE");
	lcd_send_cmd(0x80|0x56);
	lcd_send_string("MONTH");
	lcd_send_cmd(0x80|0x20);
	lcd_send_string("YEAR");
	lcd_send_cmd(0x80|0x60);
	lcd_send_string("CONFIRM");
}

void Main_menu(void){
	  lcd_send_cmd(0x80|0x01);
	  lcd_send_string("WELCOME TO COSIO");
	  lcd_send_cmd(0x80|0x43);
	  lcd_send_string("PLEASE WAIT");
	  lcd_send_cmd(0x80|0x17);
	  lcd_send_string("FOR SETTING");
	  HAL_Delay(3000);
	  lcd_clear();
	  while(1){
	  Get_time();
	  sprintf (buffer, "TIME: %02d:%02d:%02d", time.hour, time.minutes, time.seconds);
	  lcd_send_cmd(0x80|0x00);
	  lcd_send_string(buffer);
	  sprintf (buffer, "DATE: %02d-%02d-20%02d", time.date, time.month, time.year);
	  lcd_send_cmd(0x80|0x40);
	  lcd_send_string(buffer);
	  Get_data_DHT11();
	  }
}

void Change_hour_button(void){
    Change_hour();
    Set_time(Change_seconds(), Change_minutes(), Change_hour(), Change_day(), Change_date(), Change_month(), Change_year());
    Get_time();
    sprintf (buffer, "%02d:%02d:%02d", time.hour, time.minutes, time.seconds);
    lcd_send_cmd(0x80|0x45);
    lcd_send_string(buffer);
}

void Change_minutes_button(void){
	Change_minutes();
	Set_time(Change_seconds(), Change_minutes(), Change_hour(), Change_day(), Change_date(), Change_month(), Change_year());
	Get_time();
	sprintf (buffer, "%02d:%02d:%02d", time.hour, time.minutes, time.seconds);
	lcd_send_cmd(0x80|0x45);
	lcd_send_string(buffer);
}

void Change_seconds_button(void){
	Change_seconds();
	Set_time(Change_seconds(), Change_minutes(), Change_hour(), Change_day(), Change_date(), Change_month(), Change_year());
	Get_time();
	sprintf (buffer, "%02d:%02d:%02d", time.hour, time.minutes, time.seconds);
	lcd_send_cmd(0x80|0x45);
	lcd_send_string(buffer);
}

void Change_date_button(void){
	Change_date();
	Set_time(Change_seconds(), Change_minutes(), Change_hour(), Change_day(), Change_date(), Change_month(), Change_year());
	Get_time();
	sprintf (buffer, "%02d-%02d-20%02d", time.date, time.month, time.year);
	lcd_send_cmd(0x80|0x45);
	lcd_send_string(buffer);
}

void Change_month_button(void){
	Change_month();
	Set_time(Change_seconds(), Change_minutes(), Change_hour(), Change_day(), Change_date(), Change_month(), Change_year());
	Get_time();
	sprintf (buffer, "%02d-%02d-20%02d", time.date, time.month, time.year);
	lcd_send_cmd(0x80|0x45);
	lcd_send_string(buffer);
}

void Change_year_button(void){
	Change_year();
	Set_time(Change_seconds(), Change_minutes(), Change_hour(), Change_day(), Change_date(), Change_month(), Change_year());
	Get_time();
	sprintf (buffer, "%02d-%02d-20%02d", time.date, time.month, time.year);
	lcd_send_cmd(0x80|0x45);
	lcd_send_string(buffer);
}

void Setup_menu(void){
	switch(Encoder_Handle()){
		default:
			break;
		case 0:
			Print_arrow(Encoder_Handle());
				if(Button_Handle() == 0){
					lcd_clear();
					lcd_send_cmd(0x80|0x17);
					lcd_send_string("PRESS BUTTON");
						while(1){
						  while(Button_Handle() == 0);
						  Change_hour_button();
						  if(Button_Handle() == 0){
								  while(Button_Handle() == 0);
								  lcd_clear();
								  break;
							  }
					}
				}
				Setting_menu_1();
			break;
		case 1:
			Print_arrow(Encoder_Handle());
			if(Button_Handle() == 0){
				lcd_clear();
				lcd_send_cmd(0x80|0x17);
				lcd_send_string("PRESS BUTTON");
					while(1){
					  while(Button_Handle() == 0);
					  Change_minutes_button();
					  if(Button_Handle() == 0){
						  while(Button_Handle() == 0);
						  lcd_clear();
						  break;
					  }
				}
			}
			Setting_menu_1();
			break;
		case 2:
			Print_arrow(Encoder_Handle());
			if(Button_Handle() == 0){
				lcd_clear();
				lcd_send_cmd(0x80|0x17);
				lcd_send_string("PRESS BUTTON");
					while(1){
					  while(Button_Handle() == 0);
					  Change_seconds_button();
					  if(Button_Handle() == 0){
						  while(Button_Handle() == 0);
						  lcd_clear();
						  break;
					  }
				}
			}
			Setting_menu_1();
			break;
		case 3:
			Print_arrow(Encoder_Handle());
			if(Button_Handle() == 0){
				while(Button_Handle() == 0);
				lcd_clear();
				Setting_menu_2();
				while(1){
					switch(Encoder_Handle()){
					default:
						break;
					case 0:
						Print_arrow(Encoder_Handle());
						if(Button_Handle() == 0){
							lcd_clear();
							lcd_send_cmd(0x80|0x17);
							lcd_send_string("PRESS BUTTON");
								while(1){
								  while(Button_Handle() == 0);
								  Change_date_button();
								  if(Button_Handle() == 0){
									  while(Button_Handle() == 0);
									  lcd_clear();
									  break;
								  }

							}

						}
						Setting_menu_2();
						break;
					case 1:
						Print_arrow(Encoder_Handle());
						if(Button_Handle() == 0){
							lcd_clear();
							lcd_send_cmd(0x80|0x17);
							lcd_send_string("PRESS BUTTON");
								while(1){
									Change_date_button();
								  if(Button_Handle() == 0){
									  while(Button_Handle() == 0);
									  lcd_clear();
									  break;
								  }
							}
						}
						Setting_menu_2();
						break;
					case 2:
						Print_arrow(Encoder_Handle());
						if(Button_Handle() == 0){
							lcd_clear();
							lcd_send_cmd(0x80|0x17);
							lcd_send_string("PRESS BUTTON");
								while(1){
								  while(Button_Handle() == 0);
								  Change_year_button();
								  if(Button_Handle() == 0){
									  while(Button_Handle() == 0);
									  lcd_clear();
									  break;
								  }
							}
						}
						Setting_menu_2();
						break;
					case 3:
						Print_arrow(Encoder_Handle());
						if(Button_Handle() == 0){
							lcd_clear();
								while(1){
								  while(Button_Handle() == 0);
								  Main_menu();
							}
						}
						break;
				}
	}
			}
	}
}

