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

#define FONT_6x8   0     //Font-Index f?r ASCII Font 6x8
#define FONT_16x24 1     //Font-Index f?r ASCII Font 16x24


//================================================================================
//  test T51
//================================================================================
#if (T5_1==1) //5.1 Counter with TA10

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
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Press button TA10");
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
#if (T5_2==1)//5.2 Interrupt on timer reset

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
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Red); // Background color
	GLCD_SetTextColor(Blue); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test5.2: Timer reset ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Timer Counter:");

	GPIOSetDir(2, 5, 1);
	
	Timer_Init(0,10000,10000000,1,0);//timer0, counts: 0..999, divider=100?, pclk=cclk, reset with MR0 -> (100000000/s) / (1000*100*1) = 1000/s -> 1ms

	LPC_TIM0->TCR=(1<<0);//start timer 0
	
	GLCD_Simulation();	

	while(1)
	{
		tcvalue=LPC_TIM0->TC; // Timer Counter auslesen
		GLCD_DisplayString(5,16,FONT_16x24,(unsigned char*)lcd_dez(tcvalue));
		GLCD_Simulation();	
	}
}

#endif

//
//================================================================================
//  test T53
//================================================================================
#if (T5_3==1) //5.3 Meassure high and low time of PWM

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
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test5.3: Measure PWM ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"HighTime: ");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"LowTime: ");
	
	GLCD_Simulation();	
	
	GPIOSetDir(2, 5, 1);
	
	Timer_Init(0,1000,100000,1,0);//timer0, counts: 0..999, divider=10?, pclk=cclk, reset with MR0 -> (100000000/s) / (1000*100*1) = 1000/s -> 1ms
	
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
		GLCD_DisplayString(4,11,FONT_16x24,(unsigned char*)lcd_dez(highTime*10));
		GLCD_DisplayString(5,11,FONT_16x24,(unsigned char*)lcd_dez(lowTime*10));
		
		GLCD_Simulation();	
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  test T54
//================================================================================
#if (T5_4==1) //5.4 RGB LED with PWM

uint32_t dutyCycleR = 100;
uint32_t dutyCycleG = 100;
uint32_t dutyCycleB = 100;

uint32_t potiState = 40950;



void TIMER2_IRQHandler(void) // Green Handler
{
	GPIOToggle(2,4);
	if (LPC_TIM2->IR & (1<<1)) //Interrupt MR1 Green
	{
		
		if(LPC_TIM2->MR1 == 0) 
		{
			LPC_TIM2->MR1 = dutyCycleG; //CounterState at which action occurs
		}
		else
		{
			LPC_TIM2->MR1 = 0; //CounterState at which action occurs
		}
		LPC_TIM2->IR = (1<<1); //Reset pending bit
	}
} 

void TIMER3_IRQHandler(void) //Red & Blue Handler
{
	GPIOToggle(2,5);
	LPC_TIM3->IR = (1<<2);
	if (LPC_TIM3->IR & (1<<1)) //Interrupt MR1 Red
	{
		
		if(LPC_TIM3->MR1 == 0)
		{
			LPC_TIM3->MR1 = dutyCycleR; //CounterState at which action occurs
		}
		else
		{
			LPC_TIM3->MR1 = 0; //CounterState at which action occurs
		}
		LPC_TIM3->IR = (1<<1); //Reset pending bit
	}
	
	
	if (LPC_TIM3->IR & (1<<0)) //Interrupt MR0 Blue    
	{
		
		
		if(LPC_TIM3->MR0 == 0)
		{
			LPC_TIM3->MR0 = dutyCycleB; //CounterState at which action occurs
		}
		else
		{
			LPC_TIM3->MR0 = 0; //CounterState at which action occurs
		}
		LPC_TIM3->IR = (1<<0); //Reset pending bit
	}
}


