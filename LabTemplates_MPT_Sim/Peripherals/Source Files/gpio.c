/*==============================================================================
SOURCE FILE gpio.c:
--------------------------------------------------------------------------------
Datum: 
--------------------------------------------------------------------------------
Autor: 
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
definitions/functions/purpose
           -> GPIOSetDir()
           -> GPIOSetValue()
					 -> GPIOGetValue()

--------------------------------------------------------------------------------
notes:     functionprototype/ deklaration
           -> header File gpio.h
================================================================================
*/

//==============================================================================
//#includes
//==============================================================================
#include <LPC17xx.h>
#include "gpio.h"


//==============================================================================
//definitions of global variables:
//==============================================================================


//==============================================================================
//definitions
//==============================================================================

//
/*****************************************************************************
 ** Function name:               GPIOSetDir()
 **
 ** description:                function to set port direction  
 **															
 ** parameters:                 port num: number of port, 
 **										 					bit position: bit number of port 
 **															dir: direction (1 out, 0 input)
 ** return value:              None
 **
 *****************************************************************************/

void GPIOSetDir(uint8_t portNum, uint8_t bitPosi, uint8_t dir) 
{
  switch ( portNum )
  {
	case PORT0:
	  if ( !(LPC_GPIO0->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_OUTPUT) )
		LPC_GPIO0->FIODIR |= (0x1<<bitPosi);
	  else if ( (LPC_GPIO0->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_INPUT) )
		LPC_GPIO0->FIODIR &= ~(0x1<<bitPosi);
	break;
 	case PORT1:
		if ( !(LPC_GPIO1->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_OUTPUT) )
		LPC_GPIO1->FIODIR |= (0x1<<bitPosi);
	  else if ( (LPC_GPIO1->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_INPUT) )
		LPC_GPIO1->FIODIR &= ~(0x1<<bitPosi);
	break;
	case PORT2:
		if ( !(LPC_GPIO2->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_OUTPUT) )
		LPC_GPIO2->FIODIR |= (0x1<<bitPosi);
	  else if ( (LPC_GPIO2->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_INPUT) )
		LPC_GPIO2->FIODIR &= ~(0x1<<bitPosi);
	break;
	case PORT3:
		if ( !(LPC_GPIO3->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_OUTPUT) )
		LPC_GPIO3->FIODIR |= (0x1<<bitPosi);
	  else if ( (LPC_GPIO3->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_INPUT) )
		LPC_GPIO3->FIODIR &= ~(0x1<<bitPosi);
	break;
	case PORT4:
		if ( !(LPC_GPIO4->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_OUTPUT) )
		LPC_GPIO4->FIODIR |= (0x1<<bitPosi);
	  else if ( (LPC_GPIO4->FIODIR & (0x1<<bitPosi)) && (dir == GPIO_INPUT) )
		LPC_GPIO4->FIODIR &= ~(0x1<<bitPosi);
	break;
	
	default: break;
  }
  return;

}

//
/*****************************************************************************
 ** Function name:               GPIOSetValue()
 **
 ** Descriptions:                function to set port output
 ** Parameters:                  port num: number of port, 
 **										 					 bit position: bit number of port 
 **															 bitVal: value (1 , 0 )
 ** Returned value:              None
 **
 *****************************************************************************/

void GPIOSetValue(uint8_t portNum, uint8_t bitPosi, uint8_t bitVal) 
{
	if (bitVal == 1 ) 
		{ 
			/* Port-Pin auf 1 setzen  		*/
			switch ( portNum ) 
			{ case PORT0: 
				LPC_GPIO0->FIOSET = (1<<bitPosi); 
				break; 
				case PORT1: 
				LPC_GPIO1->FIOSET = (1<<bitPosi); 
				break; 

				case PORT2: 
				LPC_GPIO2->FIOSET = (1<<bitPosi); 
				break; 

				case PORT3: 
				LPC_GPIO3->FIOSET = (1<<bitPosi); 
				break; 

				case PORT4:
				LPC_GPIO4->FIOSET = (1<<bitPosi); 
				break;
				
				default: break; 
			}
		}
	else if (bitVal == 0 ) 
		{ 
			/* Port-Pin auf 0 setzen  		*/
			switch ( portNum ) 
			{ case PORT0: 
				LPC_GPIO0->FIOCLR = (1<<bitPosi); 
				break; 
				case PORT1: 
				LPC_GPIO1->FIOCLR = (1<<bitPosi); 
				break; 

				case PORT2: 
				LPC_GPIO2->FIOCLR = (1<<bitPosi); 
				break; 
 
				case PORT3: 
				LPC_GPIO3->FIOCLR = (1<<bitPosi); 
				break; 

				case PORT4: 
				LPC_GPIO4->FIOCLR = (1<<bitPosi); 
				break; 

				default: break; 
			}
		}
		
  return;
}


