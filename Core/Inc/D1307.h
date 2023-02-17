#include "main.h"

typedef struct{
	int seconds;
	int minutes;
	int hour;
	int day;
	int date;
	int month;
	int year;
}Handle_time;

uint8_t DectoBcd(int val);
int BcdtoDec(uint8_t val);
void Set_time(int seconds, int minutes, int hour, int day, int date, int month, int year);
void Get_time(void);
