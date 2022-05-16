/*******************************************************************************

test5.c


	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//include Header Files:
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

//================================================================================
//Definition 
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24


//================================================================================
//  test T51
//================================================================================
#if (T5_1==1) //5.1

int counter = 0;
int TA10StatBefore = 0;
int value;

int main(void)
{	

	button_Init();
	counter_Init(0,0,1);
	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Red); // Background color
	GLCD_SetTextColor(Blue); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test5.1: Counter ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Press button TA11");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Timer 0: ");
	
	GLCD_Simulation();	
	
	while(1)
	{

		value = LPC_TIM0->TC;
		GLCD_DisplayString(5,8,FONT_16x24,(unsigned char*)lcd_dez(value));
		
			GLCD_Simulation();	
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  test T52
//================================================================================
#if (T5_2==1)//5.2

uint32_t tcvalue=0;

void TIMER0_IRQHandler(void)
{
	
	
	if(LPC_TIM0->IR & (1<<0))
	{
		LPC_TIM0->IR |= (1<<0); //reset interrupt flag
		GPIOToggle(2,5);
	}
}	

int main ()
{ 
	GPIOSetDir(2, 5, 1);
	
	Timer_Init(0,1000,100,1,0);//timer0, counts: 0..999, divider=100?, pclk=cclk, reset with MR0 -> (100000000/s) / (1000*100*1) = 1000/s -> 1ms

	LPC_TIM0->TCR=(1<<0);//start timer 0
	
	GLCD_Simulation();	

	while(1)
	{
		tcvalue=LPC_TIM0->TC;
		GLCD_Simulation();	
	}
}

#endif

//
//================================================================================
//  test T53
//================================================================================
#if (T5_3==1) //5.3

uint32_t timerLow = 0;
uint32_t timerHigh = 0;

uint32_t highTime = 0;
uint32_t lowTime = 0;

uint32_t timerPeriod = 400; //100us

uint32_t cycles = 0;

void TIMER0_IRQHandler(void)
{

	if (LPC_TIM0->IR & (1<<0)) //Interrupt MR0 falling
	{
		LPC_TIM0->IR = (1<<0); //Reset des pending bit
		cycles++;
		LPC_GPIO2->FIOPIN ^= (1<<5); // P2.5 toggeln lassen
	}
	else if(LPC_TIM0->IR & (1<<4)) //Capture Interrupt 0.0 rising
	{
		timerHigh = LPC_TIM0->TC;
				
		lowTime = LPC_TIM0->CR0 - LPC_TIM0->CR1 + 10000 * cycles;//(timerPeriod - timerLow) + (cycles * timerPeriod) + timerHigh;
		cycles = 0;
		
		LPC_TIM0->IR |= (1<<4); //reset interrupt flag
	
	}
	else if(LPC_TIM0->IR & (1<<5)) //Capture Interrupt 0.1 falling
	{		
		timerLow = LPC_TIM0->TC;		
		
		highTime = LPC_TIM0->CR1 - LPC_TIM0->CR0 + 10000 * cycles;//(timerPeriod - timerHigh) + (cycles * timerPeriod) + timerLow;
		cycles = 0;
		
		LPC_TIM0->IR |= (1<<5); //reset interrupt flag
	}

	
}

int main(void)
{	
	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Red); // Background color
	GLCD_SetTextColor(Blue); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test5.1: Counter ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"HighTime: ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"LowTime: ");
	
	GLCD_Simulation();	
	
	GPIOSetDir(2, 5, 1);
	
	Timer_Init(0,1000,10000,1,0);//timer0, counts: 0..999, divider=10?, pclk=cclk, reset with MR0 -> (100000000/s) / (1000*100*1) = 1000/s -> 1ms
	
	//8.3 Grundbefehle
	//Capture Interrupt 0.0 TA10
	LPC_PINCON->PINSEL3 |= (3UL<<20); //activate counter pin
	LPC_PINCON->PINMODE3 |= (2UL<<20); //neither pull-up nor pull-down
	LPC_TIM0->CCR |= (1<<0); //CAP0.0 rising edge
	LPC_TIM0->CCR |= (1<<2); //interrupt on CAP0.0 event
	
	//Capture Interrupt 0.1 TA11
	LPC_PINCON->PINSEL3 |= (3UL<<22); //activate counter pin
	LPC_PINCON->PINMODE3 |= (2UL<<22); //neither pull-up nor pull-down
	LPC_TIM0->CCR |= (1<<4); //CAP0.1 falling edge
	LPC_TIM0->CCR |= (1<<5); //interrupt on CAP0.1 event
	
	NVIC_SetPriority(TIMER0_IRQn, PRIO_CAPTURE);
	LPC_TIM0->IR |= (1<<4);
	NVIC_ClearPendingIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	while(1)
	{
		GLCD_DisplayString(4,11,FONT_16x24,(unsigned char*)lcd_dez(highTime));
		GLCD_DisplayString(5,11,FONT_16x24,(unsigned char*)lcd_dez(lowTime));
		
		GLCD_Simulation();	
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T54
//================================================================================
#if (T5_4==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif
//
//================================================================================
//  test T5_55
//================================================================================
#if (T5_5==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


#if (T5_6==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  test T5_7
//================================================================================
#if (T5_7==1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


