#include "encoder.h"

int Seconds = 0, Minutes = 0, Hour = 0, Day = 0, Date = 0, Month = 0, Year = 23;
int count = 0, button_count = 1;
uint8_t begin_state;
uint8_t current_state;
uint8_t button_current_state = 1;
uint8_t button_last_state = 1;
uint8_t button_filter = 1;
uint8_t is_debouncing = 0;
uint32_t time_debounce;

void Encoder_Setup(void){

	begin_state = HAL_GPIO_ReadPin(GPIOA , CLK_PIN);
	
}

int Encoder_Handle(void){
	current_state = HAL_GPIO_ReadPin(GPIOA, CLK_PIN);
	if(current_state != begin_state){
		if(current_state != HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			count++;
		}
		else if(current_state == HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			count--;
		}
	}
	if(count < 0){
		count = 3;
	}
	else if(count > 3){
		count = 0;
	}
	begin_state = current_state;
	return count;
}

int Change_hour(void){
	current_state = HAL_GPIO_ReadPin(GPIOA, CLK_PIN);
	if(current_state != begin_state){
		if(current_state != HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			Hour++;
		}
		else{
			Hour--;
		}
	}
	if(Hour < 0)  Hour = 24;
	if(Hour > 24) Hour = 0;
	begin_state = current_state;
	return Hour;
}

int Change_minutes(void){
	current_state = HAL_GPIO_ReadPin(GPIOA, CLK_PIN);
	if(current_state != begin_state){
		if(current_state != HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			Minutes++;
		}
		else{
			Minutes--;
		}
	}
	if(Minutes < 0)  Minutes = 60;
	if(Minutes > 60) Minutes = 0;
	begin_state = current_state;
	return Minutes;
}

int Change_seconds(void){
	current_state = HAL_GPIO_ReadPin(GPIOA, CLK_PIN);
	if(current_state != begin_state){
		if(current_state != HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			Seconds++;
		}
		else{
			Seconds--;
		}
	}
	if(Seconds < 0)  Seconds = 60;
	if(Seconds > 60) Seconds = 0;
	begin_state = current_state;
	return Seconds;
}

int Change_day(void){
	current_state = HAL_GPIO_ReadPin(GPIOA, CLK_PIN);
	if(current_state != begin_state){
		if(current_state != HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			Day++;
		}
		else{
			Day--;
		}
	}
	begin_state = current_state;
	return Day;
}

int Change_date(void){
	current_state = HAL_GPIO_ReadPin(GPIOA, CLK_PIN);
	if(current_state != begin_state){
		if(current_state != HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			Date++;
		}
		else{
			Date--;
		}
	}
	if(Date < 1) Date  = 31;
	if(Date > 31) Date = 1;
	begin_state = current_state;
	return Date;
}

int Change_month(void){
	current_state = HAL_GPIO_ReadPin(GPIOA, CLK_PIN);
	if(current_state != begin_state){
		if(current_state != HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			Month++;
		}
		else{
			Month--;
		}
	}
	if(Month < 1) Month  = 12;
	if(Month > 12) Month = 1;
	begin_state = current_state;
	return Month;
}

int Change_year(void){
	current_state = HAL_GPIO_ReadPin(GPIOA, CLK_PIN);
	if(current_state != begin_state){
		if(current_state != HAL_GPIO_ReadPin(GPIOA, DT_PIN)){
			Year++;
		}
		else{
			Year--;
		}
	}
	if(Year < 0) Year = 0;
	if(Year > 99) Year = 99;
	begin_state = current_state;
	return Year;
}

int Button_Handle(void)
{
	uint8_t sta = HAL_GPIO_ReadPin(GPIOA, SW_PIN);
	if(sta != button_filter)
	{
		button_filter = sta;
		is_debouncing = 1;
		time_debounce = HAL_GetTick();
	}
	if(is_debouncing  && (HAL_GetTick() - time_debounce >= 15))
	{
		button_current_state = button_filter;
		is_debouncing = 0;
	}

	if(button_current_state != button_last_state)
	{
		if(button_current_state == 0)
		{
			button_count = 0;
		}
		else
		{
			button_count = 1;
		}
		button_last_state = button_current_state;
	}
	return button_count;
}
