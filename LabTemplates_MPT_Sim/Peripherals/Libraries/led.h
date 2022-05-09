//#include <LPC17xx.h>
//#include "gpio.h"

#ifndef led
#define led

void LED_Init(void);
void LED_On(unsigned int num);
void LED_Off(unsigned int num);
void LED_TOGGLE (unsigned int num);
void LED_Out(unsigned char value)	;


void RGB_Init(void);
void RGB_On(unsigned int num);
void RGB_Off(unsigned int num);
void RGB_Out(unsigned char value);
void RGB_Toggle(unsigned int num);

unsigned int RGB_FlipFlop(unsigned int led,unsigned int button, unsigned int buttonBefore);
unsigned int LED_FlipFlop(unsigned int led,unsigned int button, unsigned int buttonBefore);
void  rolchar (uint8_t* value, uint8_t dir);



#endif


