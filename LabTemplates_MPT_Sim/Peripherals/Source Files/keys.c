#include <LPC17xx.h>
#include "keys.h"
#include "gpio.h"
#include "prio.h"



//1.2 Get switch positions

void Switch_Init(void)
{
	//change the Portpin PX.Y to an input one time
	GPIOSetDir(1,18,0);
	GPIOSetDir(1,19,0);
	GPIOSetDir(1,20,0);
	GPIOSetDir(1,21,0);
	GPIOSetDir(1,22,0);
	GPIOSetDir(1,23,0);
	GPIOSetDir(1,24,0);
	GPIOSetDir(1,25,0);
	
	LPC_PINCON->PINMODE3&=~(0xFFFF<<4);
	LPC_PINCON->PINMODE3 |= (0xAAAA<<4);
}


unsigned char Get_SwitchPos(void)
{
	unsigned char value = 0;
	
	if(GPIOGetValue(1,25))
		{
		value += 128;
		}
	if(GPIOGetValue(1,24))
		{
		value += 64;
		}
	if(GPIOGetValue(1,23))
		{
		value += 32;
		}
	if(GPIOGetValue(1,22))
		{
		value += 16;
		}
	if(GPIOGetValue(1,21))
		{
		value += 8;
		}
	if(GPIOGetValue(1,20))
		{
		value += 4;
		}
	if(GPIOGetValue(1,19))
		{
		value += 2;
		}
	if(GPIOGetValue(1,18))
		{
		value += 1;
		}
	return value;
}


//1.3 Scan buttons

void button_Init(void)
{
	//change the Portpin PX.Y to an input one time			
	GPIOSetDir(1,26,0);
	GPIOSetDir(1,27,0);
	GPIOSetDir(2,11,0);
	
	LPC_PINCON->PINMODE3 &= ~(3 << 20);LPC_PINCON->PINMODE3 |= (2 << 20);//P1.26
	LPC_PINCON->PINMODE3 &= ~(3 << 22);LPC_PINCON->PINMODE3 |= (2 << 22);//P1.27
	LPC_PINCON->PINMODE4 &= ~(3 << 22);LPC_PINCON->PINMODE4 |= (2 << 22);//P2.11
		
}
	
unsigned int Get_TA12Stat(void)
{	
	return GPIOGetValue(2,11);
}

unsigned int Get_TA10Stat(void)
{		
	return GPIOGetValue(1,26);
}

unsigned int Get_TA11Stat(void)
{	

	return GPIOGetValue(1,27);
}


//1.5 Get Joystick
void Joystick_Init(void){
	GPIOSetDir(0,3,0);	
	GPIOSetDir(0,21,0);
	GPIOSetDir(0,25,0);
	GPIOSetDir(0,27,0);
	GPIOSetDir(0,28,0);

	LPC_PINCON->PINMODE0 &= ~(3 <<  6);LPC_PINCON->PINMODE0 |= (2 <<  6);//P0.03  
	LPC_PINCON->PINMODE1 &= ~(3 << 10);LPC_PINCON->PINMODE1 |= (2 << 10);//P0.21 
	LPC_PINCON->PINMODE1 &= ~(3 << 18);LPC_PINCON->PINMODE1 |= (2 << 18);//P0.25  
	LPC_PINCON->PINMODE1 &= ~(3 << 22);LPC_PINCON->PINMODE1 |= (2 << 22);//P0.27 
	LPC_PINCON->PINMODE1 &= ~(3 << 24);LPC_PINCON->PINMODE1 |= (2 << 24);//P0.28
}

unsigned int Get_LeftStat(void)
{
	return GPIOGetValue(0,25);
}

unsigned int Get_RightStat(void)
{
	return GPIOGetValue(0,28);
}

unsigned int Get_UpStat(void)
{
	return GPIOGetValue(0,21);
}

unsigned int Get_DownStat(void)
{
	return GPIOGetValue(0,27);
}

unsigned int Get_CenterStat(void)
{
	return GPIOGetValue(0,3);
}

unsigned int KeyFlipFlop(unsigned int stat, unsigned int statBefore) //Checks for negativ flanks
{
		if(stat == 1 && statBefore == 0)
		{
			return 0;
		}
		else if(stat != 1 && statBefore == 1)
		{
			return 1;
		}
		else
		{
			return statBefore;
		}
}
 
