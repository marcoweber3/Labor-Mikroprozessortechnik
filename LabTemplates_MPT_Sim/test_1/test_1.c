/******************************************************************************
test_1.c
******************************************************************************/


//	Autor: 
//	date: 
	       

/********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include <LPC17xx.h>
#include "tests.h"
#include "GLCD.h"
#include "gpio.h"
#include "delay.h"
#include "led.h"
#include "keys.h"

//================================================================================
//definition constants:
//================================================================================

#define RGB_Red 1
#define RGB_Green 2
#define RGB_Blue 0

//================================================================================
//  Main-Funktion Test1 T1_1
//================================================================================


#if (T1_1 == 1)

#define OUT_PORT 0
#define PORT_PIN 0

int i = 0;
unsigned int test = 0;

int main(void)
{	
	GLCD_Init();
	Switch_Init();
	LED_Init();
	Init_Input();	
	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
  LPC_GPIO0->FIODIR |= (1<<0); //change the Portpin PX.Y to an output one time
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
	
	

	
	
	while(1)
	{	
		//1.6
		LED_Out(Get_SwitchPos());
	}
	
}	// end main()


#endif


//================================================================================
//  Main-Function Test T1_2
//================================================================================
#if (T1_2 == 1)

#define OUT_PORT 0
#define PORT_PIN 0
int test = 1;

int main(void)
{	
		int TA12StateBefore = 0;
	int TA11StateBefore = 0;
	int TA10StateBefore = 0;
	
	GLCD_Init();
	Switch_Init();
	LED_Init();
	Init_Input();	
	button_Init();
	RGB_Init();
	Joystick_Init();
	

	
	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
  LPC_GPIO0->FIODIR |= (1<<0); //change the Portpin PX.Y to an output one time
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);

	

			
	while(1)
	{
		//1.7
		GLCD_Simulation();
		TA12StateBefore = RGB_FlipFlop(RGB_Red,Get_TA12Stat(),TA12StateBefore);
		TA10StateBefore = RGB_FlipFlop(RGB_Green,Get_TA10Stat(),TA10StateBefore);
		TA11StateBefore = RGB_FlipFlop(RGB_Blue,Get_TA11Stat(),TA11StateBefore);
		
	} // end while(1)
}	// end main()

#endif



//================================================================================
//  Main-Function Test T1_3
//================================================================================
#if (T1_3 == 1)

#define OUT_PORT 0
#define PORT_PIN 0
int num = 0;
int xled;

int main(void)
{	
	int LeftStateBefore = 0;
	int RightStateBefore = 0;
	int UpStateBefore = 0;
	int DownStateBefore = 0;
	int CenterStateBefore = 0;
	
	
	Joystick_Init();
	LED_Init();
	RGB_Init();

	while(1)
	{
		//prep 1.8
		GLCD_Simulation();
		LeftStateBefore = LED_FlipFlop(6,Get_LeftStat(),LeftStateBefore);
		RightStateBefore = LED_FlipFlop(2,Get_RightStat(),RightStateBefore);
		UpStateBefore = LED_FlipFlop(0,Get_UpStat(),UpStateBefore);
		DownStateBefore = LED_FlipFlop(4,Get_DownStat(),DownStateBefore);
	
		
		
		if ((num < 3) && (Get_CenterStat() != CenterStateBefore))
		{
			num++;
			
			if (num >= 3)
			{
				num = 0;
			}
		}
		
		switch (num)
		{
			case 0:
				RGB_On(0);
				RGB_Off(1);
				RGB_Off(2);
			break;
			case 1:
				RGB_On(1);
				RGB_Off(0);
				RGB_Off(2);
			break;
			case 2:
				RGB_On(2);
				RGB_Off(1);
				RGB_Off(0);
			break;
		}
			
		CenterStateBefore = Get_CenterStat();
	}		// end while(1)
	// end main()

#endif



//================================================================================
//  Main-Function TestT1_4
//================================================================================
#if (T1_4 == 1)

#define OUT_PORT 0
#define PORT_PIN 0

uint8_t value = 230;
uint8_t dir = 0;
int delay = 100;
int timer = 0;

int main(void)
{	
	int LeftStateBefore = 0;
	int RightStateBefore = 0;
	int UpStateBefore = 0;
	int DownStateBefore = 0;
	int CenterStateBefore = 0;
	
	GLCD_Init();
	Switch_Init();
	LED_Init();
	Init_Input();	
	button_Init();
	RGB_Init();
	Joystick_Init();
	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
  LPC_GPIO0->FIODIR |= (1<<0); //change the Portpin PX.Y to an output one time
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
	
	GLCD_Simulation();

	while(1)
	{
		
		
		
		if (Get_CenterStat() == 1)
		{
			value = Get_SwitchPos();
		}

		if (Get_LeftStat() == 1)
		{	
			dir = 1;
		}
		else if (Get_RightStat() == 1)
		{
			dir = 0;
		}

		if ((Get_UpStat() != UpStateBefore) && delay < 2000)
		{
			delay += 50;
			timer = 0;
		}
		if ((Get_DownStat() != DownStateBefore) && delay >= 200)
		{
			delay -= 50;
			timer = 0;
		}
		UpStateBefore = Get_UpStat();
		DownStateBefore = Get_DownStat();
		
		if (delay == 2000)
		{
			RGB_On(1);
			RGB_Off(0);
			RGB_Off(2);
		}
		else if (delay == 100)
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
		if (timer == (delay*150))
		{
			rolchar(&value, dir);
			LED_Out(value);
			timer = 0;
		}
		timer ++;
		
		GLCD_Simulation();
	} // end while(1)
}	// end main()

#endif

//================================================================================
//  Main-Function Test T1_5
//================================================================================
#if (T1_5 == 1)

int main(void)
{

	uint8_t dir=0, value;
	uint32_t DELAY_LED=5000000, DELAY_JOYSTICK=1000000;
	uint32_t delay_led=0, delay_joystick=0;
	//include the necessary init code here
	GLCD_Init();
	Switch_Init();
	LED_Init();
	Init_Input();	
	button_Init();
	RGB_Init();
	Joystick_Init();
	
	while(1)
	{ 
		delay_led++; 
		delay_joystick++;
		if (delay_led > DELAY_LED) 
		{
			delay_led=0;
			LPC_GPIO2->FIOPIN ^=(1UL<<0); //Toggle, output P2.0 (PWM2.1) to the
			// logic analyzer/ oscilloscop
			rolchar (&value,dir);
			LED_Out(value);
		}
		if (delay_joystick > DELAY_JOYSTICK) 
		{	
			delay_joystick =0;
			LPC_GPIO2->FIOPIN ^=(1UL<<1); //Toggle, output P2.1 (PWM2.2) to the
			//logic analyzer/ oscilloscop
			if (Get_RightStat()) dir=1; if (Get_LeftStat()) dir=0;
			if (Get_CenterStat())value=Get_SwitchPos();
		}
	} // end while(1)
}	// end main()

#endif


//================================================================================
//  Main-Function Test T1_6
//================================================================================
#if (T1_6 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif


//================================================================================
//  Main-Funktion Test T1_7
//================================================================================
#if (T1_7 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif




