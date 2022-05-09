/******************************************************************************

test_4.c

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

//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//
//================================================================================
//  Test T41_1
//================================================================================
#if (T41_1==1) //4.1.1

uint32_t result3=0;

int main(void) {
	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.1: SystemTick  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"LM35 AD0.3"); 
	
	GPIOSetDir(2,0,1);
	
	ADC_Init((1<<3),0); //initialize channel 3 without interrupt -
	ADC_StartCnv ((1<<3), 0);
	
	GLCD_Simulation();

	while(1)
	{
	
		if ((ADC_Stat ()>>3)&1)
		{//wait for end of conversion
			GPIOSetValue(2,0,0); //PWM 1.1		
			result3 = ADC_GetValue(3); //output result3 to the LCD
			GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*)lcd_dez(result3));
			ADC_StartCnv ((1<<3), 0);			
			GPIOSetValue(2,0,1);
		}	
	
		GLCD_Simulation();
	}
}
#endif

//
//================================================================================
//  Test T41_2
//================================================================================
#if (T41_2==1) //4.1.2

	uint32_t result3=0;
	uint32_t result4=0;
	uint32_t result5=0;
	
int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.1: SystemTick  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Pot1 AD0.4: ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Pot2 AD0.5: ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"LM35 AD0.3: ");	
	
	ADC_Init((1<<3)|(1<<4)|(1<<5),0); //initialize channel 3 without interrupt -
	
	GLCD_Simulation();

	while(1)
	{
			ADC_StartCnv ((1<<4), 0);
			while (!((ADC_Stat ()>>4)&1));//wait for end of conversion
			result4=ADC_GetValue(4); //output result4 to the LCD
			GLCD_DisplayString(4,12,FONT_16x24,(unsigned char*) lcd_dez(result4));
			
			ADC_StartCnv ((1<<5), 0);					
			while (!((ADC_Stat ()>>5)&1));//wait for end of conversion
			result5=ADC_GetValue(5); //output result5 to the LCD
			GLCD_DisplayString(5,12,FONT_16x24,(unsigned char*) lcd_dez(result5));
			
			ADC_StartCnv ((1<<3), 0);
			while (!((ADC_Stat ()>>3)&1));//wait for end of conversion
			result3=ADC_GetValue(3); //output result3 to the LCD
			GLCD_DisplayString(6,12,FONT_16x24,(unsigned char*) lcd_dez(result3));
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Test T41_3
//================================================================================
#if (T41_3==1) //4.1.3
	
	uint32_t result3=0;
	uint32_t result4=0;
	uint32_t result5=0;
	
int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.1: SystemTick  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Pot1 AD0.4: ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Pot2 AD0.5: ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Temp.AD0.3: ");	
	
	ADC_Init((1<<3)|(1<<4)|(1<<5),0); //initialize channel 3 without interrupt -
	
	GLCD_Simulation();

	while(1)
	{
			ADC_StartCnv ((1<<4), 0);
			while (!((ADC_Stat ()>>4)&1));//wait for end of conversion
			result4=ADC_GetValue(4); //output result4 to the LCD
			GLCD_DisplayString(4,13,FONT_16x24,(unsigned char*) AD_volt(result4));
			
			ADC_StartCnv ((1<<5), 0);					
			while (!((ADC_Stat ()>>5)&1));//wait for end of conversion
			result5=ADC_GetValue(5); //output result5 to the LCD
			GLCD_DisplayString(5,13,FONT_16x24,(unsigned char*) AD_volt(result5));
			
			ADC_StartCnv ((1<<3), 0);
			while (!((ADC_Stat ()>>3)&1));//wait for end of conversion
			result3=ADC_GetValue(3); //output result3 to the LCD
			GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*) TempConv(result3));
	} // end while(1)
}	// end main()

#endif
//
//================================================================================
//  Test T41_4
//================================================================================
#if (T41_4==1) //4.1.4

	uint32_t adresult[8];
	
	void ADC_IRQHandler(void) 
	{
		uint8_t temp;
		int channel;
		temp = ADC_Stat();
			
		switch(temp)
		{
			case 8: // Für Channel 3 -> 4 Bit auf 1 (2^3 = 8)
				channel =3;						
			break;
			
			case 16: // Für Channel 4 -> 5 Bit auf 1 (2^4 = 16)
				channel =4;				
			break;
			
			case 32: // Für Channel 5 -> 6 Bit auf 1 (2^5 = 32)
				channel =5;				
			break;
		}
		adresult[channel] = ADC_GetValue(channel);
	}
	
int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.1: SystemTick  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Pot1 AD0.4: ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Pot2 AD0.5: ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Temp.AD0.3: ");	
	
	ADC_Init((1<<3)|(1<<4)|(1<<5),1); //initialize channel 3 with interrupt -
	ADC_StartCnv ((1<<3) |(1<<4)|(1<<5), 1); //start conversion with burstmode
	
	GLCD_Simulation();

	while(1)
	{
			GLCD_DisplayString(4,13,FONT_16x24,(unsigned char*) AD_volt(adresult[4]));			
			GLCD_DisplayString(5,13,FONT_16x24,(unsigned char*) AD_volt(adresult[5]));			
			GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*) TempConv(adresult[3]));
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T41_5
//================================================================================
#if (T41_5==1) //4.1.5

	uint32_t adresult[8];
	uint8_t temp = 0;
		int channel = 0;
		int i=0;
	
	void ADC_IRQHandler(void) 
	{
		GPIOSetValue(2,5,1); //PWM 1.6
		
		temp = ADC_Stat();
			
		switch(temp)
		{
			case 8: // Für Channel 3 -> 4 Bit auf 1 (2^3 = 8)
				channel =3;						
			break;
			
			case 16: // Für Channel 4 -> 5 Bit auf 1 (2^4 = 16)
				channel =4;				
			break;
			
			case 32: // Für Channel 5 -> 6 Bit auf 1 (2^5 = 32)
				channel =5;				
			break;
		}
		adresult[channel] = ADC_GetValue(channel);
		
		//for(i=0;i<100;i++) {};

		GPIOSetValue(2,5,0); //PWM 1.6
	}
	
int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.1: SystemTick  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Pot1 AD0.4: ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Pot2 AD0.5: ");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Temp.AD0.3: ");	
	
	ADC_Init((1<<3)|(1<<4)|(1<<5),1); //initialize channel 3 with interrupt -
	ADC_StartCnv ((1<<3) |(1<<4)|(1<<5), 1); //start conversion with burstmode
	
	GPIOSetDir(2,4,1);
	GPIOSetDir(2,5,1);
	
	GLCD_Simulation();

	while(1)
	{
			GPIOToggle(2,4); //PWM 1.5
			GLCD_DisplayString(4,13,FONT_16x24,(unsigned char*) AD_volt(adresult[4]));			
			GLCD_DisplayString(5,13,FONT_16x24,(unsigned char*) AD_volt(adresult[5]));			
			GLCD_DisplayString(6,13,FONT_16x24,(unsigned char*) TempConv(adresult[3]));
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T41_6
//================================================================================
#if (T41_6==1) //4.2.1

int value=0;
int up = 1;

void SysTick_Handler (void) 
    {
                
            if (value == 1023)
            { 
						up = 0;
						}
            else if (value == 0)
            { 
						up = 1;
						}
            
            if (up == 1)
            {
						value++;
						}
						else if (up == 0)
            {
						value--;
						}
                                  
    }


int main(void)
{	
		GLCD_Init();  //Initialize graphical LCD
		GLCD_Clear(White); // Clear graphical LCD display
		GLCD_SetBackColor(DarkGreen); // Background color
		GLCD_SetTextColor(Yellow); // Text color
		GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
		GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.1: SystemTick  ");
		GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
		
		GLCD_SetBackColor(White); // Background color
		GLCD_SetTextColor(Black); // Text color
		
		GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"output: triangle");
		GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Period: 200ms   ");
		GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"value: ");	
		
		GLCD_Simulation();
	
		DAC_Init();
		
		SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/10000); 
		
	while(1)
	{
			DAC_Out(value);										
			GLCD_DisplayString(6,8,FONT_16x24,(unsigned char*) lcd_dez(value));	
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T42_1
//================================================================================
#if (T42_1==1)

int degree = 0;
int section = 0;
int value = 511;

uint16_t sinus[90]={ /*sin[0,…,89 degree], mean-value=511*/
511,520,529,538,547,556,564,573,582,591,
600,609,617,626,635,643,652,660,669,677,
686,694,702,711,719,727,735,743,751,759,
767,774,782,789,797,804,811,819,826,833,
839,846,853,860,866,872,879,885,891,897,
902,908,914,919,924,930,935,940,944,949,
954,958,962,966,970,974,978,981,985,988,
991,994,997,1000,1002,1005,1007,1009,1011,1013,
1014,1016,1017,1018,1019,1020,1021,1021,1022,1022};

