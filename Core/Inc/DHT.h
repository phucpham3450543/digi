#include "main.h"

void Display_Humidity(float humidity);
void Display_Temperature(float temperature);
void Set_Pin_Iput(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void DHT_Start(void);
uint8_t DHT_Check(void);
uint8_t DHT_Read(void);
void Get_data_DHT11(void);
