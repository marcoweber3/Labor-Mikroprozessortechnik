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
#if (T6_1==1)
unsigned int ticks = 0;
unsigned int sec = 0;
const unsigned char SegChars[10] = {0x24, 0xAF, 0xE0, 0xA2, 0x2B, 0x32, 0x30, 0xA7, 0x20, 0x22};
unsigned char leftSeg;
unsigned char rightSeg;

void SysTick_Handler(void)
{
		ticks++;
	
		if(ticks == 100)
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
	LPC_SC->PCONP |= (1UL<<21); //Power Control
	LPC_PINCON->PINSEL1 |= (2UL<<4); //P0.18 MOSI0 (Master Output Slave Input)
	LPC_PINCON->PINSEL1 |= (2UL<<2); //P0.17 MISO0 (Master Input Slave Output)
	
	LPC_PINCON->PINMODE1 &=~ (3<<4); //P0.18 neither pull up nor pull down
	LPC_PINCON->PINMODE1 |=  (2<<4);
	
	LPC_PINCON->PINMODE1 &=~ (3<<2); //P0.17 neither pull up nor pull down
	LPC_PINCON->PINMODE1 |=  (2<<2);
	
	LPC_PINCON->PINSEL0 |= (2UL<<30); //P0.15 SCK0 Serial Clock from Master
	LPC_PINCON->PINSEL1 |= (2UL<<0);  //P.16 SSEL0 Select Slave
	
	LPC_SC->PCLKSEL1 |= (1UL<<10); //SCLK_SSP0 = CCLK
	
	LPC_SSP0->CR0 |= (7UL<<0); //Data Size
	
	LPC_SSP0->CPSR = 100; //Prescaler -> Bitrate = 1MHz
	
	LPC_SSP0->CR1 &= ~(1UL<<0); //Control Register Normal Mode
	LPC_SSP0->CR1 &= ~(1UL<<2); //SSP0 is master
	
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
#if (T6_2==1)

unsigned int ticks = 0;
unsigned int sec = 0;
const unsigned char SegChars[10] = {0x24, 0xAF, 0xE0, 0xA2, 0x2B, 0x32, 0x30, 0xA7, 0x20, 0x22};

uint8_t seg1Temp = 0;
uint8_t seg2Temp = 0;
uint8_t seg3Temp = 0;
uint8_t seg4Temp = 0;



void SysTick_Handler(void)
{
		ticks++;
	
		if(ticks == 100)
		{
			sec++;
			ticks = 0;
			
			if (sec > 59)
			{
				sec = 0;
			}
		}
		seg1Temp = SegChars[(sec/10)%10];
		seg2Temp = SegChars[(sec%10)];
		
}

int32_t out7seg (uint8_t seg1, uint8_t seg2, uint8_t seg3, uint8_t seg4)
{
	
	
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
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test6.2: I2C-Bus ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8       ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"sec:");
	
	I2C1_Init();
	
	
	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_3
//================================================================================
#if (T6_3==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_4
//================================================================================
#if (T6_4==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T6_5
//================================================================================
#if (T6_5==1)

int main(void)
{	

	while(1)
	{
		
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

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

