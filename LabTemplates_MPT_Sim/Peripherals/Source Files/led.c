
#include <LPC17xx.h>
#include "gpio.h"

//#include "led.h"

void LED_Init(void)
	{
		//change the Portpins PX.Y to an output
		GPIOSetDir(0,0,1);
		GPIOSetDir(0,2,1);
		GPIOSetDir(0,22,1);
		GPIOSetDir(2,6,1);
		GPIOSetDir(2,7,1);
		GPIOSetDir(2,8,1);
		GPIOSetDir(2,12,1);
		GPIOSetDir(2,13,1);
		
		
		
		//set the Portpin PX.Y to ?0?/ 0V
		GPIOSetValue(0,0,0);
		GPIOSetValue(0,2,0);
		GPIOSetValue(0,22,0);
		GPIOSetValue(2,6,0);
		GPIOSetValue(2,7,0);
		GPIOSetValue(2,8,0);
		GPIOSetValue(2,12,0);
		GPIOSetValue(2,13,0);
		
	}
	
	
void LED_On(unsigned int num)
{
	switch(num)
	{
		case 0:
			GPIOSetValue(0,0,1);
		break;
		case 1:
			GPIOSetValue(0,2,1);
		break;
		case 2:
			GPIOSetValue(0,22,1);
		break;
		case 3:
			GPIOSetValue(2,6,1);
		break;
		case 4:
			GPIOSetValue(2,7,1);
		break;
		case 5:
			GPIOSetValue(2,8,1);
		break;
		case 6:
			GPIOSetValue(2,12,1);
		break;
		case 7:
			GPIOSetValue(2,13,1);
		break;
		default:
		break;
		}
}

void LED_Off(unsigned int num)
{
	switch(num)
	{
		case 0:
			GPIOSetValue(0,0,0);
		break;
		case 1:
			GPIOSetValue(0,2,0);
		break;
		case 2:
			GPIOSetValue(0,22,0);
		break;
		case 3:
			GPIOSetValue(2,6,0);
		break;
		case 4:
			GPIOSetValue(2,7,0);
		break;
		case 5:
			GPIOSetValue(2,8,0);
		break;
		case 6:
			GPIOSetValue(2,12,0);
		break;
		case 7:
			GPIOSetValue(2,13,0);
		break;
		default:
		break;
		}
}

void LED_TOGGLE (unsigned int num)
{
	  switch (num) 
	{
		case 0:
			GPIOToggle(0,0);
		break;
		case 1:
			GPIOToggle(0,2);
		break;
		case 2:
			GPIOToggle(0,22);
		break;
		case 3:
			GPIOToggle(2,6);
		break;
		case 4:
			GPIOToggle(2,7);
		break;
		case 5:
			GPIOToggle(2,8);
		break;
		case 6:
			GPIOToggle(2,12);
		break;
		case 7:
			GPIOToggle(2,13);
		break;
		default:
		break;
	}
}

void LED_Out(unsigned char value)																		
{
	
	if(value>=128)
			{
				LED_On(7);
				value=value-128;
			}	
	else
		LED_Off(7);
	if(value>=64)
			{
				LED_On(6);
				value=value-64;
			}	
			else
		LED_Off(6);
if(value>=32)
			{
				LED_On(5);
				value=value-32;
			}
else
		LED_Off(5);			
if(value>=16)
			{
				LED_On(4);
				value=value-16;
			}	
else
		LED_Off(4);			
if(value>=8)
			{
				LED_On(3);
				value=value-8;
			}		
			else
		LED_Off(3);
if(value>=4)
			{
				LED_On(2);
				value=value-4;
			}	
else
		LED_Off(2);			
if(value>=2)
			{
				LED_On(1);
				value=value-2;
			}	
else
		LED_Off(1);			
if(value>=1)
			{
				LED_On(0);
				value=value-1;
			}
else
		LED_Off(0);			
}



//1.4 RGB LED control

void RGB_Init(void)
{
	//change the Portpin PX.Y to an output
	GPIOSetDir(0,10,1); //Blue
	GPIOSetDir(0,11,1);	//Red
	GPIOSetDir(4,29,1);	//Green
	
	//set the Portpin PX.Y to „0“/ 0V
	GPIOSetValue(0,10,0); 
	GPIOSetValue(0,11,0);
	GPIOSetValue(4,29,0);
}

void RGB_On(unsigned int num)
{
	switch (num)
	{
		case 0:
			GPIOSetValue(0,10,1); //Blue
		break;
		case 1:
			GPIOSetValue(0,11,1); //Red
		break;
		case 2:
			GPIOSetValue(4,29,1); //Green
		break;
	}
}

void RGB_Off(unsigned int num)
{
	switch (num)
	{
		case 0:
			GPIOSetValue(0,10,0); //Blue
		break;
		case 1:
			GPIOSetValue(0,11,0); //Red
		break;
		case 2:
			GPIOSetValue(4,29,0); //Green
		break;
	}
}

void RGB_Out(unsigned char value)
{
		if(value>=4)
			{
				RGB_On(2);
				value=value-4;
			}	
	else
		RGB_Off(2);
	if(value>=2)
			{
				RGB_On(1);
				value=value-2;
			}	
			else
		RGB_Off(1);
if(value>=1)
			{
				RGB_On(0);
				value=value-1;
			}
else
		RGB_Off(0);		
}

void RGB_Toggle(unsigned int num)
{
	  switch (num) 
	{
		case 0:
			GPIOToggle(0,10); //Blue
		break;
		case 1:
			GPIOToggle(0,11);	//Red
		break;
		case 2:
			GPIOToggle(4,29); //Green
		break;
		default:
		break;
	}
}


unsigned int RGB_FlipFlop(unsigned int led,unsigned int button, unsigned int buttonBefore)
{
	if(button == 1 && buttonBefore == 0){
			RGB_Toggle(led);
			return 1;
		}
		else if(button != 1 && buttonBefore == 1){
			return 0;
		}
		else{
			return buttonBefore;
		}
}

unsigned int LED_FlipFlop(unsigned int led,unsigned int button, unsigned int buttonBefore){
	if(button && buttonBefore == 0){
			LED_TOGGLE(led);
			return 1;
		}
		else if(!button && buttonBefore == 1){
			return 0;
		}
		else{
			return buttonBefore;
		}
}




//uint8_t  rolchar2 (uint8_t value, uint8_t dir)
//{
//		if(dir == 0){
//		if(value & (1 << 7)){
//			value = ((value << 1)+1);
//		}
//		else{
//			value = (value << 1);
//		}
//	}
//	else if(dir == 1){
//		if(value & 1){
//			value = ((value >> 1)+128);
//		}
//		else{
//			value = (value >> 1);
//		}
//	}
//	
//	return value;
//}

void  rolchar (uint8_t* value, uint8_t dir)
{
		if(dir == 0){
		if(*value & (1 << 7)){
			*value = ((*value << 1)+1);
		}
		else{
			*value = (*value << 1);
		}
	}
	else if(dir == 1){
		if(*value & 1){
			*value = ((*value >> 1)+128);
		}
		else{
			*value = (*value >> 1);
		}
	}
}

