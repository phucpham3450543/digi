#include "DHT.h"
#include "delay_us.h"
#include "i2c-lcd.h"
#include "stdio.h"
uint8_t Response;
uint8_t RH_byte1, RH_byte2, T_byte1, T_byte2, Check_sum;
uint16_t RH,TEMP;
float temperature = 0;
float humidity = 0;
uint8_t Presence = 0;
void Display_Humidity(float humidity)
{
	char str[20];
	lcd_send_cmd(0x80|0x14);
	sprintf(str, "RH: %.f", humidity);
	lcd_send_string(str);
	lcd_send_cmd(0x80|0x1A);
	lcd_send_string("%");
}

void Display_Temperature(float temperature)
{
	char str[20];
	lcd_send_cmd(0x80|0x54);
	sprintf(str, "TEMP: %.f", temperature);
	lcd_send_string(str);
	lcd_send_cmd(0x80|0x5C);
	lcd_send_string("C");

}

void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void DHT_Start(void){
	Set_Pin_Output(GPIOA, GPIO_PIN_4);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	Delay_us(18000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
	Delay_us(20);
	Set_Pin_Input(GPIOA, GPIO_PIN_4);
}
uint8_t DHT_Check(void){
	Set_Pin_Input(GPIOA, GPIO_PIN_4);
	Delay_us(40);
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0){
		Delay_us(80);
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1){
			Response = 1;
		}
		else Response = -1;
	}
	while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 1);
	return Response;
}

uint8_t DHT_Read(void){
	uint8_t i, j;
for(j=0; j< 8; j++)
	{
			while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0);
			Delay_us(40);
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)
			{
				i = i<<1;
			}
			else
			{
				i = (i<<1) | 0x01;
			}
			while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==1);
	}
	return i;
}

void Get_data_DHT11(void)
{
	  Display_Temperature(temperature);
	  Display_Humidity(humidity);

	  DHT_Start();
	  Presence = DHT_Check();
	  RH_byte1 = DHT_Read();
	  RH_byte2 = DHT_Read();
	  T_byte1 = DHT_Read();
	  T_byte2 = DHT_Read();
	  Check_sum = DHT_Read();

	  TEMP = T_byte1;
	  RH = RH_byte1;

	  temperature = (float) TEMP;
	  humidity = (float) RH;

	  HAL_Delay(1000);
}

