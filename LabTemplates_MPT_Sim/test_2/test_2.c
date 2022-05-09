/******************************************************************************
test_2.c
*******************************************************************************
	Autor: 
	Datum: 

********************************************************************************/

//================================================================================
//include Header Files:
//================================================================================
#include <LPC17xx.h>
#include "tests.h"
#include "GLCD.h"
#include "keys.h"
#include "lcd.h"


//================================================================================
//Definitions and constants:
//================================================================================

#define FONT_6x8   0     //Font-Index für ASCII Font 6x8
#define FONT_16x24 1     //Font-Index für ASCII Font 16x24


//================================================================================
//  Test T2_1
//================================================================================
#if (T2_1 == 1)

#include "GLCD.h"
#include "gpio.h"


#define OUT_PORT PORT2
#define PORT_PIN 2


int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Red); // Background color
	GLCD_SetTextColor(White); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"Microproc tech lab   "); // Output text in line 0, from column 0 with font size 16x24
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"PORT_PIN="); // Output text in line 5, from column 0 with font size 16x24

	
	GPIOSetDir(OUT_PORT, PORT_PIN, GPIO_OUTPUT);
	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
	GLCD_Simulation();


	while(1)
	{	GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_HIGH);
		GLCD_Simulation();
		GLCD_DisplayString(5,9,FONT_16x24,(unsigned char*)"1");
		GPIOSetValue(OUT_PORT,PORT_PIN,PORT_PIN_LOW);
		GLCD_Simulation();		
		GLCD_DisplayString(5,9,FONT_16x24,(unsigned char*)"0");
	}
	
}	// end main()

#endif


//
//================================================================================
//  Test T2_2
//================================================================================
#if (T2_2 == 1)


int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Blue); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"   Lab Microproc.     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test2.1: switchpos  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"bin: "); 
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"hex:"); 
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"dez:"); 
	
	Switch_Init();
	GLCD_Simulation();
	
	
	
	while(1)
	{
		GLCD_Simulation();
		GLCD_DisplayString(5,5,FONT_16x24,(unsigned char*)lcd_bin(Get_SwitchPos())); 
	  GLCD_DisplayString(6,5,FONT_16x24,(unsigned char*)lcd_hex(Get_SwitchPos())); 
	  GLCD_DisplayString(7,5,FONT_16x24,(unsigned char*)lcd_dez(Get_SwitchPos()));
		
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T2_3
//================================================================================
#if (T2_3 == 1)

int main(void)
{	
	GLCD_Init();  //Initialize graphical LCD
	GLCD_Clear(White); // Clear graphical LCD display
	GLCD_SetBackColor(Blue); // Background color
	GLCD_SetTextColor(Yellow); // Text color
	GLCD_DisplayString(0,0,FONT_16x24,(unsigned char*)"   Lab Microproc.     ");
	GLCD_DisplayString(1,0,FONT_16x24,(unsigned char*)" test2.2: switches  ");
	GLCD_DisplayString(2,0,FONT_16x24,(unsigned char*)"      Group A8        ");
	
	GLCD_SetBackColor(White); // Background color
	GLCD_SetTextColor(Black); // Text color
	GLCD_DisplayString(5,0,FONT_16x24,(unsigned char*)"bin: "); 
	GLCD_DisplayString(6,0,FONT_16x24,(unsigned char*)"hex:"); 
	GLCD_DisplayString(7,0,FONT_16x24,(unsigned char*)"dez:"); 
	
	Switch_Init();
	GLCD_Simulation();
	
	
	while(1)
	{
		GLCD_Simulation();
		GLCD_DisplayString(5,5,FONT_16x24,(unsigned char*)lcd_bin(Get_SwitchPos())); 
	  GLCD_DisplayString(6,5,FONT_16x24,(unsigned char*)lcd_hex(Get_SwitchPos())); 
	  GLCD_DisplayString(7,5,FONT_16x24,(unsigned char*)lcd_dez(Get_SwitchPos()));
		GLCD_Bargraph(8, 215, 192, 20, (int)4 * Get_SwitchPos());	
	} // end while(1)
}	// end main()

#endif



//
//================================================================================
//  Test T2_4
//================================================================================
#if (T2_4 == 1)
#include <LPC17xx.h>
#include "GLCD.h"
#include "gpio.h"
#include "keys.h"
#include "lcd.h"

int main(void){	
	
	int value = 0;
	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,1,FONT_16x24,(unsigned char*)"Lab microprocessor");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"Test2.3: volt/temp");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A8");
	
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"Value");
	GLCD_DisplayString(5, 1, FONT_16x24, (unsigned char*)"Temp.");
	
	Switch_Init();
	GLCD_Simulation();

	
	while(1){	
		GLCD_Simulation();
		value = (Get_SwitchPos() << 4)|0xF;

		GLCD_DisplayString(4, 7, FONT_16x24, (unsigned char*)lcd_dez(value));
		GLCD_DisplayString(4, 14, FONT_16x24, (unsigned char*)AD_volt(value));

		GLCD_DisplayString(5, 13, FONT_16x24, (unsigned char*)TempConv(value));
	} // end while(1)
}	// end main()

#endif


//
//================================================================================
//  Test T2_5
//================================================================================
#if (T2_5 == 1)
#include <LPC17xx.h>
#include "GLCD.h"
#include "gpio.h"
#include "keys.h"
#include "lcd.h"

char var = 0x20;
char stat = 0x20;
char statBefore = 0x20;

int main(void)
{	
	GLCD_Init();
	GLCD_Clear(White);
	GLCD_SetBackColor(Yellow);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(0,1,FONT_16x24,(unsigned char*)"Lab microprocessor");
	GLCD_DisplayString(1,1,FONT_16x24,(unsigned char*)"Test2.3: volt/temp");
	GLCD_DisplayString(2,5,FONT_16x24,(unsigned char*)"Group A8");
	
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 1, FONT_16x24, (unsigned char*)"Taste:");

	Matrix_Init();
	GLCD_Simulation();

	
	while(1)
	{	
		GLCD_Simulation();
		
		stat = Get_Mkey();

		if(stat == 0x20 && statBefore != 0x20)
		{
			var = statBefore;
		}
		
		GLCD_DisplayChar(4, 8, FONT_16x24, (unsigned char)var);
		
		statBefore = stat;
	}

	// end while(1)
}	// end main()

#endif

//
//================================================================================
//  Test T2_6
//================================================================================
#if (T2_6 == 1)

int main(void)
{	

	while(1)
	{
		
	} // end while(1)
}	// end main()

#endif



