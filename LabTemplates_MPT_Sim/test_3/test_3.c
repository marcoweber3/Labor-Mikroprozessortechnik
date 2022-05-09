/******************************************************************************

test_3.c

	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
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


//================================================================================
//Definition v. Konstanten:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24

//================================================================================
//  Test T3_1
//================================================================================
#if (T3_1 == 1) //3.1

unsigned int tick = 0;
void SysTick_Handler(void)
	{
		tick++;
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
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"LED0 flashes"); 
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"50ms on, 150ms off,"); 
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"50ms on, 750 ms off"); 
	
	GLCD_Simulation();
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	//SysTick_Config(100000000/100); 
	SysTick_Handler();
	
	LED_Init();
	
	while(1)
	{
		if (tick < 5) //50ms on
		{
			LED_On(0);
		}
		else if (tick < 20) //150ms off
		{
			LED_Off(0);
		}
		else if (tick < 25) //50ms on
		{
			LED_On(0);
		}
		else //750ms off
		{
			LED_Off(0);
			
			if (tick > 100)
			{
				tick = 0;
			}
		}
		

		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Main-Funktion Versuchsteil T3_2
//================================================================================
#if (T3_2 == 1) //3.2

unsigned int PRIO_EINT1_IRQN = 3;
unsigned int count_TA12_int = 0;

	void EINT1_IRQ_Int(void)
	{
		//LPC_SC->PCONP|=(1<<15);// GPIO Power
		//LPC_PINCON->PINSEL4 &= (3<<0);// P2.0 (PWM1.1) is GPIO
		LPC_GPIO2->FIODIR &= ~(1<<11); //Pin as Input
		
		//LPC_PINCON->PINSEL4 &= ~(3<<22);// reset Bits 26, 27
		LPC_PINCON->PINSEL4 |= (1<<22); // select EINT1 (fkt 01)

		// P2.11 neither on-chip pull-up nor down
		//LPC_PINCON->PINMODE4 &= ~(3<<22);//reset Bits
		LPC_PINCON->PINMODE4 |= (2<<22);
		
		LPC_SC->EXTMODE |= (1<<1);// EINT1: edge UM3.6.1
		LPC_SC->EXTPOLAR &=~(1<<1);// 0:low/falling, 1:high/rising
		
		NVIC_SetPriority(EINT1_IRQn, PRIO_EINT1_IRQN);// Prio = 13 from 0..31
		// Clear pending bit of EINTX (0<=x<=3)
		LPC_SC->EXTINT = (1UL<<1); //Clear pending Bit of EXTINT1
		NVIC_ClearPendingIRQ(EINT1_IRQn);
		NVIC_EnableIRQ(EINT1_IRQn); // enable Interrupt
	}
		
	void EINT1_IRQHandler(void)
	{
		LPC_SC->EXTINT = (1<<1);
		count_TA12_int++;
	}
	
int main(void)
{	
	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.2: Count TA12 ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	//GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Bljad"); 

	
	GLCD_Simulation();
	
	EINT1_IRQ_Int();


	while(1)
	{
		GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"TA12 counter: ");
		GLCD_DisplayString(4,14,FONT_16x24,(unsigned char*)lcd_dez(count_TA12_int));
		GLCD_Simulation();		
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Main-Funktion Versuchsteil T3_3
//================================================================================
#if (T3_3 == 1) //3.3

	int count_GPIOINT_left_Int = 0;
	int count_GPIOINT_right_Int = 0;
	int count_GPIOINT_up_Int = 0;
	int count_GPIOINT_down_Int = 0;
	
void EINT3_IRQHandler(void)
{
	if (Get_LeftStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<25);
		count_GPIOINT_left_Int++;
	}
	else if (Get_RightStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<28);
		count_GPIOINT_right_Int++;
	}
	else if (Get_UpStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<21);
		count_GPIOINT_up_Int++;
	}
	else if (Get_DownStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<27);
		count_GPIOINT_down_Int++;
	}
	else if (Get_CenterStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<3);
		count_GPIOINT_left_Int = 0;
		count_GPIOINT_right_Int = 0;
	  count_GPIOINT_up_Int = 0;
	  count_GPIOINT_down_Int = 0;
	}
}
	

int main(void)
{	
	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.2: Count TA12 ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	//GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Bljad"); 
	
	JoyStick_IRQ_Init();

	
	GLCD_Simulation();
	
	while(1)
	{
		GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"up:");
		GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"down:");
		GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"left:");
		GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"right:");
		
		GLCD_DisplayString(4,7,FONT_16x24,(unsigned char*)lcd_dez(count_GPIOINT_up_Int));
		GLCD_DisplayString(5,7,FONT_16x24,(unsigned char*)lcd_dez(count_GPIOINT_down_Int));
		GLCD_DisplayString(6,7,FONT_16x24,(unsigned char*)lcd_dez(count_GPIOINT_left_Int));
		GLCD_DisplayString(7,7,FONT_16x24,(unsigned char*)lcd_dez(count_GPIOINT_right_Int));
		
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Main-Funktion Versuchsteil T3_4
//================================================================================
#if (T3_4 == 1) //3.4

uint8_t value = 0;
uint8_t dir = 0;

	int UpStateBefore = 0;
	int DownStateBefore = 0;
	
int speed = 9;

unsigned int time = 50; //500ms

unsigned int tick = 0;

void SysTick_Handler(void)
	{
		tick++;
	}

	void EINT3_IRQHandler(void)
{
	if (Get_LeftStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<25);
		dir = 1;
	}
	else if (Get_RightStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<28);
		dir = 0;
	}
	else if (Get_UpStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<21);
		
		if(time <= 95)
		{
			time += 5;
			tick = 0;

		}
		if(speed >= 2)
		{
			speed--;
		}

	}
	else if (Get_DownStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<27);
		
		if(time >= 15)
		{
			time -= 5;
			tick = 0;
		}
		if(speed <= 18)
		{
			speed++;
		}

	}
	else if (Get_CenterStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<3);
		value = Get_SwitchPos();
	}
}

int main(void)
{	
	LED_Init();
	RGB_Init();
	Switch_Init();
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.4:running light");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"running light with"); 
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"S-Tick"); 
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Speed:"); 	
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"Direction"); 
	GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"LEDs:"); 
	
	JoyStick_IRQ_Init();
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	//SysTick_Config(100000000/100); 
	SysTick_Handler();
			
	GLCD_Simulation();

	while(1)
	{	
		if (time == 100)
		{
			RGB_On(1);
			RGB_Off(0);
			RGB_Off(2);
		}
		else if (time == 10)
		{
			RGB_On(2);
			RGB_Off(0);
			RGB_Off(1);
		}
		else
		{
			RGB_On(0);
			RGB_Off(2);
			RGB_Off(1);
		}
		if (tick >= time)
		{
			rolchar(&value, dir);
			LED_Out(value);
			tick = 0;
		}
		
		

	GLCD_DisplayString(6,8,FONT_16x24,(unsigned char*)lcd_dez(speed)); 	
		
		if (dir == 0)
		{
			GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"counterclock"); 
		}
		else if (dir == 1)
		{
			GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"clockwise    "); 
		}
		
	GLCD_DisplayString(9,0,FONT_16x24,(unsigned char*)lcd_hex(value)); 
		
		
		GLCD_Simulation();
		
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T3_5
//================================================================================
#if (T3_5 == 1)

int count_encoder = 1;

void EINT0_IRQHandler(void)
{
	LPC_SC->EXTINT = (1<<1);
	count_encoder = 1;
	LPC_SC->EXTINT = (1<<0);
}

void EINT3_IRQHandler(void)
{
 if (GPIOGetValue(0,23))
 {
	 if (GPIOGetValue(0,24))
	 {
		 if(count_encoder >= 2)
		 {
			 count_encoder--;
		 }
		 else if (count_encoder == 1)
		 {
			 count_encoder = 5;
		 }
	 }
	 else
	 {
		 if(count_encoder <= 4)
		 {
			 count_encoder++;
		 }
		 else if (count_encoder == 5)
		 {
			 count_encoder = 1;
		 }
	 }
	LPC_GPIOINT->IO0IntClr |= (1<<23);
 }
 
}
	
int main(void)
{	
	
	Encoder_Init();
	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" Test3.5: encoder ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(LightGrey); // Text color

	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Menue 1:"); 
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Menue 2:"); 
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"Menue 3:"); 
	GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"Menue 4:"); 
	GLCD_DisplayString(9,0,FONT_16x24,(unsigned char*)"Menue 5:"); 
	
	GLCD_Simulation();
	while(1)
	{

	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"counter:");
	GLCD_DisplayString(4,8,FONT_16x24,(unsigned char*)lcd_dez(count_encoder));
	switch (count_encoder)
	{
		case 1:
				GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Menue 1:");
				
				GLCD_SetTextColor(LightGrey); // Text color

				GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Menue 2:"); 
				GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"Menue 3:"); 
				GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"Menue 4:"); 
				GLCD_DisplayString(9,0,FONT_16x24,(unsigned char*)"Menue 5:"); 
		break;
		case 2:
				GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Menue 2:"); 
		
				GLCD_SetTextColor(LightGrey); // Text color
				GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Menue 1:"); 
				GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"Menue 3:"); 
				GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"Menue 4:"); 
				GLCD_DisplayString(9,0,FONT_16x24,(unsigned char*)"Menue 5:"); 
		break;
		case 3:
				GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"Menue 3:"); 
		
				GLCD_SetTextColor(LightGrey); // Text color
				GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Menue 1:"); 
				GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Menue 2:");  
				GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"Menue 4:"); 
				GLCD_DisplayString(9,0,FONT_16x24,(unsigned char*)"Menue 5:"); 
		break;
		case 4:
				GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"Menue 4:"); 
		
				GLCD_SetTextColor(LightGrey); // Text color
				GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Menue 1:"); 
				GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Menue 2:"); 
				GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"Menue 3:"); 
				GLCD_DisplayString(9,0,FONT_16x24,(unsigned char*)"Menue 5:"); 
		break;
		case 5:
				GLCD_DisplayString(9,0,FONT_16x24,(unsigned char*)"Menue 5:"); 
		
				GLCD_SetTextColor(LightGrey); // Text color
				GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"Menue 1:"); 
				GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"Menue 2:"); 
				GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"Menue 3:"); 
				GLCD_DisplayString(8,0,FONT_16x24,(unsigned char*)"Menue 4:"); 
		break;
	}
	
			GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Test T3_6
//================================================================================
#if (T3_6 == 1)

int h = 0;
int min = 0;
int s = 0;
int _h = 0;
int _min = 0;
int _s = 0;

int edit = 0;
int pos = 0;

int CenterStateBefore = 0;
int Get_UpStatBefore = 0;
int Get_DownStatBefore = 0;

void editTime(void)
{
	
	switch (pos)
	{
		case 0:

			if ((Get_UpStat() != Get_UpStatBefore) && Get_UpStat() == 1 && _h <= 23)
			{
				_h += 1;
			}
			else if ((Get_UpStat() != Get_UpStatBefore) && Get_UpStat() == 1 && _h == 24)
			{
				_h = 1;
			}
			if ((Get_DownStat() != Get_DownStatBefore) && Get_DownStat() == 1 && _h >= 1)
			{
				_h -= 1;
			}
			else if ((Get_DownStat() != Get_DownStatBefore) && Get_DownStat() == 1 && _h == 0)
			{
				_h = 23;
			}
			Get_UpStatBefore = Get_UpStat();
			Get_DownStatBefore = Get_DownStat();
		break;
		case 1:

			if ((Get_UpStat() != Get_UpStatBefore) && Get_UpStat() == 1 && _min <= 59)
			{
				_min += 1;
			}
			else if((Get_UpStat() != Get_UpStatBefore) && Get_UpStat() == 1 && _min == 60)
			{
				_min = 1;
			}
			if ((Get_DownStat() != Get_DownStatBefore) && Get_DownStat() == 1 && _min >= 1)
			{
				_min -= 1;
			}
			else if((Get_DownStat() != Get_DownStatBefore) && Get_DownStat() == 1 && _min == 0)
			{
				_min = 59;
			}
			Get_UpStatBefore = Get_UpStat();
			Get_DownStatBefore = Get_DownStat();
		break;
		case 2:
	
			if ((Get_UpStat() != Get_UpStatBefore) && Get_UpStat() == 1 && _s <=59)
			{
				_s += 1;
			}
			else if((Get_UpStat() != Get_UpStatBefore) && Get_UpStat() == 1 && _s == 60)
			{
				_s = 1;
			}
			
			if ((Get_DownStat() != Get_DownStatBefore) && Get_DownStat() == 1 && _s >= 1)
			{
				_s -= 1;
			}
			else if((Get_DownStat() != Get_DownStatBefore) && Get_DownStat() == 1 && _s == 0)
			{
				_s = 59;
			}
			Get_UpStatBefore = Get_UpStat();
			Get_DownStatBefore = Get_DownStat();
		break;
		}
}

unsigned int tick = 0;
void SysTick_Handler(void)
	{
		tick++;
	}

void EINT3_IRQHandler(void)
{
	if (Get_LeftStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<25);
		if (pos > 0)
		{
			pos -=1;
		}
		else if (pos == 0)
		{
			pos = 2;
		}
	}
	else if (Get_RightStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<28);
		
		if (pos < 2)
		{
			pos +=1;
		}
		else if (pos == 2)
		{
			pos = 0;
		}
	}
	else if (Get_UpStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<21);


	}
	else if (Get_DownStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<27);
		

	}
	else if (Get_CenterStat())
	{
		LPC_GPIOINT->IO0IntClr |= (1<<3);
		
				if (Get_CenterStat() && edit == 0)
				{
					edit = 1;
					_s = s;
					_min = min;
					_h = h;
				}
				else if (Get_CenterStat() && edit == 1)
				{
					edit = 0;
					h = _h;
					min = _min;
					s = _s;
				}
	}
}


	

int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(DarkGreen); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)" Lab Microproc-Lab     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)"Test3.6: time of day");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	GLCD_DisplayString(4,0,FONT_16x24,(unsigned char*)"Actual time of day:"); 
	GLCD_DisplayString(6,6,FONT_16x24,(unsigned char*)":"); 
	GLCD_DisplayString(6,9,FONT_16x24,(unsigned char*)":"); 	


	
	JoyStick_IRQ_Init();
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	//SysTick_Config(100000000/100); 
	SysTick_Handler();
			
	GLCD_Simulation();


	while(1)
	{	
		if (edit == 0)
		{
			if (tick >= 100)
			{
				s += 1;
				tick = 0;
			}
			if (s >= 60)
			{
				s = 0;
				min+=1;
			}
			if (min >= 60)
			{
				min = 0;
				h +=1;
			}
			if (h >= 24)
			{
				h = 0;
			}
		}
		
		if (edit == 1)
		{
			editTime();
			if (pos == 0)
			{
				GLCD_SetTextColor(Red); // Text color
				GLCD_DisplayString(6,4,FONT_16x24,(unsigned char*)lcd_dez2(_h));
				GLCD_SetTextColor(LightGrey);
				GLCD_DisplayString(6,7,FONT_16x24,(unsigned char*)lcd_dez2(_min));
				GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*)lcd_dez2(_s));
			}
			else if (pos == 1)
			{
				GLCD_SetTextColor(Red); // Text color
				GLCD_DisplayString(6,7,FONT_16x24,(unsigned char*)lcd_dez2(_min));
				GLCD_SetTextColor(LightGrey);
				GLCD_DisplayString(6,4,FONT_16x24,(unsigned char*)lcd_dez2(_h));
				GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*)lcd_dez2(_s));
			}
			else if (pos == 2)
			{
				GLCD_SetTextColor(Red); // Text color
				GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*)lcd_dez2(_s));
				GLCD_SetTextColor(LightGrey);
				GLCD_DisplayString(6,4,FONT_16x24,(unsigned char*)lcd_dez2(_h));
				GLCD_DisplayString(6,7,FONT_16x24,(unsigned char*)lcd_dez2(_min));
			}
		}
		else if (edit == 0)
		{
				GLCD_SetTextColor(Black); // Text color

				GLCD_DisplayString(6,4,FONT_16x24,(unsigned char*)lcd_dez2(h));
				GLCD_DisplayString(6,7,FONT_16x24,(unsigned char*)lcd_dez2(min));
				GLCD_DisplayString(6,10,FONT_16x24,(unsigned char*)lcd_dez2(s));
		}
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T3_7
//================================================================================

#if (T3_7 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif

