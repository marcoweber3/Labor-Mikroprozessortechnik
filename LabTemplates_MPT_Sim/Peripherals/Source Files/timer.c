#include <LPC17xx.h>
#include "timer.h" 
#include <stdio.h>
#include "gpio.h"
#include "prio.h"


void counter_Init (uint8_t TimerNum, uint8_t CapIn, uint8_t edge)
{
	switch(TimerNum){
		case 0:		
				LPC_SC->PCONP |=(1UL<<1);
			
				if(CapIn == 0) //Capture Interrupt 0
				{
					LPC_PINCON->PINSEL3 |= (3UL<<20); //activate counter pin
					LPC_PINCON->PINMODE3 |= (2UL<<20); //neither pull-up nor pull-down
				}
				else //Capture Interrupt 1
				{
					LPC_PINCON->PINSEL3 |= (3UL<<22); //activate counter pin
					LPC_PINCON->PINMODE3 |= (2UL<<22); //neither pull-up nor pull-down
				}
				LPC_TIM0->CTCR &= ~(3UL<<0); //Timermode ???
				
				switch (edge) // Gewählte Flanke setzen
				{
						case 1: // steigende Flanke
							LPC_TIM0->CTCR |= (1UL<<0); /* Capture if rising edge at CAP1.0 */
						break;
						
						case 2: // fallende Flanke 
							LPC_TIM0->CTCR |= (2UL<<0); /* Capture if falling edge at CAP1.0 */
						break;
						
						case 3: // beide Flanken
							LPC_TIM0->CTCR |= (3UL<<0); /* Capture if both edges at CAP1.0 */
						break; 
				}
				
				LPC_TIM0->TCR = (1UL<<1); //Timer reset
				LPC_TIM0->TCR = (1UL<<0); //Timer start
		break;
		
		case 1:
				LPC_SC->PCONP |=(1UL<<2);
			
				if(CapIn == 0)
				{
					LPC_PINCON->PINSEL3 |= (3UL<<4);
					
					LPC_PINCON->PINMODE3 |= (2UL<<4);
				}
				else
				{
					LPC_PINCON->PINSEL3 |= (3UL<<6);
					
					LPC_PINCON->PINMODE3 |= (2UL<<6);
				}
				LPC_TIM1->CTCR &= ~(3UL<<0); //Timermode ???
				
				switch (edge) // Gewählte Flanke setzen
				{
						case 1: // steigende Flanke
							LPC_TIM1->CTCR |= (1UL<<0); /* Capture if rising edge at CAP1.0 */
						break;
						
						case 2: // fallende Flanke 
							LPC_TIM1->CTCR |= (2UL<<0); /* Capture if falling edge at CAP1.0 */
						break;
						
						case 3: // beide Flanken
							LPC_TIM1->CTCR |= (3UL<<0); /* Capture if both edges at CAP1.0 */
						break;			
				}
				LPC_TIM1->TCR = (1UL<<1); //Timer reset
				LPC_TIM1->TCR = (1UL<<0); //Timer start
		break;
		
		case 2:
				LPC_SC->PCONP |=(1UL<<22);
			
				if(CapIn == 0)
				{
					LPC_PINCON->PINSEL3 |= (3UL<<8);
					
					LPC_PINCON->PINMODE0 |= (2UL<<8);
				}
				else
				{
					LPC_PINCON->PINSEL3 |= (3UL<<10);
					
					LPC_PINCON->PINMODE0 |= (2UL<<10);
				}
				LPC_TIM2->CTCR &= ~(3UL<<0); //Timermode ???
				
				switch (edge) // Gewählte Flanke setzen
				{
						case 1: // steigende Flanke
							LPC_TIM2->CTCR |= (1UL<<0); /* Capture if rising edge at CAP1.0 */
						break;
						
						case 2: // fallende Flanke 
							LPC_TIM2->CTCR |= (2UL<<0); /* Capture if falling edge at CAP1.0 */
						break;
						
						case 3: // beide Flanken
							LPC_TIM2->CTCR |= (3UL<<0); /* Capture if both edges at CAP1.0 */
						break; 
				}			
				LPC_TIM2->TCR = (1UL<<1); //Timer reset
				LPC_TIM2->TCR = (1UL<<0); //Timer start
		break;
		
		case 3:
				LPC_SC->PCONP |=(1UL<<23);
			
				if(CapIn == 0)
				{
					LPC_PINCON->PINSEL3 |= (3UL<<14);
					
					LPC_PINCON->PINMODE1 |= (2UL<<14);
				}
				else
				{
					LPC_PINCON->PINSEL3 |= (3UL<<16);
					
					LPC_PINCON->PINMODE1 |= (2UL<<16);
				}
				LPC_TIM3->CTCR &= ~(3UL<<0); //Timermode ???
				
				switch (edge) // Gewählte Flanke setzen
				{
						case 1: // steigende Flanke
							LPC_TIM3->CTCR |= (1UL<<0); /* Capture if rising edge at CAP1.0 */
						break;
						
						case 2: // fallende Flanke 
							LPC_TIM3->CTCR |= (2UL<<0); /* Capture if falling edge at CAP1.0 */
						break;
						
						case 3: // beide Flanken
							LPC_TIM3->CTCR |= (3UL<<0); /* Capture if both edges at CAP1.0 */
						break; 
				}
				
				LPC_TIM3->TCR = (1UL<<1); //Timer reset
				LPC_TIM3->TCR = (1UL<<0); //Timer start
			break;
		}
}



