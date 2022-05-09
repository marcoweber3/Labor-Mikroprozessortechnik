#include <LPC17xx.h>
#include "lcd.h" 
//#include <stdio.h>

char *lcd_bin (uint8_t value) //e.g.: 135 -> 10000111 -> 0x31 0x30 0x30 0x30 0x30 0x31 0x31 0x31 0
{	
	unsigned char asc[] = "0123456789ABCDEF";
	static char array[9];

	int i = 0;
	
	
	for (i = 0; i < 8; i++)
	{
		array[7-i] = asc[value % 2];
		value = value / 2;
	}
	array[8] = 0;
	
	
	return (array);
}

char *lcd_hex (uint16_t value) //e.g.: 135 -> 0 16 8 7 -> 0x30 0x78 0x38 0x37 0
{
		static char text_string[7];
		unsigned char asc[] = "0123456789ABCDEFx";
	  
/*
	GPIOSetDir(2, 0, 1); //Pin 2.0
	GPIOSetDir(2, 1, 1); //Pin 2.1
	
	GPIOSetValue(2, 0, 1); //Start Array-Function
*/
		text_string[0] = asc[0];
		text_string[1] = asc[16];
		text_string[2] = asc[(value/16 )%16];
		text_string[3] = asc[(value/1)%16];
		text_string[4] = 0;


	//GPIOSetValue(2, 0, 0); //End Array-Function
	
	//764 ns Laufzeit mit text_string

/*	
	GPIOSetValue(2, 1, 1); //Start sprintf-Function
	sprintf(text_string,"%5u",value); //alternative use sprintf
	GPIOSetValue(2, 1, 0); //End sprintf-Function
*/
//6,3us Laufzeit mit sprintf	
		return (text_string);
}


char *lcd_dez(uint16_t value) //e.g.: 135 -> 0 0 1 3 5 -> 0x30 0x30 0x31 0x33 0x35 0
{ 
		static char text_string[6];
		unsigned char asc[] = "0123456789ABCDEF";
	
/*
	GPIOSetDir(2, 0, 1); //Pin 2.0
	GPIOSetDir(2, 1, 1); //Pin 2.1
	
	GPIOSetValue(2, 0, 1); //Start Array-Function
*/
		text_string[0] = asc[(value/10000 )%10];
		text_string[1] = asc[(value/1000 )%10];
		text_string[2] = asc[(value/100 )%10];
		text_string[3] = asc[(value/10 )%10];
		text_string[4] = asc[(value/1 )%10];
		text_string[5] = 0;
	

	//GPIOSetValue(2, 0, 0); //End Array-Function

	//1000ns Laufzeit mit text_string

/*
	GPIOSetValue(2, 1, 1); //Start sprintf-Function
	sprintf(text_string,"%5u",value); //alternative use sprintf
	GPIOSetValue(2, 1, 0); //End sprintf-Function
	
	//5,66us Laufzeit mit sprintf
*/
		// sprintf (text_string,"%5u",value); //alternative use sprintf
		return (text_string);
} 

char *lcd_dez2(uint16_t value) //e.g.: 135 -> 0 0 1 3 5 -> 0x30 0x30 0x31 0x33 0x35 0
{ 
		static char text_string[3];
		unsigned char asc[] = "0123456789ABCDEF";
	
		text_string[0] = asc[(value/10 )%10];
		text_string[1] = asc[(value/1 )%10];
		text_string[2] = 0;
	

		return (text_string);
} 

char *AD_volt(unsigned short val)
{
	static char text_string[6];
	unsigned char asc[] = "0123456789,V";
	
	val = (val * 3300) / 4095;
	
	text_string[0] = asc[(val/1000)%10];
	text_string[1] = asc[10];
	text_string[2] = asc[(val/100)%10];
	text_string[3] = asc[(val/10)%10];
	text_string[4] = asc[11];
	text_string[5] = 0;
	return (text_string);
}

char *TempConv(unsigned short val)
{
	static char text_string[7];
	unsigned char asc[] = "0123456789,C";
	val = (val * 3300) / 4095;
	text_string[0] = asc[(val/1000)%10];
	text_string[1] = asc[(val/100)%10];
	text_string[2] = asc[10];
	text_string[3] = asc[(val/10)%10];
	text_string[4] = asc[(val/1)%10];
	text_string[5] = asc[11];
	text_string[6] = 0;
	return (text_string);
}
