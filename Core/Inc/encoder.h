#include "stm32f1xx_hal.h"
#include "main.h"

#define CLK_PIN         GPIO_PIN_1
#define DT_PIN         GPIO_PIN_2
#define SW_PIN         GPIO_PIN_3

void Encoder_Setup(void);
int Encoder_Handle(void);
int Change_hour(void);
int Change_minutes(void);
int Change_seconds(void);
int Change_day(void);
int Change_date(void);
int Change_month(void);
int Change_year(void);
int Button_Handle(void);
