/******************************************************************************

test_6.c

	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//Einbinden v. Header Files:
//================================================================================
#include "tests.h"
#include "GLCD.h"
#include <LPC17xx.h>
#include <stdio.h>
#include "gpio.h"
#include "tests.h"
#include "GLCD.h"
#include "keys.h"
#include "lcd.h"
#include "led.h"
#include "core_cm3.h"
#include "prio.h"
#include "adc.h"
#include "dac.h"
#include "timer.h"
#include "I2C.h"


//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//================================================================================
//  test T6_1
//================================================================================
#if (T6_1==1) //6.1 SPI Bus
unsigned int ticks = 0;
unsigned int sec = 0;
const unsigned char SegChars[10] = {0x24, 0xAF, 0xE0, 0xA2, 0x2B, 0x32, 0x30, 0xA7, 0x20, 0x22};
unsigned char leftSeg;
unsigned char rightSeg;

void SysTick_Handler(void)
{
		ticks++;
	
		if(ticks >= 100)
		{
			sec++;
			ticks = 0;
			
			if (sec > 59)
			{
				sec = 0;
			}
		}

		
			leftSeg = SegChars[(sec/10)%10];
			rightSeg = SegChars[sec%10];
		
		if (ticks%2 == 0)
		{
			GPIOSetValue(0,1,0); //P0.1 Left Segments on
			GPIOSetValue(3,25,1); //P3.25 Right Segments off
			
			LPC_SSP0->DR = leftSeg; //Send Data
		}
		else
		{
			GPIOSetValue(0,1,1); //P0.1 Left Segments off
			GPIOSetValue(3,25,0); //P3.25 Right Segments on
			
			LPC_SSP0->DR = rightSeg; //Send Data
		}
}

int main(void)
{	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	SysTick_Handler();
	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Maroon); // Background color
	GLCD_SetTextColor(Blue); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test6.1: SPI-Bus ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8       ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"sec:");
	GLCD_DisplayString(5, 1, FONT_16x24, (unsigned char*)"left:");
	GLCD_DisplayString(6, 1, FONT_16x24, (unsigned char*)"right:");
	
	//SPI-Initialisation
	LPC_PINCON->PINSEL0 &=~ (3<<30); //P0.15
	LPC_PINCON->PINSEL0 |=  (2<<30);
	LPC_PINCON->PINSEL1 &=~ 0x3F; //P0.16-18
	LPC_PINCON->PINSEL1 |=  0x2A;
	LPC_PINCON->PINMODE1 &=~ (3<<2); //P0.17 neither pull up nor pull down
	LPC_PINCON->PINMODE1 |=  (2<<2);
	
	LPC_SC->PCLKSEL1 &=~ (3<<10); //clk = cclk
	LPC_SC->PCLKSEL1 |=  (1<<10);
	
	LPC_SSP0->CR0 &=~ (0xFFFF); //control register 0
	LPC_SSP0->CR0 |=  (0x0007);
	
	LPC_SSP0->CPSR = 100; //clock prescale
	
	LPC_SSP0->CR1 = 2; //control register 1
	
	//Defekte Init
//	LPC_SC->PCONP |= (1UL<<21); //Power Control
//	LPC_PINCON->PINSEL1 |= (2UL<<4); //P0.18 MOSI0 (Master Output Slave Input)
//	LPC_PINCON->PINSEL1 |= (2UL<<2); //P0.17 MISO0 (Master Input Slave Output)
//	
//	LPC_PINCON->PINMODE1 &=~ (3<<4); //P0.18 neither pull up nor pull down
//	LPC_PINCON->PINMODE1 |=  (2<<4);
//	
//	LPC_PINCON->PINMODE1 &=~ (3<<2); //P0.17 neither pull up nor pull down
//	LPC_PINCON->PINMODE1 |=  (2<<2);
//	
//	LPC_PINCON->PINSEL0 |= (2UL<<30); //P0.15 SCK0 Serial Clock from Master
//	LPC_PINCON->PINSEL1 |= (2UL<<0);  //P.16 SSEL0 Select Slave
//	
//	LPC_SC->PCLKSEL1 |= (1UL<<10); //SCLK_SSP0 = CCLK
//	
//	LPC_SSP0->CR0 |= (7UL<<0); //Data Size
//	
//	LPC_SSP0->CPSR = 100; //Prescaler -> Bitrate = 1MHz
//	
//	LPC_SSP0->CR1 &= ~(1UL<<0); //Control Register Normal Mode
//	LPC_SSP0->CR1 &= ~(1UL<<2); //SSP0 is master


	GPIOSetDir(0,1,1); //P0.1 Output
	GPIOSetDir(3,25,1); //P3.25 Output
	
	GPIOSetValue(0,1,1); //P0.1 Left Segments off
	GPIOSetValue(3,25,1); //P3.25 Right Segments off
	
	GLCD_Simulation();
	
	while(1)
	{
		
		GLCD_DisplayString(4, 8, FONT_16x24, (unsigned char*)lcd_dez(sec));
		GLCD_DisplayString(5, 8, FONT_16x24, (unsigned char*)lcd_hex(leftSeg));
		GLCD_DisplayString(6, 8, FONT_16x24, (unsigned char*)lcd_hex(rightSeg));
		GLCD_Simulation();
	} // end while(1)
}	// end main()


#endif


//
//================================================================================
//  test T6_2
//================================================================================
#if (T6_2==1) //6.2.1 I2C: 4 digit 7segment display

unsigned int ticks = 0;
unsigned int seconds = 0;
unsigned int sec = 0;
unsigned char SegChars[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char sbuf[3];
int32_t ret;


int32_t out7seg(uint8_t seg1, uint8_t seg2, uint8_t seg3, uint8_t seg4){
	uint8_t tx_dat[5];
	tx_dat[0] = 0x01; //Seg1 Adress
	tx_dat[1] = SegChars[seg1&0xF]|(seg1&0x80); // (SegChars[(4 & 0xF = 0000 0100 & 0000 1111) = 0000 0100 = 4] = 0x66 | 0 = ((0x3F & 0x80 = 0000 0100 & 1000 0000) = 0000 0000)) = 0x66 = 0100 0010
	tx_dat[2] = SegChars[seg2&0xF]|(seg2&0x80); // (SegChars[(130 & 0xF = 1000 0010 & 0000 1111) = 0000 0010 = 2] = 0x5B | 0x80 =((130 & 0x80 = 1000 0010 & 1000 0000) = 1000 0000)) = 0xDB = 1101 1011 = 219
	tx_dat[3] = SegChars[seg3&0xF]|(seg3&0x80);
	tx_dat[4] = SegChars[seg4&0xF]|(seg4&0x80);
	
	return I2C1Write(0x38, tx_dat, 5); //Adress, Data, Data length
}

//Alternativ
//int32_t out7seg(uint8_t seg1, uint8_t seg2, uint8_t seg3, uint8_t seg4){
//	uint8_t tx_dat[5];
//	tx_dat[0] = 0x01; //Seg 1 Adress
//	tx_dat[1] = SegChars[seg1];
//	tx_dat[2] = SegChars[seg2]|0x80; 
//	tx_dat[3] = SegChars[seg3];
//	tx_dat[4] = SegChars[seg4];
//	
//	return I2C1Write(0x38, tx_dat, 5); //Adress, Data, Data length
//}

void SysTick_Handler(void){
		ticks++;
	
		if(ticks >= 100)
		{
			sec++;
			ticks = 0;
			
			if (sec > 59)
			{
				sec = 0;
			}
		}
}

int main(void)
{	
	// systick 10ms
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	SysTick_Handler();
	
	// LCD Init
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Maroon);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test6.2.1: I2C-Disp ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8       ");
	
	GLCD_DisplayString(4, 0, FONT_16x24, (unsigned char*)"sec:");
	GLCD_DisplayString(5, 0, FONT_16x24, (unsigned char*)Hex-sec:);
	
	//i2c init
	I2C1_Init();sbuf[0]=0;sbuf[1]=0x17;//initialize 7 segment display, sbuf[] is to define
	ret=I2C1Write(0x38,sbuf,2); //it is only possible with connected hardware

	GLCD_Simulation();
	
	while(1)
	{		
		//out7seg((sec/10)%10, sec%10, 5-((sec/10)%10), 9-(sec%10));
		
		out7seg((sec/10)%10, sec%10|0x80, 5-((sec/10)%10), 9-(sec%10));  //Bsp.: 42: (4, (2 | 0x80 = 0000 0010 | 1000 0000 = 130 ???),5-4 = 1, 9-2 = 7)
		
		GLCD_DisplayString(4, 9, FONT_16x24, (unsigned char*)lcd_dez(sec));
		GLCD_DisplayString(5, 11, FONT_16x24, (unsigned char*)lcd_hex(sec));
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_3
//================================================================================
#if (T6_3==1) //6.2.2 I2C: Temperature display

unsigned int ticks = 0;

unsigned char SegChars[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char sbuf[3];
int32_t ret;
int32_t temp;

int32_t out7seg(uint8_t seg1, uint8_t seg2, uint8_t seg3, uint8_t seg4){
	uint8_t tx_dat[5];
	tx_dat[0] = 0x01;
	tx_dat[1] = SegChars[seg1&0xF]|(seg1&0x80);
	tx_dat[2] = SegChars[seg2&0xF]|(seg2&0x80);
	tx_dat[3] = SegChars[seg3&0xF]|(seg3&0x80);
	tx_dat[4] = SegChars[seg4&0xF]|(seg4&0x80);
	
	return I2C1Write(0x38, tx_dat, 5);
}

void SysTick_Handler(void){
		ticks++;
}

int main(void)
{	
	// systick 10ms
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	SysTick_Handler();
	
	// LCD Init
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Maroon);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test6.2.2: I2C-Temp");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8       ");
	
	GLCD_DisplayString(4, 0, FONT_16x24, (unsigned char*)"Temp:");
	GLCD_DisplayString(5, 0, FONT_16x24, (unsigned char*)"Hex-Temp:");
	//i2c init
	I2C1_Init();sbuf[0]=0;sbuf[1]=0x17;//initialize 7 segment display, sbuf[] is to define
	ret=I2C1Write(0x38,sbuf,2); //it is only possible with connected hardware
	
	//temp sensor init
	sbuf[0]=1;sbuf[1]=0x60; ret=I2C1Write(0x48,sbuf,2);//sbuf = 0000 0001   0110 0000
	sbuf[0]=0;
	
	while(1)
	{
		if(!sbuf[0]) //sbuf[0] = 0 ?
		{ 
			ret=I2C1Write(0x48,sbuf,1); //sbuf = 0000 0000
		}
		if(!ret){ //no Error ?
			ret=I2C1Read(0x48,sbuf,2); //sbuf[0] = read Tempvalue MSByte, sbuf[1] = read Tempvalue LSByte(Nachkommastellen), 
			if(!ret) //no Error ?
			{ 
				temp = (((sbuf[0]<<8)|sbuf[1])>>4); // (0001 1001 << 8) = 0001 1001 0000 0000 | 0100 =(0100 **** >> 4)	= 0001 1001 0000 0100
				if((temp>>11)&1) // 0001 1
				{
					temp |= (0x8 << 12); // 1001 1001 0000 0100
				}
				sbuf[0]=0;
			}
		}
		if(temp){
			
			temp *= 625;
			temp /= 100;
			
			out7seg((temp/1000)%10, (temp/100)%10|0x80, (temp/10)%10, temp%10);
			
			GLCD_DisplayString(4, 9, FONT_16x24, (unsigned char*)TempConv2(temp));
			GLCD_DisplayString(5, 11, FONT_16x24, (unsigned char*)lcd_hex(temp));
			
			temp=0;
		}
			
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_4
//================================================================================
#if (T6_4==1) //6.2.4 EEPROM with I2C bus

unsigned char sbuf[3];
int32_t ret;

int main(void)
{	
	// LCD Init
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Maroon);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test6.2.4: I2C-EEPROM");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8       ");
	
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"switch:");
	GLCD_DisplayString(5, 1, FONT_16x24, (unsigned char*)"address:");
	GLCD_DisplayString(6, 1, FONT_16x24, (unsigned char*)"read byte:");
	
	//i2c init
	I2C1_Init();
	
	//switch init
	Switch_Init();
	button_Init();
	
	//eeprom address
	sbuf[0] = 0x15; //0001 0101
	sbuf[1] = 0x55;	//0101 0101

	while(1)
	{
		if(Get_TA12Stat()){
			//read switchpos
			sbuf[2] = Get_SwitchPos();
			//write to eeprom
			I2C1Write(0x50, sbuf, 3);
			
			//read from eeprom
			I2C1Write(0x50, sbuf, 2);
			I2C1Read(0x50, &sbuf[2], 1);
			
			//display values
			GLCD_DisplayString(4, 13, FONT_16x24, (unsigned char*)lcd_hex(Get_SwitchPos()));
			GLCD_DisplayString(5, 13, FONT_16x24, (unsigned char*)lcd_hex((sbuf[0]<<8|sbuf[1])));
			GLCD_DisplayString(6, 13, FONT_16x24, (unsigned char*)lcd_hex(sbuf[2]));
		}
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_5
//================================================================================
#if (T6_5==1) //6.2.5 I2C: Light sensor

unsigned char sbuf[4];
int32_t lux;

int main(void)
{	
	// LCD Init
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Maroon);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab    ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test6.2.5: I2C-Light-Sens");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8       ");
	
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"lux:");
	
	//i2c init
	I2C1_Init();
	
	//light sensor init
	sbuf[0] = 0x00; //register adress 0
	sbuf[1] = 0x80; //Enable Sensor
	I2C1Write(0x44, sbuf, 2);
	
	//set sbuf
	sbuf[0] = 0x04; //register adress 0x04
	sbuf[1] = 0x05; //register adress 0x05
	
	GLCD_Simulation();

	while(1)
	{
		//read from light sensor
		I2C1Write(0x44, &sbuf[0], 1);
		I2C1Read(0x44, &sbuf[2], 1);
		I2C1Write(0x44, &sbuf[1], 1);
		I2C1Read(0x44, &sbuf[3], 1);
		
		//calculate lux value
		lux = 973*((sbuf[3]<<8)|sbuf[2])/(1<<16);
		
		//display values
		GLCD_DisplayString(4, 13, FONT_16x24, (unsigned char*)lcd_dez(lux));
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif


#if (T6_6==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_7
//================================================================================
#if (T6_7==1)

unsigned char sbuf[3];
int test = 0;

int main(void)
{	
	
	while(1)
	{

	} // end while(1)
}	// end main()

#endif

