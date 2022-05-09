/*================================================================================
HEADER FILE gpio.h:
--------------------------------------------------------------------------------
Datum: 
--------------------------------------------------------------------------------
Autor: 
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
Beschreibung: protoytypes/ deklarations 
           -> GPIOSetDir()
           -> GPIOSetValue()
	   -> GPIOGetValue()

--------------------------------------------------------------------------------
Hinweise:     definitiones/ implementations v. libraryfunctions
           -> s. Source File gpio.c
================================================================================
*/

#ifndef __GPIO_H //start conditional compilation
#define __GPIO_H
//#include <LPC17xx.h>

//================================================================================
//definition of contants:
//================================================================================
#define PORT0 0
#define PORT1 1
#define PORT2 2
#define PORT3 3
#define PORT4 4

#define PORT_PIN2 2

#define PORT_PIN_HIGH 1
#define PORT_PIN_LOW 0
#define GPIO_OUTPUT 1
#define GPIO_INPUT 0


//================================================================================
//Funktionsprototypen/ Deklarationen v. Bibliotheksfunktionen:
//================================================================================

//--------------------------------------------------------------------------------
//function for setting  the portdirection (dir=1: Output) of a  port-pin:
//--------------------------------------------------------------------------------
extern void GPIOSetDir(uint8_t portNum, uint8_t bitPosi, uint8_t dir);

//--------------------------------------------------------------------------------
//function for setting  the port-pin (bitval=1: 3,3V)
//--------------------------------------------------------------------------------
extern void GPIOSetValue (uint8_t portNum, uint8_t bitPosi, uint8_t bitVal);

//--------------------------------------------------------------------------------
//function to read a port-pin (returnvalue: "0":0V, "1":3,3V)
//--------------------------------------------------------------------------------
uint8_t GPIOGetValue(uint8_t portNum, uint8_t bitPosi) ;


extern void GPIOToggle (uint8_t portNum, uint8_t bitPosi);
	
extern void Init_Input(void);

#endif //end conditional compilation



