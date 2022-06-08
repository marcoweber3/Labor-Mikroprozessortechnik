#ifndef lcd
#define lcd

char *lcd_bin (uint8_t value);
char *lcd_hex (uint16_t value);
char *lcd_dez(uint16_t value);

char *lcd_dez2(uint16_t value);

char *AD_volt(unsigned short val);
char *TempConv(unsigned short val);	
char *TempConv2(unsigned short val);

#endif