//
/*****************************************************************************
 ** Function name:               GPIOGetValue()
 **
 ** Descriptions:                function to get port input 
 **															 
 ** Parameters:                  port num: number of port, 
 **										 					 bit position: bit number of port, 
 **															 
 ** Returned value:              
 **
 *****************************************************************************/

uint8_t GPIOGetValue(uint8_t portNum, uint8_t bitPosi) 
{			
	uint32_t value=0;
	switch ( portNum ) 
	{ case PORT0: 
			value = ((LPC_GPIO0->FIOPIN) & (1<<bitPosi)); //
		break; 
		case PORT1: 
				value = ((LPC_GPIO1->FIOPIN) & (1<<bitPosi)); 
		break; 			 
		case PORT2: 
			value = ((LPC_GPIO2->FIOPIN) & (1<<bitPosi)); 
		break; 				 
		case PORT3: 
			value = ((LPC_GPIO3->FIOPIN) & (1<<bitPosi)); 
		break; 				 
		case PORT4: 
			value = ((LPC_GPIO4->FIOPIN) & (1<<bitPosi)); 
		break; 				 
		default: break; 
	}
		if(value)
		{
			value = 1;	
		}
  return value;	

		
}
//
/*****************************************************************************
 ** Function name:               GPIOToggle()
 **
 ** Descriptions:                function to toggel port pin
 **															 
 ** Parameters:                  port num: number of port, 
 **										 					 bit position: bit number of port, 
 **															 
 ** Returned value:              None
 **
 *****************************************************************************/

void GPIOToggle (uint8_t portNum, uint8_t bitPosi)
	{
		
  switch ( portNum ) 
	{ case PORT0: 
		     LPC_GPIO0->FIOPIN ^= (1<<bitPosi); //toggle the Portpin PX.Y „1“?“0“/“0“?“1
		break; 
		case PORT1: 
				 LPC_GPIO1->FIOPIN ^= (1<<bitPosi); //toggle the Portpin PX.Y „1“?“0“/“0“?“1
		break;
		case PORT2: 
				 LPC_GPIO2->FIOPIN ^= (1<<bitPosi); //toggle the Portpin PX.Y „1“?“0“/“0“?“1
		break;
		case PORT3: 
				 LPC_GPIO3->FIOPIN ^= (1<<bitPosi); //toggle the Portpin PX.Y „1“?“0“/“0“?“1
		break;
		case PORT4: 
				 LPC_GPIO4->FIOPIN ^= (1<<bitPosi); //toggle the Portpin PX.Y „1“?“0“/“0“?“1
		break;
		default: break; 
	}
}
	//
	
	void Init_Input()
	{
		//switches S0..7:
		LPC_PINCON->PINMODE3&=~(0xFFFF<<4); LPC_PINCON->PINMODE3|=(0xAAAA<<4);//P1.18...25
		//Joystick:
		LPC_PINCON->PINMODE0 &= ~(3 << 6);LPC_PINCON->PINMODE0 |= (2 << 6); //P0.3
		LPC_PINCON->PINMODE1 &= ~(3 << 10);LPC_PINCON->PINMODE1 |= (2 << 10);//P0.21
		LPC_PINCON->PINMODE1 &= ~(3 << 18);LPC_PINCON->PINMODE1 |= (2 << 18);//P0.25
		LPC_PINCON->PINMODE1 &= ~(3 << 22);LPC_PINCON->PINMODE1 |= (2 << 22);//P0.27
		LPC_PINCON->PINMODE1 &= ~(3 << 24);LPC_PINCON->PINMODE1 |= (2 << 24);//P0.28
		//buttons TA10..12
		LPC_PINCON->PINMODE3 &= ~(3 << 20);LPC_PINCON->PINMODE3 |= (2 << 20);//P1.26
		LPC_PINCON->PINMODE3 &= ~(3 << 22);LPC_PINCON->PINMODE3 |= (2 << 22);//P1.27
		LPC_PINCON->PINMODE4 &= ~(3 << 22);LPC_PINCON->PINMODE4 |= (2 << 22);//P2.11
		
	}
