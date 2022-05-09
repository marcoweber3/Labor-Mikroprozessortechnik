#include <LPC17xx.h>
#include "dac.h" 
#include <stdio.h>
#include "gpio.h"
#include "prio.h"



void DAC_Init(void)
{
	//P0.26 as AOut
	LPC_PINCON->PINSEL1 &= ~(3<<20);
	LPC_PINCON->PINSEL1 |= (2<<20);
	
	//no pullup or pulldown resistor
	LPC_PINCON->PINMODE1 &= ~(3<<20);
	LPC_PINCON->PINMODE1 |= (2<<20);
}

void DAC_Out (unsigned int wert)
{
	LPC_DAC->DACR = ((wert & 0x3FF) << 6); //12bit auf 10bit reduzieren und ausgeben 
}