void SysTick_Handler (void) 
{
      switch (section)
			{
				case 0:
					value = sinus[degree];
					degree++;
				break;
				case 1:
					value = sinus[degree];
					degree--;
				break;
				case 2:
					value = 1022 - sinus[degree];
					degree++;
				break;
				case 3:
					value = 1022 - sinus[degree];
					degree--;
				break;
			}	
			
			if(degree >= 89 || degree <= 0)
			{
				section++;
			}	
				if (section > 3)
				{
					section = 0;
				}			
			DAC_Out(value);
 }


int main(void)
{	
		GLCD_Init();  //Initialize graphical LCD
		GLCD_Clear(White); // Clear graphical LCD display
		GLCD_SetBackColor(DarkGreen); // Background color
		GLCD_SetTextColor(Yellow); // Text color
		GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
		GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.1: SystemTick  ");
		GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
		
		GLCD_SetBackColor(White); // Background color
		GLCD_SetTextColor(Black); // Text color
		
		GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"output: sinus");
		GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Period: 200ms   ");
		GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"value: ");	
		
		GLCD_Simulation();
		
		DAC_Init();
		
		SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock/1000); 
		
	while(1)
	{										
			GLCD_DisplayString(6,8,FONT_16x24,(unsigned char*) lcd_dez(value));	
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T42_2
//================================================================================
#if (T42_2==1)

#include "dac.h"

#define PERIOD 200

static unsigned int ticks = 0;
unsigned int lastStart, value;

// systick handler
void SysTick_Handler(void){
	ticks++;
}

//main
int main(void)
{	
	// sin values
	uint16_t sin[90] = { /*sin[0,?,89 degree], mean-value=511*/
	511,520,529,538,547,556,564,573,582,591,
	600,609,617,626,635,643,652,660,669,677,
	686,694,702,711,719,727,735,743,751,759,
	767,774,782,789,797,804,811,819,826,833,
	839,846,853,860,866,872,879,885,891,897,
	902,908,914,919,924,930,935,940,944,949,
	954,958,962,966,970,974,978,981,985,988,
	991,994,997,1000,1002,1005,1007,1009,1011,1013,
	1014,1016,1017,1018,1019,1020,1021,1021,1022,1022};
	
	// initialize systick timer
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	
	// Initialize LCD-Display, write headlines
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,1,FONT_16x24,(unsigned char*)"Lab microprocessor");
	GLCD_DisplayString(1,3,FONT_16x24,(unsigned char*)"test4.2.1: DAC");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A.10"); //TO-DO: Set correct group

	// write data fields
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, FONT_16x24,(unsigned char*)"output:");
	GLCD_DisplayString(4, 11, FONT_16x24,(unsigned char*)"sine");
	GLCD_DisplayString(5, 0, FONT_16x24,(unsigned char*)"period:");
	GLCD_DisplayString(5, 11, FONT_16x24,(unsigned char*)lcd_dez(PERIOD));
	GLCD_DisplayString(6, 0, FONT_16x24,(unsigned char*)"value:");

	// initialize dac
	DAC_Init();
	
	// set start variable
	lastStart = ticks;
	
	while(1){
		if(ticks - lastStart < 90){
			value = sin[ticks - lastStart];
		}
		else if(ticks - lastStart == 90){
			value = 1023;
		}
		else if(ticks - lastStart < 180){
			value = sin[180 - (ticks - lastStart)];
		}
		else if(ticks - lastStart < 270){
			value = 1023 - sin[ticks - lastStart - 180];
		}
		else if(ticks - lastStart == 270){
			value = 0;
		}
		else if(ticks - lastStart < 359){
			value = 1023 - sin[360 - (ticks - lastStart)];
		}
		else{
			lastStart = ticks;
		}
		DAC_Out(value);
		//GLCD_DisplayString(6, 11, FONT_16x24,(unsigned char*)lcd_dez(value));
	} // end while(1)
}	// end main()

#endif