int main(void)
{	
	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Red); // Background color
	GLCD_SetTextColor(Blue); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test5.4: PWM LEDs ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Red:");
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Green:");
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Blue:");
	GLCD_Simulation();	
	
	ADC_Init((1<<4), 0);
	Switch_Init();
	Init_Input();
	RGB_Init();
	
	GPIOSetDir(2, 5, 1);
	GPIOSetDir(2, 4, 1);
	GPIOSetDir(2, 3, 1);
	
	Timer_Init (2,1000,100000,1,0); //timer2, counts: 0..999, divider=10?, pclk=cclk, reset with MR0 -> (100000000/s) / (1000*100*1) = 1000/s -> 1ms
	LPC_PINCON->PINSEL9 |= (2UL<<26);		//Activate MAT2.1 Green
	LPC_TIM2->EMR |= (3UL<<6); //Toggle MAT2.1 at match
	LPC_TIM2->MR1 = dutyCycleG; //CounterState at which action occurs
	LPC_TIM2->MCR |= (1UL<<3);  //Interrupt at match
	
	Timer_Init (3,1000,100000,1,2); //timer3, counts: 0..999, divider=10?, pclk=cclk, reset with MR0 -> (100000000/s) / (1000*100*1) = 1000/s -> 1ms
	LPC_PINCON->PINSEL0 |= (3<<20);		//Activate MAT3.0 Blue
	LPC_TIM3->EMR |= (3UL<<4); //Toggle MAT3.0 at match
	LPC_TIM3->MR0 = dutyCycleB; //CounterState at which action occurs
	LPC_TIM3->MCR |= (1UL<<0);  //Interrupt at match
	
	LPC_PINCON->PINSEL0 |= (3<<22);	//Activate MAT3.1 Red
	LPC_TIM3->EMR |= (3UL<<6); //Toggle MAT3.1 at match
	LPC_TIM3->MR1 = dutyCycleR; //CounterState at which action occurs
	LPC_TIM3->MCR |= (1UL<<3);  //Interrupt at match

	NVIC_SetPriority(TIMER2_IRQn, 17); //priority
	NVIC_ClearPendingIRQ (TIMER2_IRQn); // Pending bits 
	NVIC_EnableIRQ(TIMER2_IRQn);
	
	NVIC_SetPriority(TIMER3_IRQn, 16); //priority
	NVIC_ClearPendingIRQ (TIMER3_IRQn); //clear pending bits 
	NVIC_EnableIRQ(TIMER3_IRQn);
	
	
	LPC_TIM2->TCR = (1<<1); //Reset von Timer2
	LPC_TIM2->TCR = (1<<0); //Start von Timer2
	
	LPC_TIM3->TCR = (1<<1); //Reset von Timer3
	LPC_TIM3->TCR = (1<<0); //Start von Timer3
	
	//ADC_StartCnv ((1<<4), 0); //Start ADC Conversion
	
	while(1)
	{
		
//		if((ADC_Stat ()>>4)&1)
//		{	
			ADC_StartCnv ((1<<4), 0); //Start ADC Conversion
			while (!((ADC_Stat()>>4)&1));//wait for end of conversion
			potiState = ADC_GetValue(4)*1000; //output result4 to the LCD
			
		
			
			if(Get_SwitchPos() == 128) //S7
			{
				dutyCycleR = potiState / 40950;
			}
			else if(Get_SwitchPos() == 64) //S6
			{
				dutyCycleG = potiState / 40950;
			}
			else if(Get_SwitchPos() == 32) //S5
			{
				dutyCycleB = potiState / 40950;
			}

			GLCD_DisplayString(4,8,FONT_16x24,(unsigned char*)lcd_dez(dutyCycleR));
			GLCD_DisplayString(5,8,FONT_16x24,(unsigned char*)lcd_dez(dutyCycleG));
			GLCD_DisplayString(6,8,FONT_16x24,(unsigned char*)lcd_dez(dutyCycleB));
			
			GLCD_Simulation();	
			GPIOToggle(2,3);
	} // end while(1)
}	// end main()

#endif
//
//================================================================================
//  test T5_55
//================================================================================
#if (T5_5==1) //5.5 warbling square wave

int period = 12500;
int dir = 1;

void TIMER0_IRQHandler(void){
	
	if(LPC_TIM0->IR & (1<<0))
	{
		LPC_TIM0->IR |= (1<<0); //reset pending bit
		
		if (period >= 25000)
		{
			dir = 0;
		}
		else if (period <=  12500)
		{
			dir = 1;
		}
		
		if (dir == 1)
		{
			period += 50;
		}
		else if (dir == 0)
		{
			period -= 50;
		}
		
		LPC_TIM0->MR0 = period; //CounterState at which action occurs
	
	}
}

