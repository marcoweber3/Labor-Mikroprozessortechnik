#ifndef lcd
#define lcd





char *lcd_dez(uint16_t value); //wandelt value un dez text um
char *lcd_hex(uint16_t value); //wandelt value in hex text um
char *lcd_bin(uint8_t value);  //wandelt value in binär text um
char *AD_volt(unsigned short val); //wandelt val= 0...4095 in Spannung[V]=0.00...3.30 quasi DA Wandler
char *TempConv(unsigned short val); //wandelt val= 0...4095 in Temp[C]=00.00...33.00 quasi DA Wandler

#endif