void Timer_Init (uint8_t TimerNum, uint32_t cycle, uint32_t TimerDivid, uint8_t pclk , uint8_t ResetMR)
{
		SystemCoreClockUpdate();
		switch(TimerNum){ //Timer Number
			case 0:
						LPC_SC->PCONP |= (1UL<<1); //TIM0
			
//						switch (pclk){ //Peripherial Clock
//								case 0:
//									LPC_SC->PCLKSEL0 &= ~(3UL<<2); 
//								break;
//								case 1:
//									LPC_SC->PCLKSEL0 |= (1UL<<2); //0100
//								break;
//								case 2:
//									LPC_SC->PCLKSEL0 |= (2UL<<2); //1000
//								break;
//								case 3:
//									LPC_SC->PCLKSEL0 |= (3UL<<2); //1100
//								break;
//						}
			
						LPC_SC->PCLKSEL0 |= (pclk<<2);//Peripherial Clock (0000, 0100, 1000, 1100)
						
						LPC_TIM0->PR = SystemCoreClock/TimerDivid-1; //Prescale Register (TimerDivid)
						LPC_TIM0->TCR = (1<<0);
						
						switch(ResetMR){
								case 0: //Matchregister 0
									LPC_TIM0->MR0 = cycle -1; //Timer cycles MR0
									LPC_TIM0->MCR |= (3 <<0); //Interupt on MR0 match
									LPC_TIM0->EMR = (3UL<<4); //Toggle Matchregister
									LPC_TIM0->IR |= (1<<0); //Acivate Interrupt
								break;
								case 1: //Matchregister 1
									LPC_TIM0->MR1 = cycle -1;
									LPC_TIM0->MCR |= (3 <<3);
									LPC_TIM0->EMR = (3UL<<6);
									LPC_TIM0->IR |= (1<<1);
								break;
								case 2: //Matchregister 2
									LPC_TIM0->MR2 = cycle -1;
									LPC_TIM0->MCR |= (3 <<6); 
									LPC_TIM0->EMR = (3UL<<8);
									LPC_TIM0->IR |= (1<<2);
								break;
								case 3: //Matchregister 3
									LPC_TIM0->MR3 = cycle -1;
									LPC_TIM0->MCR |= (3 <<9);
									LPC_TIM0->EMR = (3UL<<10);
									LPC_TIM0->IR |= (1<<3);
								break;
						}
						
						NVIC_SetPriority(TIMER0_IRQn, PRIO_TIMER0); //set priority
						NVIC_ClearPendingIRQ(TIMER0_IRQn); //reset pending bit
						NVIC_EnableIRQ(TIMER0_IRQn);	//activate interrupt
			break;
			
				
			case 1:
						LPC_SC->PCONP |= (1UL<<2); //TIM1
						
						LPC_SC->PCLKSEL0 |= (pclk<<4); //Peripherial Clock
						
						LPC_TIM1->PR = SystemCoreClock/(TimerDivid)-1; //Prescale Register (TimerDivid)
						
						switch(ResetMR){
								case 0: //Matchregister 0
									LPC_TIM1->MR0 = cycle -1; //Timer cycles MR0
									LPC_TIM1->MCR |= (1UL<<1); //Reset on MR0
									LPC_TIM1->EMR = (3UL<<4); //Toggle Matchregister
									LPC_TIM1->IR |= (1<<0); //Acivate Interrupt
								break;
								case 1: //Matchregister 1
									LPC_TIM1->MR1 = cycle -1;
									LPC_TIM1->MCR |= (3 <<3);
									LPC_TIM1->EMR = (3UL<<6);
									LPC_TIM1->IR |= (1<<1);
								break;
								case 2: //Matchregister 2
									LPC_TIM1->MR2 = cycle -1;
									LPC_TIM1->MCR |= (3 <<6);
									LPC_TIM1->EMR = (3UL<<8);
									LPC_TIM1->IR |= (1<<2);
								break;
								case 3: //Matchregister 3
									LPC_TIM1->MR3 = cycle -1;
									LPC_TIM1->MCR |= (3 <<9);
									LPC_TIM1->EMR = (3UL<<10);
									LPC_TIM1->IR |= (1<<3);
								break;
								default:
									break;
						}
						
						NVIC_SetPriority(TIMER1_IRQn, PRIO_TIMER1); //set priority
						NVIC_ClearPendingIRQ(TIMER1_IRQn); //reset pending bit
						NVIC_EnableIRQ(TIMER1_IRQn);	//activate interrupt
			break;	
			
			case 2:
						LPC_SC->PCONP |= (1UL<<22); //TIM2
					
						LPC_SC->PCLKSEL1 |= (pclk<<12); //Peripherial Clock
						
						LPC_TIM2->PR = SystemCoreClock/(TimerDivid)-1; //Prescale Register (TimerDivid)
						
						switch(ResetMR){
								case 0: //Matchregister 0
									LPC_TIM2->MR0 = cycle -1; //Timer cycles MR0
									LPC_TIM2->MCR |= (1UL<<1); //Reset on MR0
									LPC_TIM2->EMR = (3UL<<4); //Toggle Matchregister
									LPC_TIM2->IR |= (1<<0); //Acivate Interrupt
								break;
								case 1: //Matchregister 1
									LPC_TIM2->MR1 = cycle -1;
									LPC_TIM2->MCR |= (3 <<3);
									LPC_TIM2->EMR = (3UL<<6);
									LPC_TIM2->IR |= (1<<1);
								break;
								case 2: //Matchregister 2
									LPC_TIM2->MR2 = cycle -1;
									LPC_TIM2->MCR |= (3 <<6);
									LPC_TIM2->EMR = (3UL<<8);
									LPC_TIM2->IR |= (1<<2);
								break;
								case 3: //Matchregister 3
									LPC_TIM2->MR3 = cycle -1;
									LPC_TIM2->MCR |= (3 <<9);
									LPC_TIM2->EMR = (3UL<<10);
									LPC_TIM2->IR |= (1<<3);
								break;
								default:
									break;
						}
						
						NVIC_SetPriority(TIMER2_IRQn, PRIO_TIMER2); //set priority
						NVIC_ClearPendingIRQ(TIMER2_IRQn); //reset pending bit
						NVIC_EnableIRQ(TIMER2_IRQn);	//activate interrupt
			break;
			
			case 3:
						LPC_SC->PCONP |= (1UL<<23); //TIM3
					
						LPC_SC->PCLKSEL1 |= (pclk<<14); //Peripherial Clock
						
						LPC_TIM3->PR = SystemCoreClock/(TimerDivid)-1; //Prescale Register (TimerDivid)
				
									switch(ResetMR){
								case 0: //Matchregister 0
									LPC_TIM3->MR0 = cycle -1; //Timer cycles MR0
									LPC_TIM3->MCR |= (1UL<<1); //Reset on MR0
									LPC_TIM3->EMR = (3UL<<4); //Toggle Matchregister
									LPC_TIM3->IR |= (1<<0); //Acivate Interrupt
								break;
								case 1: //Matchregister 1
									LPC_TIM3->MR1 = cycle -1;
									LPC_TIM3->MCR |= (3 <<3);
									LPC_TIM3->EMR = (3UL<<6);
									LPC_TIM3->IR |= (1<<1);
								break;
								case 2: //Matchregister 2
									LPC_TIM3->MR2 = cycle -1;
									LPC_TIM3->MCR |= (3 <<6);
									LPC_TIM3->EMR = (3UL<<8);
									LPC_TIM3->IR |= (1<<2);
								break;
								case 3: //Matchregister 3
									LPC_TIM3->MR3 = cycle -1;
									LPC_TIM3->MCR |= (3 <<9);
									LPC_TIM3->EMR = (3UL<<10);
									LPC_TIM3->IR |= (1<<3);
								break;
								default:
									break;
						}
									
						NVIC_SetPriority(TIMER3_IRQn, PRIO_TIMER3); //set priority
						NVIC_ClearPendingIRQ(TIMER3_IRQn); //reset pending bit
						NVIC_EnableIRQ(TIMER3_IRQn);	//activate interrupt
			break;		
		}
		
}
