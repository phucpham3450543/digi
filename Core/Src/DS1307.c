#include "D1307.h"

#define DS3231_Address 0xD0
#define Address_Start 0x00


Handle_time time;
extern I2C_HandleTypeDef hi2c1;
char buffer[16];

uint8_t DectoBcd(int val){
	return (uint8_t)( (val/10*16) + (val%10) );
}

int BcdtoDec(uint8_t val){
  return (int)( (val/16*10) + (val%16) );
}

void Set_time(int seconds, int minutes, int hour, int day, int date, int month, int year){
	uint8_t Time[7];
	Time[0] = DectoBcd(seconds);
	Time[1] = DectoBcd(minutes);
	Time[2] = DectoBcd(hour);
	Time[3] = DectoBcd(day);
	Time[4] = DectoBcd(date);
	Time[5] = DectoBcd(month);
	Time[6] = DectoBcd(year);
	HAL_I2C_Mem_Write(&hi2c1, DS3231_Address, Address_Start, 1, Time, 7, 1000);
}

void Get_time(void){
	uint8_t Time[7];
	HAL_I2C_Mem_Read(&hi2c1, DS3231_Address, Address_Start, 1, Time, 7, 1000);
	time.seconds = BcdtoDec(Time[0]);
	time.minutes = BcdtoDec(Time[1]);
	time.hour = BcdtoDec(Time[2]);
	time.day = BcdtoDec(Time[3]);
	time.date = BcdtoDec(Time[4]);
	time.month = BcdtoDec(Time[5]);
	time.year = BcdtoDec(Time[6]);
}