void JoyStick_IRQ_Init(void)
{
	LPC_SC->PCONP |= (1<<15);
	
	LPC_PINCON->PINSEL0 &=~ (3<<6); //GPIO Power
	LPC_PINCON->PINSEL1 &=~ (3<<10);
	LPC_PINCON->PINSEL1 &=~ (3<<18);
	LPC_PINCON->PINSEL1 &=~ (3<<22);
	LPC_PINCON->PINSEL1 &=~ (3<<24);
	
	GPIOSetDir(0,3,0);	//Input
	GPIOSetDir(0,21,0);
	GPIOSetDir(0,25,0);
	GPIOSetDir(0,27,0);
	GPIOSetDir(0,28,0);

	LPC_PINCON->PINMODE0 &= ~(3 <<  6);LPC_PINCON->PINMODE0 |= (2 <<  6);//P0.03  
	LPC_PINCON->PINMODE1 &= ~(3 << 10);LPC_PINCON->PINMODE1 |= (2 << 10);//P0.21 
	LPC_PINCON->PINMODE1 &= ~(3 << 18);LPC_PINCON->PINMODE1 |= (2 << 18);//P0.25  
	LPC_PINCON->PINMODE1 &= ~(3 << 22);LPC_PINCON->PINMODE1 |= (2 << 22);//P0.27 
	LPC_PINCON->PINMODE1 &= ~(3 << 24);LPC_PINCON->PINMODE1 |= (2 << 24);//P0.28
	
	LPC_GPIOINT->IO0IntEnR |= (1<<3); //rising Enge enable
	LPC_GPIOINT->IO0IntEnR |= (1<<21);
	LPC_GPIOINT->IO0IntEnR |= (1<<25);
	LPC_GPIOINT->IO0IntEnR |= (1<<27);
	LPC_GPIOINT->IO0IntEnR |= (1<<28);
	
	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_SetPriority(EINT3_IRQn, PRIO_EINT3_IRQN);
	NVIC_EnableIRQ(EINT3_IRQn);

}


void Matrix_Init(void)
{
	//rows as output
	GPIOSetDir(2, 3, 1);
	GPIOSetDir(2, 4, 1);
	GPIOSetDir(2, 5, 1);
	
	// colums as input
	GPIOSetDir(0, 4, 0);
	GPIOSetDir(0, 5, 0);
	GPIOSetDir(3,26, 0);
	
// set pinmode for inputs ?????????????????????? 	
	LPC_PINCON->PINMODE0 &= ~(3 <<  8);LPC_PINCON->PINMODE0 |= (2 <<  8);//P0.04 
	LPC_PINCON->PINMODE0 &= ~(3 << 10);LPC_PINCON->PINMODE0 |= (2 << 10);//P0.05 
	LPC_PINCON->PINMODE7 &= ~(3 << 20);LPC_PINCON->PINMODE7 |= (2 << 20);//P3.26
	
}

unsigned char Get_Mkey(void)
{
	unsigned char value = 0x20; //0x20

	GPIOSetValue(2, 3, 1);
	GPIOSetValue(2, 4, 0);
	GPIOSetValue(2, 5, 0);
	
	if(GPIOGetValue(0, 4))
	{ 
		value = '1'; 
	}
	else if(GPIOGetValue(0, 5))
	{ 
		value = '2'; 
	}
	else if(GPIOGetValue(3, 26)) 
	{ 
		value = '3'; 
	}
	else {
		GPIOSetValue(2, 3, 0);
		GPIOSetValue(2, 4, 1);
		GPIOSetValue(2, 5, 0);
		
		if(GPIOGetValue(0, 4))
		{ 
			value = '4'; 
		}
		else if(GPIOGetValue(0, 5))
		{ 
			value = '5'; 
		}
		else if(GPIOGetValue(3, 26)) 
		{ 
			value = '6'; 
		}
		else {
			GPIOSetValue(2, 3, 0);
			GPIOSetValue(2, 4, 0);
			GPIOSetValue(2, 5, 1);
			
			if(GPIOGetValue(0, 4))
			{ 
				value = '7'; 
			}
			else if(GPIOGetValue(0, 5))
			{ 
				value = '8'; 
			}
			else if(GPIOGetValue(3, 26)) 
			{ 
				value = '9'; 
			}
		}
	}
	
	
	GPIOSetValue(2, 3, 0);
	GPIOSetValue(2, 4, 0);
	GPIOSetValue(2, 5, 0);
	
	return (value);	
}	



void Encoder_Init(void)
{
	LPC_SC->PCONP |= (1<<15);
	
	//A, B
	//GPIO Power
	LPC_PINCON->PINSEL1 &=~ (3<<14); //0.23 -> 1.14
	LPC_PINCON->PINSEL1 &=~ (3<<16); //0.24 -> 1.16
	
	GPIOSetDir(0,23,0);	//Input
	GPIOSetDir(0,24,0);

	LPC_PINCON->PINMODE1 &= ~(3 <<  14);LPC_PINCON->PINMODE1 |= (2 <<  14);//P0.23  
	LPC_PINCON->PINMODE1 &= ~(3 << 16);LPC_PINCON->PINMODE1 |= (2 << 16);//P0.24

	LPC_GPIOINT->IO0IntEnR |= (1<<23); //A: rising Enge enable

	NVIC_ClearPendingIRQ(EINT3_IRQn);
	NVIC_SetPriority(EINT3_IRQn, PRIO_EINT3_IRQN);
	NVIC_EnableIRQ(EINT3_IRQn);
	
	//Center
	LPC_PINCON->PINSEL4 &=~ (3<<20); //GPIO Power
	LPC_PINCON->PINSEL4 |= (1<<20);
	LPC_PINCON->PINMODE4 &=~ (3<<20);
	LPC_PINCON->PINMODE4 |= (2<<20);
	LPC_SC->EXTMODE |= (1<<0);
	LPC_SC->EXTPOLAR |= (1<<0);
	LPC_SC->EXTINT |= (1<<0);
	NVIC_ClearPendingIRQ(EINT0_IRQn);
	NVIC_SetPriority(EINT0_IRQn, PRIO_EINT0_IRQN);
	NVIC_EnableIRQ(EINT0_IRQn);
}

	
