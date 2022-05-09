#include <LPC17xx.h>
#include "adc.h" 
#include <stdio.h>
#include "gpio.h"
#include "prio.h"



void ADC_Init (uint8_t chsel, uint8_t intEn)
{
	//power on
	LPC_SC->PCONP |= (1 << 12);
	LPC_SC->PCONP |= (1 << 15);
	
	//peripheral clock
	LPC_SC->PCLKSEL0 &=~ (3 << 24); // PCLK = CCLK/4 = 25MHz, default
	//LPC_SC->PCLKSEL0 |=  (1 << 24); // PCLK = CCLK = 100MHz
	

	LPC_ADC->ADCR &=~ (0xFF << 8); //Bit = 0 for Burstmode
	
	LPC_ADC->ADCR |= (7 << 8); //CLKDIV (24, 9, 4, 3, 2, 1, 7)
	       
	LPC_ADC->ADCR |= (1<<21); //power-down-mode off
	LPC_ADC->ADCR &=~(1 << 24); //single aktivaton (111 ~ 000 -> Bit 24-26=0)
	
	if ((chsel>>3)&1) //1000 -> 0001 =? 1
		{
			/*initialize channel 3*/
			LPC_PINCON->PINSEL1  &=~(3 << 20); //0.26 -> 1.20
			LPC_PINCON->PINSEL1  |= (1 << 20);
			LPC_PINCON->PINMODE1 &=~(3 << 20);
			LPC_PINCON->PINMODE1 |= (2 << 20);
		}
	if ((chsel>>4)&1) 
		{
			/*initialize channel 4*/
			LPC_PINCON->PINSEL3  |= (3 << 28); //1.30 -> 3.28
			LPC_PINCON->PINMODE3 &=~(3 << 28);
			LPC_PINCON->PINMODE3 |= (2 << 28);
		}
	if ((chsel>>5)&1) 
		{
      LPC_PINCON->PINSEL3|=(3UL<<30);   
      LPC_PINCON->PINMODE3 &= ~(3UL<<30);
      LPC_PINCON->PINMODE3 |= (2UL<<30);
		}
		

		if (intEn)
		{
				
				LPC_ADC-> ADINTEN &=~ (1<<8); //Enablen, dass Interrupt möglich ist
				
				LPC_ADC-> ADINTEN |= (1<<3); //enable interrupt für Kanal 3...5
				LPC_ADC-> ADINTEN |= (1<<4); 
				LPC_ADC-> ADINTEN |= (1<<5); 
				
				NVIC_SetPriority(ADC_IRQn, PRIO_ADC_IRQN);            
				NVIC_EnableIRQ(ADC_IRQn);
				NVIC_ClearPendingIRQ(ADC_IRQn);        
				
		}
}

void ADC_StartCnv (uint8_t chsel, uint8_t burst)
{
		LPC_ADC->ADCR &=~ (0xFF); //Auswahl für den Channel rücksetzen
		LPC_ADC->ADCR |= chsel;
	
	if ((chsel>>3)&1)
	{
		LPC_ADC->ADCR |= (1UL << 3);
	}
	if ((chsel>>4)&1)
	{
		LPC_ADC->ADCR |= (1UL << 4);
	}
	if ((chsel>>5)&1)
	{
		LPC_ADC->ADCR |= (1UL << 5);
	}
	
	if(!burst)
	{
		LPC_ADC->ADCR &=~ (7<<24);
		LPC_ADC->ADCR |= (1<<24);
	}
	else
	{
		LPC_ADC->ADCR |= (1 << 16);
	}
}

void ADC_StopCnv (void) 
{
	LPC_ADC->ADCR &= ~(1<<16);
}

uint32_t ADC_Stat (void) 
{
	return LPC_ADC->ADSTAT;
}

uint32_t ADC_GetValue(unsigned int channel)
{
	
	uint32_t Value = 0;
	switch(channel){
		case 3:
			Value = (LPC_ADC->ADDR3 >> 4) & 0xFFF;
		break;
		case 4:
			Value =(LPC_ADC->ADDR4 >> 4) & 0xFFF;
		break;
		case 5:
			Value = (LPC_ADC->ADDR5 >> 4) & 0xFFF;
		break;
	}
	
	return Value;
}
