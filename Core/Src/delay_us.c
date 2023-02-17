#include "delay_us.h"

extern TIM_HandleTypeDef htim1;

void Delay_us(uint16_t us){
	htim1.Instance->CNT = 0;
	HAL_TIM_Base_Start(&htim1);
	while(htim1.Instance->CNT < us);
	HAL_TIM_Base_Stop(&htim1);
}


