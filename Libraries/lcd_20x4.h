#include "main.h"

void lcd_init(void);
void lcd_write_data(uint8_t Data);
void lcd_write_cmd(uint8_t Data);
void lcd_clear(void);
void lcd_write_string(char * string);
void Lcd_creat_customchar(char * custom_data, uint8_t location);
void Lcd_writ_customchar(uint8_t row, uint8_t column, uint8_t location);