int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Red); // Background color
	GLCD_SetTextColor(Blue); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test5.5: Speaker ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Period:");
	GLCD_Simulation();	
	
	Timer_Init (0,12500,10000000,1,0);
	LPC_PINCON->PINSEL3 |= (3UL<<24); //Activate MAT0.0
	LPC_TIM0->EMR |= (3UL<<4); //Toggle Pin at match
	
	while(1)
	{
			GLCD_DisplayString(5,9,FONT_16x24,(unsigned char*)lcd_dez(period));
			GLCD_Simulation();	
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  test T5_6
//================================================================================
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
#if (T5_7==1) //5.4 Alternative 

uint32_t dutyCycleR=50, dutyCycleB=50, dutyCycleG=50;
uint8_t a=50;
uint32_t zaehler=0;

void PWM_Init(void)
{
	unsigned char k;
	//unsigned char pin;
	LPC_SC->PCONP |=(1<<15); //Power GPIO-Block
	
	LPC_PINCON->PINSEL4 &= ~(3<<0); //GPIO - Funktionen f?r Portpin P2.0
	LPC_PINCON->PINSEL3 &= ~(3<<2); //GPIO - Funktionen f?r Portpin P2.1
	LPC_PINCON->PINSEL3 &= ~(3<<4); //GPIO - Funktionen f?r Portpin P2.2
	LPC_PINCON->PINSEL4 &= ~(3<<6); //GPIO - Funktionen f?r Portpin P2.3
	LPC_PINCON->PINSEL3 &= ~(3<<8); //GPIO - Funktionen f?r Portpin P2.4
	LPC_PINCON->PINSEL3 &= ~(3<<10); //GPIO - Funktionen f?r Portpin P2.5
	
	for(k = 0; k < 6; k++)
	{
		GPIOSetDir(2,k, GPIO_OUTPUT);
		GPIOSetValue(2,k, 0);
		
		//Nighter pull up nor pulldown
		LPC_PINCON->PINMODE4 &=~(3<<(k*2));
		LPC_PINCON->PINMODE4 |=(2<<(k*2));
		//PWMENA 
	}
	
}


void TIMER3_IRQHandler(void)
{
	if(LPC_TIM3->IR &(1<<1)) //MR1 augel?st
	{
		LPC_TIM3->IR=(1<<1);		//pending bit
		
		//MR1 wechselt zwischen dutyCycleR und 0 hin und her, damite er bei 0 aufgerufen wird und das n?chste Mal bei dutyCycleR 
	if(LPC_TIM3->MR1 == 0)
		{
			LPC_TIM3->MR1 = (dutyCycleR*10)-1;			
		}
		else
		{
			LPC_TIM3->MR1 = 0;
		}
	}
	
	if(LPC_TIM3->IR &(1<<0)) //MR0 augel?st
	{
		LPC_TIM3->IR=(1<<0);		//pending bit
		
		//MR0 wechselt zwischen dutyCycleB und 0 hin und her, damite er bei 0 aufgerufen wird und das n?chste Mal bei dutyCycleB 
		if(LPC_TIM3->MR0 == 0)
			{
				LPC_TIM3->MR0 = (dutyCycleB*10)-1;			
			}
		else
			{
				LPC_TIM3->MR0 = 0;
			}
	}
		
	if(LPC_TIM3->IR &(1<<2)) //MR2 augel?st, Reset TIM3
	{
		LPC_TIM3->IR=(1<<2);		//pending bit
		GPIOToggle(2,5);				// P2.5 Toggeln
	}
}


void TIMER2_IRQHandler(void)
{
	if(LPC_TIM2->IR &(1<<1)) //MR1 augel?st
	{
		LPC_TIM2->IR=(1<<1);		//pending bit
		
		//MR1 wechselt zwischen dutyCycleG und 0 hin und her, damite er bei 0 aufgerufen wird und das n?chste Mal bei dutyCycleG
		if(LPC_TIM2->MR1 == 0)
			{
				LPC_TIM2->MR1 = (dutyCycleG*10)-1;			
			}
			else
			{
				LPC_TIM2->MR1 = 0;
			}
		}
			
		if(LPC_TIM2->IR &(1<<0)) //MR0 augel?st, Reset TIM2
		{
			LPC_TIM2->IR=(1<<0);		//pending bit
			//GPIOtoggle(2,5);				// P2.5 Toggeln
		}
}



void ADC_IRQHandler(void)
{
	if (ADC_Stat() & (1<<4))
	{
		a = (ADC_GetValue(4)*100)/4095;
		
		if(a <= 0) a=1;
		if(a>=100) a=99;
	}
}

int main(void)
{	
	Switch_Init();
	//LED_Init();
	ADC_Init((1<<4),1);
	RGB_Init();
	//Joystick_Init();
	//Matrix_Init();
	button_Init();
	//JoyStick_IRQ_Init();
	//Encoder_Init();
	//GPIOSetDir(2,0,GPIO_OUTPUT);	
	PWM_Init();
	//DAC_Init();
	
	SystemCoreClockUpdate();
	//counter_Init();
	
	
	
	GLCD_Init();                               // Initialize graphical LCD
	GLCD_Clear(White);
	GLCD_SetBackColor(Red);
	GLCD_SetTextColor(Green);
	GLCD_DisplayString(0, 0, FONT_16x24, (unsigned char *)" Lab Microprocessor");
	GLCD_DisplayString(1, 0, FONT_16x24, (unsigned char *)"Test5.4: Control RGB LED");
	GLCD_DisplayString(2, 0, FONT_16x24, (unsigned char *)"APB1");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, FONT_16x24, (unsigned char *)"dutyCycleR: ");
	GLCD_DisplayString(5, 0, FONT_16x24, (unsigned char *)"dutyCycleG: ");
	GLCD_DisplayString(6, 0, FONT_16x24, (unsigned char *)"dutyCycleB:");
//	GLCD_DisplayString(6, 0, FONT_16x24, (unsigned char *)"Lowtime: ");
//	GLCD_DisplayString(6, 15, FONT_16x24, (unsigned char *)"ms");


	/****************************************************************************************************/
	//Rote (MAT3.1) und Blaue (MAT3.0) RGB mit MR2
	Timer_Init(3,1000,100,1,2); //timer3, counts: 0..999, divider=100, pclk=cclk, reset with MR2
	
	LPC_PINCON->PINSEL0 |= (3<<22);//MAT3.1
	LPC_PINCON->PINSEL0 |= (3<<20);//MAT3.0
	LPC_PINCON->PINMODE0 &=~(3<<22);LPC_PINCON->PINMODE0 |=(2<<22);//neither pull nor pull down
	LPC_PINCON->PINMODE0 &=~(3<<20);LPC_PINCON->PINMODE0 |=(2<<20);//neither pull nor pull down
	
	LPC_TIM3->MR1 = 0;
	LPC_TIM3->MR0 = 0;
	LPC_TIM3->MCR |=(1<<3); // Interrupt on MR1
	LPC_TIM3->MCR |=(1<<0); // Interrupt on MR0
	LPC_TIM3->EMR |=(3<<6); //Toggle des zugeh?rigen externen Matches (MAT3.1) bei InterruptHandlerAufruf
	LPC_TIM3->EMR |=(3<<4); //Toggle des zugeh?rigen externen Matches (MAT3.0) bei InterruptHandlerAufruf
	
	
	
	//Gr?ne (MAT2.1) RGB mit MR0
	Timer_Init(2,1000,100,1,0);
	
	LPC_PINCON->PINSEL9 &= ~(3<<26);LPC_PINCON->PINSEL9 |= (2<<26);//MAT2.1
	LPC_PINCON->PINMODE9 &=~(3<<26);LPC_PINCON->PINMODE9 |=(2<<26);//neither pull nor pull down
	
	LPC_TIM2->MR1 = 0;
	LPC_TIM2->MCR |=(1<<3); // Interrupt on MR1
	LPC_TIM2->EMR |=(3<<6); //Toggle des zugeh?rigen externen Matches (MAT2.1) bei InterruptHandlerAufruf
	/*********************************************************************************************************/
	
	
	



	LPC_TIM3->TCR=(1<<0);//start timer 3
	LPC_TIM2->TCR=(1<<0);//start timer 2	


	ADC_StartCnv((1<<4),1);
	while(1)
	{
//		zaehler ++;
//		if((zaehler == 1000000) && (dutyCycleR<100))
//		{
//			zaehler = 0;
//			dutyCycleR = dutyCycleR +10;
//		}
//		if((zaehler == 1000000) && (dutyCycleR>=100))
//		{
//			zaehler = 0;
//			dutyCycleR = 0;
// 		}
		
		if(Get_SwitchPos() & (1<<7))
		{
			dutyCycleR =a;
		}
		if(Get_SwitchPos() & (1<<6))
		{
			dutyCycleB =a;
		}
		if(Get_SwitchPos() & (1<<5))
		{
			dutyCycleG =a;
		}
		
		GLCD_DisplayString(4, 15, FONT_16x24, (unsigned char *)lcd_dez(dutyCycleR));
		GLCD_DisplayString(5, 15, FONT_16x24, (unsigned char *)lcd_dez(dutyCycleG));
		GLCD_DisplayString(6, 15, FONT_16x24, (unsigned char *)lcd_dez(dutyCycleB));
	} // end while(1)
}	// end main()
#endif


