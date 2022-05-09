//==============================================================================
//Einbinden v. Header Files:
//==============================================================================
#include <LPC17xx.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "GLCD_S.h"
#include "gpio.h"

//==============================================================================
//Initierung des printf outputs
//==============================================================================

#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000
struct __FILE { int handle; /* Add whatever needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
} 

//==============================================================================
//Definition v. globalen Variablen:
//==============================================================================


//==============================================================================
//Definitionen/ Implementierungen v. Bibliotheksfunktionen:
//==============================================================================


//==============================================================================
//Definitionen/ Implementierungen v. Bibliotheksfunktionen:
//==============================================================================

//
/*****************************************************************************
 ** Function name:               ClearScreen(void)
 **
 ** Descriptions:                Funktion leeren des seriellen Fensters
 ** Parameters:                  None 
 ** Returned value:              None
 **
 *****************************************************************************/

// Clear screen and set cursor home
void ClearScreen(void)
{
        printf("%c[1;1f%c[J", 27, 27);

}

//
/*****************************************************************************
 ** Function name:               SetCursorPosition(x,y)
 **
** Descriptions:                Funktion Cursor an Position x,y setzen, x: Spalte, y: Zeile
 ** Parameters:                  x,y 
 ** Returned value:              Nonel
 **
 *****************************************************************************/

// set cursor to position (x, y)
void SetCursorPosition(int x, int y)
{
        printf("%c[%i;%if", 27, (signed int)y, (signed int)x);
}

//
/*****************************************************************************
 ** Function name:               DeleteLineRight(void)
 **
** Descriptions:                 Funktion alles rechts der Zeile löschen
 ** Parameters:                  x,y 
 ** Returned value:              Nonel
 **
 *****************************************************************************/

// delete character right from cursor
void DeleteLineRight(void)
{
        printf("%c[K", 27);
}

//
/*****************************************************************************
 ** Function name:               DeleteLineRight(void)
 **
** Descriptions:                 Funktion alles rechts der Zeile löschen
 ** Parameters:                  x,y 
 ** Returned value:              Nonel
 **
 *****************************************************************************/

// delete character right from cursor
void wait(unsigned int n)
{
	unsigned int iz1;
	for (iz1=1;iz1<n;iz1++) 
	{
 	;
  }
}

//
/*****************************************************************************
 ** Function name:               GLCD_S_Init(void)
 **
** Descriptions:                 Funktion zu Initialisierung des debug printf windows
 ** Parameters:                  None 
 ** Returned value:              None
 **
 *****************************************************************************/


void GLCD_S_Init(void)
{  
	unsigned int iz1,/*iz2,*/ixmax=20,iymax=10;
	unsigned int ix_LED_RGB=10,iy_LED_RGB=22,ix_Switch=25,iy_Switch=17,ix_JST=45,iy_JST=17;
		//,ix_7Seg=25,iy_7Seg=31;
	
	ClearScreen();
	ibgCol=15;
	itextCol=0;
	SetCursorPosition(ixmax/2+ix_offset-1,iy_offset-1);
	printf("LCD\n");
	SetCursorPosition(ixmax+ix_offset+3,iy_offset-1);
	printf("BackgroundColor\n");
	SetCursorPosition(ixmax+ix_offset+21,iy_offset-1);
	printf("TextColor\n");
	//wait(25000);
	SetCursorPosition(ix_offset,iy_offset);
	printf("|");
	for (iz1=1;iz1<=ixmax;iz1++)
	{
	       printf("=");
	}
	printf("|\n");
	//wait(25000);
	for (iz1=1;iz1<=iymax+1;iz1++)
	{
//	      SetCursorPosition(ix_offset,iz1+iy_offset+1);
        printf("|\n");
	}
	for (iz1=1;iz1<=iymax;iz1++)
	{
	      SetCursorPosition(ix_offset+ixmax+1,iz1+iy_offset);
        printf("|\n");
	}
	SetCursorPosition(ix_offset+1,iymax+iy_offset+1);
	for (iz1=1;iz1<=ixmax;iz1++)
	{
	       printf("=");
	}
	printf("|\n\n");
	
	SetCursorPosition(ix_LED_RGB,iy_LED_RGB-1);
	printf("\n"); 
	SetCursorPosition(ix_LED_RGB-5,iy_LED_RGB);
	printf(" \n"); 
	SetCursorPosition(ix_LED_RGB,iy_LED_RGB);
	printf("OOO\n");
	SetCursorPosition(ix_LED_RGB,iy_LED_RGB-4);
	printf("LED0\n");
	SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB-3);
	printf("O\n");
	SetCursorPosition(ix_LED_RGB,iy_LED_RGB+3);
	printf(" ");
	SetCursorPosition(ix_LED_RGB,iy_LED_RGB+3);
	printf("LED4\n");
	SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB+4);
	printf("O\n");
  SetCursorPosition(ix_LED_RGB+4,iy_LED_RGB-3);
  printf("LED1\n");
	SetCursorPosition(ix_LED_RGB+5,iy_LED_RGB-2);
	printf("O\n");
	SetCursorPosition(ix_LED_RGB+4,iy_LED_RGB+1);
	printf("LED3\n");
	SetCursorPosition(ix_LED_RGB+5,iy_LED_RGB+2);
	printf("O\n");
	SetCursorPosition(ix_LED_RGB+8,iy_LED_RGB-1);
	printf("LED2\n");
	SetCursorPosition(ix_LED_RGB+9,iy_LED_RGB);
	printf("O\n");
	SetCursorPosition(ix_LED_RGB-5,iy_LED_RGB-3);
	printf("LED7\n");
	SetCursorPosition(ix_LED_RGB-4,iy_LED_RGB-2);
	printf("O\n");
	SetCursorPosition(ix_LED_RGB-5,iy_LED_RGB+1);
	printf("LED5\n");
	SetCursorPosition(ix_LED_RGB-4,iy_LED_RGB+2);
	printf("O\n");
	SetCursorPosition(ix_LED_RGB-9,iy_LED_RGB-1);
	printf("LED6\n");
	SetCursorPosition(ix_LED_RGB-8,iy_LED_RGB);
	printf("O\n");
	SetCursorPosition(ix_LED_RGB,iy_LED_RGB-1);
	printf("RGB\n");
    SetCursorPosition(ix_LED_RGB-9,iy_LED_RGB-7);
   // printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("  O: Inactive   X: Active\n");
	//SetCursorPosition(ix_LED_RGB,iy_LED_RGB-1);
  //printf("\n");
	
	//Switch TA10,TA11,TA12
	SetCursorPosition(ix_Switch-2,iy_Switch);
	printf("TA12 TA11 TA10\n");										// Reihenfolge Geändert
	SetCursorPosition(ix_Switch-2,iy_Switch+1);
	printf(" O    O    O\n");
	SetCursorPosition(ix_Switch,iy_Switch+3);
	printf("   0 1\n");
	SetCursorPosition(ix_Switch,iy_Switch+4);
	printf("S7 <- \n");
	SetCursorPosition(ix_Switch,iy_Switch+5);
	printf("S6 <- \n");
	SetCursorPosition(ix_Switch,iy_Switch+6);
	printf("S5 <- \n");
	SetCursorPosition(ix_Switch,iy_Switch+7);
	printf("S4 <- \n");
	SetCursorPosition(ix_Switch,iy_Switch+8);
	printf("S3 <- \n");
	SetCursorPosition(ix_Switch,iy_Switch+9);
	printf("S2 <- \n");
	SetCursorPosition(ix_Switch,iy_Switch+10);
	printf("S1 <- \n");
	SetCursorPosition(ix_Switch,iy_Switch+11);
	printf("S0 <- \n");
	//Joystick
	SetCursorPosition(ix_JST-3,iy_JST);
	printf("JoyStick\n");
	SetCursorPosition(ix_JST,iy_JST+1);
	printf("UP\n");
	SetCursorPosition(ix_JST,iy_JST+2);
	printf("O\n");
	SetCursorPosition(ix_JST-7,iy_JST+3);
	printf("LEFT O O O RIGHT\n");
	SetCursorPosition(ix_JST,iy_JST+4);
	printf("O\n");
	SetCursorPosition(ix_JST-1,iy_JST+5);
	printf("DOWN\n");
	SetCursorPosition(ix_JST-4,iy_JST+7);
	//3 x 3 Matrix
	printf("3x3 Matrix\n");
	SetCursorPosition(ix_JST-2,iy_JST+8);
	printf("1 2 3\n");
	SetCursorPosition(ix_JST-2,iy_JST+9);
	printf("4 5 6\n");
	SetCursorPosition(ix_JST-2,iy_JST+10);
	printf("7 8 9\n");
	SetCursorPosition(ix_LED_RGB,iy_LED_RGB-1);
	printf("\n");
	// Encoder
	SetCursorPosition(ix_LED_RGB-2,iy_LED_RGB+8);
	printf("Encoder\n");
	SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB+9);
	printf("O\n");
  //7Segmentanzeige
#if 0
	SetCursorPosition(ix_7Seg,iy_7Seg-1);
 	printf("    7Seg_DSP\n");
	SetCursorPosition(ix_7Seg,iy_7Seg);
	printf("|======|======|\n");
	SetCursorPosition(ix_7Seg,iy_7Seg+1);
 	printf("|      |      |\n");
	SetCursorPosition(ix_7Seg,iy_7Seg+2);
 	printf("|      |      |\n");
	SetCursorPosition(ix_7Seg,iy_7Seg+3);
 	printf("|      |      |\n");
	SetCursorPosition(ix_7Seg,iy_7Seg+4);
 	printf("|      |      |\n");
	SetCursorPosition(ix_7Seg,iy_7Seg+5);
 	printf("|      |      |\n");
	SetCursorPosition(ix_7Seg,iy_7Seg+6);
 	printf("|      |      |\n");
	SetCursorPosition(ix_7Seg,iy_7Seg+7);
 	printf("|      |      |\n");
	SetCursorPosition(ix_7Seg,iy_7Seg+8);
	printf("|======|======|\n");
#endif
	
	
	
	//	char cCol[16][9]={"Black    ","Navy     ","DarkGreen","Maroon   ","Purple   ","Olive    ","LightGrey","DarkGrey ",
//		              "Blue     ","Green    ","Cyan     ","Red      ","Magenta  ","Yellow   ","White    "};
	strcpy(cCol[0],"Black    ");
	strcpy(cCol[1],"Navy     ");
	strcpy(cCol[2],"DarkGreen");
	strcpy(cCol[3],"DarkCyan ");
	strcpy(cCol[4],"Maroon   ");
	strcpy(cCol[5],"Purple   ");
	strcpy(cCol[6],"Olive    ");
	strcpy(cCol[7],"LightGrey");
	strcpy(cCol[8],"DarkGrey ");
	strcpy(cCol[9],"Blue     ");
	strcpy(cCol[10],"Green    ");
	strcpy(cCol[11],"Cyan     ");
	strcpy(cCol[12],"Red      ");
	strcpy(cCol[13],"Magenta  ");
	strcpy(cCol[14],"Yellow   ");
	strcpy(cCol[15],"White    ");
}

//
/*****************************************************************************
 ** Function name:               GLCD_S_DisplayString  (ln, col, fi, *s)
 **
 ** Descriptions:                Funktion zur Ausgabe eines Strings im debug printf window
 ** Parameters:                  ln, col, fi, *s 
 ** Returned value:              None
 **
 *****************************************************************************/
void GLCD_S_DisplayString  (unsigned int iln, unsigned int icol, unsigned char fi, unsigned char *s)
{
	unsigned int iz1=0,/*iz2,*/ixmax=20/*,iymax=10*/;
  char text[21];
	if (iln > 9) return;
	while (s[iz1]>0)
	{
		text[iz1]=s[iz1];
		iz1++;
	}
	if(iz1>20)iz1=20;
	text[iz1]=0;
	if ((iz1+icol)>ixmax)text[ixmax-icol]=0;
	SetCursorPosition(icol+ix_offset+1,iln+iy_offset+1);
	printf("%s\n",text);
	ibgCol;
	SetCursorPosition(ixmax+ix_offset+3,iln+iy_offset+1);
	strcpy(text,cCol[ibgCol]);
	printf("%s\n",text);
	strcpy(text,cCol[itextCol]);
	printf("\n");
	SetCursorPosition(ixmax+ix_offset+21,iln+iy_offset+1);
	printf("%s\n",text);
}

//
/*****************************************************************************
 ** Function name:               void GLCD_S_SetTextColor   (unsigned short color)
 **
 ** Descriptions:                Funktion zum Setzen der Textfarbe
 ** Parameters:                  color 
 ** Returned value:              None
 **
 *****************************************************************************/
void GLCD_S_SetTextColor   (unsigned short color)
{
	switch (color)
	{
		case	0x0000:
			itextCol=0;
		break;
		case	0x000F:
			itextCol=1;
		break;
		case	0x03E0:
			itextCol=2;
		break;
		case	0x03EF:
			itextCol=3;
		break;
		case	0x7800:
			itextCol=4;
		break;
		case	0x780F:
			itextCol=5;
		break;
		case	0x7BE0:
			itextCol=6;
		break;
		case	0xC618:
			itextCol=7;
		break;
		case	0x7BEF:
			itextCol=8;
		break;
		case	0x001F:
			itextCol=9;
		break;
		case	0x07E0:
			itextCol=10;
		break;
		case	0x07FF:
			itextCol=11;
		break;
		case	0xF800:
			itextCol=12;
		break;
		case	0xF81F:
			itextCol=13;
		break;
		case	0xFFE0:
			itextCol=14;
		break;
		case	0xFFFF:
			itextCol=15;
		break;
		default:
		  itextCol=0;
	}
}

//
/*****************************************************************************
 ** Function name:               void GLCD_S_SetBackColor   (unsigned short color)
 **
 ** Descriptions:                Funktion zum Setzen der Hintergrundfarbe
 ** Parameters:                  color 
 ** Returned value:              None
 **
 *****************************************************************************/
void GLCD_S_SetBackColor   (unsigned short color)
{
	switch (color)
	{
		case	0x0000:
			ibgCol=0;
		break;
		case	0x000F:
			ibgCol=1;
		break;
		case	0x03E0:
			ibgCol=2;
		break;
		case	0x03EF:
			ibgCol=3;
		break;
		case	0x7800:
			ibgCol=4;
		break;
		case	0x780F:
			ibgCol=5;
		break;
		case	0x7BE0:
			ibgCol=6;
		break;
		case	0xC618:
			ibgCol=7;
		break;
		case	0x7BEF:
			ibgCol=8;
		break;
		case	0x001F:
			ibgCol=9;
		break;
		case	0x07E0:
			ibgCol=10;
		break;
		case	0x07FF:
			ibgCol=11;
		break;
		case	0xF800:
			ibgCol=12;
		break;
		case	0xF81F:
			ibgCol=13;
		break;
		case	0xFFE0:
			ibgCol=14;
		break;
		case	0xFFFF:
			ibgCol=15;
		break;
		default:
		  ibgCol=15;
	}
}
//
/*****************************************************************************
 ** Function name:               voidGLCD_S_Simulation()
 **
 ** Descriptions:                Funktion zum Anzeigen verschiedener Aktionen
 ** Parameters:                  None 
 ** Returned value:              None
 **
 *****************************************************************************/
void GLCD_S_Simulation (void)
{
  unsigned int ix_LED_RGB=10,iy_LED_RGB=22,ix_Switch=25,iy_Switch=17,ix_JST=45,iy_JST=17,ix_7Seg=25,iy_7Seg=31;
	static short int iTA12_time=0,iTA12_iz1=0;
	//i7Seg=0x22;
	if (LPC_SC->PCONP & (1 << 15))  //nur wenn Power on
	{
	  //RGB-LED
	  if (!(LPC_PINCON->PINSEL0 & (3 << 20))&&(LPC_GPIO0->FIODIR &(1UL<< 10))) //Blaue LED
	  {
 	    if (LPC_GPIO0->FIOPIN &(1UL<< 10)) //Blaue LED
      {SetCursorPosition(ix_LED_RGB+2,iy_LED_RGB);printf("X\n");}  
	    else{SetCursorPosition(ix_LED_RGB+2,iy_LED_RGB);printf("O\n");} 
	  }
 	  if (!(LPC_PINCON->PINSEL0 & (3 << 22))&&(LPC_GPIO0->FIODIR &(1UL<< 11))) //Rote LED
    {
	    if (LPC_GPIO0->FIOPIN &(1UL<< 11)) //Rote LED
      {SetCursorPosition(ix_LED_RGB,iy_LED_RGB);printf("X\n");}  
	    else{SetCursorPosition(ix_LED_RGB,iy_LED_RGB);printf("O\n");} 
	  }
 	  if (!(LPC_PINCON->PINSEL9 & (3 << 26))&&(LPC_GPIO4->FIODIR &(1UL<< 29))) //Grüne LED
    {
	    if (LPC_GPIO4->FIOPIN &(1UL<< 29)) //Grüne LED
      {SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB);printf("X\n");}  
	    else{SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB);printf("O\n");} 
	  }
	  //7 LED
	  if (!(LPC_PINCON->PINSEL0 & (3 << 0))&&(LPC_GPIO0->FIODIR &(1UL<< 0))) //LED0
    {
      if (LPC_GPIO0->FIOPIN &(1UL<< 0)) //LED 0
      {SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB-3);printf("X\n");}  
	    else{SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB-3);printf("O\n");} 
	  }
	  if (!(LPC_PINCON->PINSEL0 & (3 << 4))&&(LPC_GPIO0->FIODIR &(1UL<< 2))) //LED1
    {
      if (LPC_GPIO0->FIOPIN &(1UL<< 2)) //LED 1
      {SetCursorPosition(ix_LED_RGB+5,iy_LED_RGB-2);printf("X\n");}  
	    else{SetCursorPosition(ix_LED_RGB+5,iy_LED_RGB-2);printf("O\n");} 
	  }
	  if (!(LPC_PINCON->PINSEL0 & (3 << 12))&&(LPC_GPIO0->FIODIR &(1UL<< 22))) //LED2
    {
	    if (LPC_GPIO0->FIOPIN &(1UL<< 22)) //LED 2
      {SetCursorPosition(ix_LED_RGB+9,iy_LED_RGB);printf("X\n");}  
	    else{SetCursorPosition(ix_LED_RGB+9,iy_LED_RGB);printf("O\n");} 
	  }
	  if (!(LPC_PINCON->PINSEL4 & (3 << 12))&&(LPC_GPIO2->FIODIR &(1UL<< 6))) //LED3
    {
      if (LPC_GPIO2->FIOPIN &(1UL<< 6)) //LED 3
      {SetCursorPosition(ix_LED_RGB+5,iy_LED_RGB+2);printf("X\n");}  
	    else{SetCursorPosition(ix_LED_RGB+5,iy_LED_RGB+2);printf("O\n");} 
	  }
	  if (!(LPC_PINCON->PINSEL4 & (3 << 14))&&(LPC_GPIO2->FIODIR &(1UL<< 7))) //LED4
    {
	    if (LPC_GPIO2->FIOPIN &(1UL<< 7)) //LED 4
      {SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB+4);printf("X\n");}  
      else{SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB+4);printf("O\n");} 
	  }
	  if (!(LPC_PINCON->PINSEL4 & (3 << 16))&&(LPC_GPIO2->FIODIR &(1UL<< 8))) //LED5
    {
      if (LPC_GPIO2->FIOPIN &(1UL<< 8)) //LED 5
      {SetCursorPosition(ix_LED_RGB-4,iy_LED_RGB+2);printf("X\n");}  
      else{SetCursorPosition(ix_LED_RGB-4,iy_LED_RGB+2);printf("O\n");} 
	  }
	  if (!(LPC_PINCON->PINSEL4 & (3 << 24))&&(LPC_GPIO2->FIODIR &(1UL<< 12))) //LED6
    {
     	if (LPC_GPIO2->FIOPIN &(1UL<< 12)) //LED 6
      {SetCursorPosition(ix_LED_RGB-8,iy_LED_RGB);printf("X\n");}  
      else{SetCursorPosition(ix_LED_RGB-8,iy_LED_RGB);printf("O\n");} 
	  }
	  if (!(LPC_PINCON->PINSEL4 & (3 << 26))&&(LPC_GPIO2->FIODIR &(1UL<< 13))) //LED7
    {
	    if (LPC_GPIO2->FIOPIN &(1UL<< 13)) //LED 7
      {SetCursorPosition(ix_LED_RGB-4,iy_LED_RGB-2);printf("X\n");}  
      else{SetCursorPosition(ix_LED_RGB-4,iy_LED_RGB-2);printf("O\n");} 
	  }	
		//Switches
	  if (!(LPC_PINCON->PINSEL3 & (3 << 4)) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 4))-( 2 << 4)) && !(LPC_GPIO1->FIODIR &(1UL<< 18))) //Switch S0
    {
	    if (LPC_GPIO1->FIOPIN & (1UL << 18)) //Switch S0
      {SetCursorPosition(ix_Switch+3,iy_Switch+11);printf(" ->\n");}  
      else{SetCursorPosition(ix_Switch+3,iy_Switch+11);printf("<- \n");} 
	  }	
	  if (!(LPC_PINCON->PINSEL3 & (3 << 6)) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 6))-( 2 << 6)) && !(LPC_GPIO1->FIODIR &(1UL<< 19))) //Switch S1
    {
	    if (LPC_GPIO1->FIOPIN & (1UL << 19)) //Switch S1
      {SetCursorPosition(ix_Switch+3,iy_Switch+10);printf(" ->\n");}  
      else{SetCursorPosition(ix_Switch+3,iy_Switch+10);printf("<- \n");} 
	  }	
	  if (!(LPC_PINCON->PINSEL3 & (3 << 8)) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 8))-( 2 << 8)) && !(LPC_GPIO1->FIODIR &(1UL<< 20))) //Switch S2
    {
	    if (LPC_GPIO1->FIOPIN & (1UL << 20)) //Switch S2
      {SetCursorPosition(ix_Switch+3,iy_Switch+9);printf(" ->\n");}  
      else{SetCursorPosition(ix_Switch+3,iy_Switch+9);printf("<- \n");} 
	  }	
	  if (!(LPC_PINCON->PINSEL3 & (3 << 10)) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 10))-( 2 << 10)) && !(LPC_GPIO1->FIODIR &(1UL<< 21))) //Switch S3
    {
	    if (LPC_GPIO1->FIOPIN & (1UL << 21)) //Switch S3
      {SetCursorPosition(ix_Switch+3,iy_Switch+8);printf(" ->\n");}  
      else{SetCursorPosition(ix_Switch+3,iy_Switch+8);printf("<- \n");} 
	  }	
	  if (!(LPC_PINCON->PINSEL3 & (3 << 12)) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 12))-( 2 << 12)) && !(LPC_GPIO1->FIODIR &(1UL<< 22))) //Switch S4
    {
	    if (LPC_GPIO1->FIOPIN & (1UL << 22)) //Switch S4
      {SetCursorPosition(ix_Switch+3,iy_Switch+7);printf(" ->\n");}  
      else{SetCursorPosition(ix_Switch+3,iy_Switch+7);printf("<- \n");} 
	  }	
	  if (!(LPC_PINCON->PINSEL3 & (3 << 14)) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 14))-( 2 << 14)) && !(LPC_GPIO1->FIODIR &(1UL<< 23))) //Switch S5
    {
	    if (LPC_GPIO1->FIOPIN & (1UL << 23)) //Switch S5
      {SetCursorPosition(ix_Switch+3,iy_Switch+6);printf(" ->\n");}  
      else{SetCursorPosition(ix_Switch+3,iy_Switch+6);printf("<- \n");} 
	  }	
	  if (!(LPC_PINCON->PINSEL3 & (3 << 16)) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 16))-( 2 << 16)) && !(LPC_GPIO1->FIODIR &(1UL<< 24))) //Switch S6
    {
	    if (LPC_GPIO1->FIOPIN & (1UL << 24)) //Switch S6
      {SetCursorPosition(ix_Switch+3,iy_Switch+5);printf(" ->\n");}  
      else{SetCursorPosition(ix_Switch+3,iy_Switch+5);printf("<- \n");} 
	  }	
	  if (!(LPC_PINCON->PINSEL3 & (3 << 18)) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 18))-( 2 << 18)) && !(LPC_GPIO1->FIODIR &(1UL<< 25))) //Switch S7
    {
	    if (LPC_GPIO1->FIOPIN & (1UL << 25)) //Switch S7
      {SetCursorPosition(ix_Switch+3,iy_Switch+4);printf(" ->\n");}  
      else{SetCursorPosition(ix_Switch+3,iy_Switch+4);printf("<- \n");} 
	  }	
		//Joystick
		if (!(LPC_PINCON->PINSEL1 & (3 << 18)) &&  !((LPC_PINCON->PINMODE1 & ( 3 << 18))-( 2 << 18)) && !(LPC_GPIO0->FIODIR &(1UL<< 25))) //JST Left
    {
	    if (LPC_GPIO0->FIOPIN & (1UL << 25)) //JST Left
      {SetCursorPosition(ix_JST-2,iy_JST+3);printf("X\n");}  
      else{SetCursorPosition(ix_JST-2,iy_JST+3);printf("O\n");} 
	  }	
		if (!(LPC_PINCON->PINSEL1 & (3 << 24)) /*&&  !((LPC_PINCON->PINMODE1 & ( 3 << 24))-( 2 << 24))*/ && !(LPC_GPIO0->FIODIR &(1UL<< 28))) //JST Right
    {
	    if (LPC_GPIO0->FIOPIN & (1UL << 28)) //JST Right
      {SetCursorPosition(ix_JST+2,iy_JST+3);printf("X\n");}  
      else{SetCursorPosition(ix_JST+2,iy_JST+3);printf("O\n");} 
	  }	
		if (!(LPC_PINCON->PINSEL1 & (3 << 10)) &&  !((LPC_PINCON->PINMODE1 & ( 3 << 10))-( 2 << 10)) && !(LPC_GPIO0->FIODIR &(1UL<< 21))) //JST Up
    {
	    if (LPC_GPIO0->FIOPIN & (1UL << 21)) //JST Up
      {SetCursorPosition(ix_JST,iy_JST+2);printf("X\n");}  
      else{SetCursorPosition(ix_JST,iy_JST+2);printf("O\n");} 
	  }	
		if (!(LPC_PINCON->PINSEL1 & (3 << 22)) /*&&  !((LPC_PINCON->PINMODE1 & ( 3 << 22))-( 2 << 22))*/ && !(LPC_GPIO0->FIODIR &(1UL<< 27))) //JST Down
    {
	    if (LPC_GPIO0->FIOPIN & (1UL << 27)) //JST Down
      {SetCursorPosition(ix_JST,iy_JST+4);printf("X\n");}  
      else{SetCursorPosition(ix_JST,iy_JST+4);printf("O\n");} 
	  }	
		if (!(LPC_PINCON->PINSEL0 & (3 << 6)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 6))-( 2 << 6)) && !(LPC_GPIO0->FIODIR &(1UL<< 3))) //JST Center
    {
	    if (LPC_GPIO0->FIOPIN & (1UL << 3)) //JST Center
      {SetCursorPosition(ix_JST,iy_JST+3);printf("X\n");}  
      else{SetCursorPosition(ix_JST,iy_JST+3);printf("O\n");} 
	    if ((LPC_GPIO0->FIOPIN & (1UL << 3))&& (LPC_GPIO0->FIOPIN & (1UL << 21))&& (LPC_GPIO0->FIOPIN & (1UL << 25))&&(LPC_GPIO0->FIOPIN & (1UL << 27))&&(LPC_GPIO0->FIOPIN & (1UL << 28))) //Rest all
			{
				SetCursorPosition(ix_JST,iy_JST+3);printf("O\n");
				SetCursorPosition(ix_JST,iy_JST+4);printf("O\n");
				SetCursorPosition(ix_JST,iy_JST+2);printf("O\n");
				SetCursorPosition(ix_JST+2,iy_JST+3);printf("O\n");
				SetCursorPosition(ix_JST-2,iy_JST+3);printf("O\n");
			}			
	  }	
		//Switch TA10, TA11 and TA12
    if ((!(LPC_PINCON->PINSEL3 & (3 << 20)) || (!((LPC_PINCON->PINSEL3 & ( 3 << 20))-( 3 << 20))) ) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 20))-( 2 << 20)) && !(LPC_GPIO1->FIODIR &(1UL<< 26))) //TA 10
    {
	    if (iS_TA10) //TA 10
				{SetCursorPosition(ix_Switch+9,iy_Switch+1);printf("X\n");LPC_GPIO1->FIOMASK&=~(1UL<<26);}  	// vorher:ix_Switch-1
      else{SetCursorPosition(ix_Switch+9,iy_Switch+1);printf("O\n");LPC_GPIO1->FIOMASK|=(1UL<<26);}  	// vorher:ix_Switch-1
	  }	
    if ((!(LPC_PINCON->PINSEL3 & (3 << 22)) || (!((LPC_PINCON->PINSEL3 & ( 3 << 22))-( 3 << 22))) ) &&  !((LPC_PINCON->PINMODE3 & ( 3 << 22))-( 2 << 22)) && !(LPC_GPIO1->FIODIR &(1UL<< 27))) //TA 11
    {
	    if (iS_TA11) //TA 11
      {SetCursorPosition(ix_Switch+4,iy_Switch+1);printf("X\n");LPC_GPIO1->FIOMASK&=~(1UL<<27);}  
      else{SetCursorPosition(ix_Switch+4,iy_Switch+1);printf("O\n");LPC_GPIO1->FIOMASK|=(1UL<<27);} 
	  }	
    if ((!(LPC_PINCON->PINSEL4 & (3 << 22)) || (!((LPC_PINCON->PINSEL4 & ( 3 << 22))-( 1 << 22))) ) &&  !((LPC_PINCON->PINMODE4 & ( 3 << 22))-( 2 << 22)) && !(LPC_GPIO1->FIODIR &(1UL<< 11))) //TA 12
    { 
			if (iFlag_Sim & (1<<0))
			{
				iTA12_time++;
	      if (iS_TA12) //TA 12
        {SetCursorPosition(ix_Switch-1,iy_Switch+1);printf("X\n");}  		 	// vorher:ix_Switch+9
        else{SetCursorPosition(ix_Switch-1,iy_Switch+1);printf("O\n");} 	// vorher:ix_Switch+9
				if (iTA12_time > 5)
				{	
					iTA12_iz1++;
					if ((iTA12_iz1&1) | (iTA12_iz1> 5))
					{
  	        if (iS_TA12) //TA 12
            {LPC_GPIO2->FIOMASK&=~(1UL<<11);}  
            else{LPC_GPIO2->FIOMASK|=(1UL<<11);} 
				  }
					else
					{
						LPC_GPIO2->FIOMASK|=(1UL<<11);
					}
		   	  iTA12_time=0;
				}
				if (!iS_TA12){LPC_GPIO2->FIOMASK|=(1UL<<11);iTA12_iz1=0;} //TA 12
			}
			else
			{
	      if (iS_TA12) //TA 12
        {SetCursorPosition(ix_Switch-1,iy_Switch+1);printf("X\n");}  
        else{SetCursorPosition(ix_Switch-1,iy_Switch+1);printf("O\n");} 
		  }
	  }	
    //3x3 Matrix
		// set input ports to 0
		if (!(LPC_PINCON->PINSEL0 & (3 << 8)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 8))-( 2 << 8)) && !(LPC_GPIO0->FIODIR &(1UL<< 4))) // Port 0.4 Input	
    {
			//LPC_GPIO0->FIOMASK |= (1UL << 4);
		}
    if (!(LPC_PINCON->PINSEL0 & (3 << 10)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 10))-( 2 << 10)) && !(LPC_GPIO0->FIODIR &(1UL<< 5))) // Port 0.5 Input	
    {
			//LPC_GPIO0->FIOMASK |= (1UL << 5);
	  }
    if (!(LPC_PINCON->PINSEL7 & (3 << 20)) &&  !((LPC_PINCON->PINMODE7 & ( 3 << 20))-( 2 << 20)) && !(LPC_GPIO3->FIODIR &(1UL<< 26))) // Port 3.26 Input	
    {
			//LPC_GPIO3->FIOMASK |= (1UL << 26);
		}
		// set input ports
		if (!(LPC_PINCON->PINSEL4 & (3 << 6))&&(LPC_GPIO2->FIODIR &(1UL<< 3))) // Port P2.3  Output
    {
      if (!(LPC_PINCON->PINSEL0 & (3 << 8)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 8))-( 2 << 8)) && !(LPC_GPIO0->FIODIR &(1UL<< 4))) // Port 0.4 Input	
      {
				if (iS_TA1)  // TA1
				{
					SetCursorPosition(ix_JST-2,iy_JST+8);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 3) & 1<<0) > 0)LPC_GPIO0->FIOMASK &= ~(1UL << 4);
				}
				else
 				{
					SetCursorPosition(ix_JST-2,iy_JST+8);printf("1\n");
					//if(!(iS_TA1 || iS_TA4 || iS_TA7))LPC_GPIO0->FIOMASK |= (1UL << 4);
				}
			}
      if (!(LPC_PINCON->PINSEL0 & (3 << 10)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 10))-( 2 << 10)) && !(LPC_GPIO0->FIODIR &(1UL<< 5))) // Port 0.5 Input	
      {
				if (iS_TA2)  //TA2
				{
					SetCursorPosition(ix_JST,iy_JST+8);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 3) & 1<<0) > 0)LPC_GPIO0->FIOMASK &= ~(1UL << 5);
				}
				else
 				{
					SetCursorPosition(ix_JST,iy_JST+8);printf("2\n");
					//if(!(iS_TA2 || iS_TA5 || iS_TA8))LPC_GPIO0->FIOMASK |= (1UL << 5);
				}
			}
      if (!(LPC_PINCON->PINSEL7 & (3 << 20)) &&  !((LPC_PINCON->PINMODE7 & ( 3 << 20))-( 2 << 20)) && !(LPC_GPIO3->FIODIR &(1UL<< 26))) // Port 3.26 Input	
      {
				if (iS_TA3)  //TA3
				{
					SetCursorPosition(ix_JST+2,iy_JST+8);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 3) & 1<<0) > 0)LPC_GPIO3->FIOMASK &= ~(1UL << 26);
				}
				else
 				{
					SetCursorPosition(ix_JST+2,iy_JST+8);printf("3\n");
					//if(!(iS_TA3 || iS_TA6 || iS_TA9))LPC_GPIO3->FIOMASK |= (1UL << 26);
				}
			}
    }				 
 		if (!(LPC_PINCON->PINSEL4 & (3 << 8))&&(LPC_GPIO2->FIODIR &(1UL<< 4))) // Port P2.4  Output
    {
      if (!(LPC_PINCON->PINSEL0 & (3 << 8)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 8))-( 2 << 8)) && !(LPC_GPIO0->FIODIR &(1UL<< 4))) // Port 0.4 Input	
      {
				if (iS_TA4)  // TA4
				{
					SetCursorPosition(ix_JST-2,iy_JST+9);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 4) & 1<<0) > 0)LPC_GPIO0->FIOMASK &= ~(1UL << 4);
				}
				else
 				{
					SetCursorPosition(ix_JST-2,iy_JST+9);printf("4\n");
					//if(!(iS_TA1 || iS_TA4 || iS_TA7))LPC_GPIO0->FIOMASK |= (1UL << 4);
				}
			}
      if (!(LPC_PINCON->PINSEL0 & (3 << 10)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 10))-( 2 << 10)) && !(LPC_GPIO0->FIODIR &(1UL<< 5))) // Port 0.5 Input	
      {
				if (iS_TA5)  //TA5
				{
					SetCursorPosition(ix_JST,iy_JST+9);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 4) & 1<<0) > 0)LPC_GPIO0->FIOMASK &= ~(1UL << 5);
				}
				else
 				{
					SetCursorPosition(ix_JST,iy_JST+9);printf("5\n");
					//if(!(iS_TA2 || iS_TA5 || iS_TA8))LPC_GPIO0->FIOMASK |= (1UL << 5);
				}
				if (iS_TA6)  //TA6
				{
					SetCursorPosition(ix_JST+2,iy_JST+9);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 4) & 1<<0) > 0)LPC_GPIO3->FIOMASK &= ~(1UL << 26);
				}
				else
 				{
					SetCursorPosition(ix_JST+2,iy_JST+9);printf("6\n");
					//if(!(iS_TA3 || iS_TA6 || iS_TA9))LPC_GPIO3->FIOMASK |= (1UL << 26);
				}
      }		
    }			
 		if (!(LPC_PINCON->PINSEL4 & (3 << 10))&&(LPC_GPIO2->FIODIR &(1UL<< 5))) // Port P2.5  Output
    {
      if (!(LPC_PINCON->PINSEL0 & (3 << 8)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 8))-( 2 << 8)) && !(LPC_GPIO0->FIODIR &(1UL<< 4))) // Port 0.4 Input	
      {
				if (iS_TA7)  // TA7
				{
					SetCursorPosition(ix_JST-2,iy_JST+10);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 5) & 1<<0) > 0)LPC_GPIO0->FIOMASK &= ~(1UL << 4);
				}
				else
 				{
					SetCursorPosition(ix_JST-2,iy_JST+10);printf("7\n");
					//if(!(iS_TA1 || iS_TA4 || iS_TA7))LPC_GPIO0->FIOMASK |= (1UL << 4);
				}
			}
      if (!(LPC_PINCON->PINSEL0 & (3 << 10)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 10))-( 2 << 10)) && !(LPC_GPIO0->FIODIR &(1UL<< 5))) // Port 0.5 Input	
      {
				if (iS_TA8)  //TA8
				{
					SetCursorPosition(ix_JST,iy_JST+10);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 5) & 1<<0) > 0)LPC_GPIO0->FIOMASK &= ~(1UL << 5);
				}
				else
 				{
					SetCursorPosition(ix_JST,iy_JST+10);printf("8\n");
					//if(!(iS_TA2 || iS_TA5 || iS_TA8))LPC_GPIO0->FIOMASK |= (1UL << 5);
				}
			}
      if (!(LPC_PINCON->PINSEL7 & (3 << 20)) &&  !((LPC_PINCON->PINMODE7 & ( 3 << 20))-( 2 << 20)) && !(LPC_GPIO3->FIODIR &(1UL<< 26))) // Port 3.26 Input	
      {
				if (iS_TA9)  //TA9
				{
					SetCursorPosition(ix_JST+2,iy_JST+10);printf("X\n");
					//if (((LPC_GPIO2->FIOPIN >> 5) & 1<<0) > 0)LPC_GPIO3->FIOMASK &= ~(1UL << 26);
				}
				else
 				{
					SetCursorPosition(ix_JST+2,iy_JST+10);printf("9\n");
					//if(!(iS_TA3 || iS_TA6 || iS_TA9))LPC_GPIO3->FIOMASK |= (1UL << 26);
				}
      }				 
    }
		// Encoder
    if ((!(LPC_PINCON->PINSEL4 & (3 << 20)) || (!((LPC_PINCON->PINSEL4 & ( 3 << 20))-( 1 << 20))) ) &&  !((LPC_PINCON->PINMODE4 & ( 3 << 20))-( 2 << 20)) && !(LPC_GPIO1->FIODIR &(1UL<< 10))) //Encoder Button
    { 
	      if (iS_Enc) //Encoder
        {SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB+9);printf("X\n");}  
        else{SetCursorPosition(ix_LED_RGB+1,iy_LED_RGB+9);printf("O\n");} 		  
	  }	
  } 
	if (LPC_SC->PCONP & (1 << 21))  //nur wenn Power on SPP0
	{
    if ((!((LPC_PINCON->PINSEL0 & ( 3UL << 30))-( 2UL << 30))) || (!((LPC_PINCON->PINSEL1 & ( 3 << 4))-( 2 << 4))) )  //SPPI enablede
		{
      if (!(LPC_PINCON->PINSEL0 & (3 << 2)) &&  !((LPC_PINCON->PINMODE0 & ( 3 << 2))-( 2 << 2)) && (LPC_GPIO0->FIODIR &(1UL<< 1))) // Port 0.1 Output	
			{
				if(!(LPC_GPIO0->FIOPIN &(1UL<< 1)))
				{
  				if (!(i7Seg & (1<<0)))//d
          {SetCursorPosition(ix_7Seg+3,iy_7Seg+6);printf("-\n");}  
          else{SetCursorPosition(ix_7Seg+3,iy_7Seg+6);printf(" \n");} 		  
  				if (!(i7Seg & (1<<1)))//e
          {SetCursorPosition(ix_7Seg+2,iy_7Seg+5);printf("|\n");}  
          else{SetCursorPosition(ix_7Seg+2,iy_7Seg+5);printf(" \n");} 		  
  				if (!(i7Seg & (1<<2)))//g
          {SetCursorPosition(ix_7Seg+3,iy_7Seg+4);printf("-\n");}  
          else{SetCursorPosition(ix_7Seg+3,iy_7Seg+4);printf(" \n");} 		  
  				if (!(i7Seg & (1<<3)))//a
          {SetCursorPosition(ix_7Seg+3,iy_7Seg+2);printf("-\n");}  
          else{SetCursorPosition(ix_7Seg+3,iy_7Seg+2);printf(" \n");} 		  
  				if (!(i7Seg & (1<<4)))//b
          {SetCursorPosition(ix_7Seg+4,iy_7Seg+3);printf("|\n");}  
          else{SetCursorPosition(ix_7Seg+4,iy_7Seg+3);printf(" \n");} 		  
  				if (!(i7Seg & (1<<5)))//DP
          {SetCursorPosition(ix_7Seg+5,iy_7Seg+6);printf(".\n");}  
          else{SetCursorPosition(ix_7Seg+6,iy_7Seg+6);printf(" \n");} 		  
  				if (!(i7Seg & (1<<6)))//c
          {SetCursorPosition(ix_7Seg+4,iy_7Seg+5);printf("|\n");}  
          else{SetCursorPosition(ix_7Seg+4,iy_7Seg+5);printf(" \n");} 		  
  				if (!(i7Seg & (1<<7)))//f
          {SetCursorPosition(ix_7Seg+2,iy_7Seg+3);printf("|\n");}  
          else{SetCursorPosition(ix_7Seg+2,iy_7Seg+3);printf(" \n");} 
        }					
			}
      if (!(LPC_PINCON->PINSEL7 & (3 << 18)) &&  !((LPC_PINCON->PINMODE7 & ( 3 << 18))-( 2 << 18)) && (LPC_GPIO3->FIODIR &(1UL<< 25))) // Port 0.1 Output	
			{
				if(!(LPC_GPIO3->FIOPIN &(1UL<< 25)))
				{
  				if (!(i7Seg & (1<<0)))  //d
          {SetCursorPosition(ix_7Seg+10,iy_7Seg+6);printf("-\n");}  
          else{SetCursorPosition(ix_7Seg+10,iy_7Seg+6);printf(" \n");} 		  
  				if (!(i7Seg & (1<<1)))  //e
          {SetCursorPosition(ix_7Seg+9,iy_7Seg+5);printf("|\n");}  
          else{SetCursorPosition(ix_7Seg+9,iy_7Seg+5);printf(" \n");} 		  
  				if (!(i7Seg & (1<<2))) //g
          {SetCursorPosition(ix_7Seg+10,iy_7Seg+4);printf("-\n");}  
          else{SetCursorPosition(ix_7Seg+10,iy_7Seg+4);printf(" \n");} 		  
  				if (!(i7Seg & (1<<3))) //a
          {SetCursorPosition(ix_7Seg+10,iy_7Seg+2);printf("-\n");}  
          else{SetCursorPosition(ix_7Seg+10,iy_7Seg+2);printf(" \n");} 		  
  				if (!(i7Seg & (1<<4))) //b
          {SetCursorPosition(ix_7Seg+11,iy_7Seg+3);printf("|\n");}  
          else{SetCursorPosition(ix_7Seg+11,iy_7Seg+3);printf(" \n");} 		  
  				if (!(i7Seg & (1<<5))) //DP
          {SetCursorPosition(ix_7Seg+12,iy_7Seg+6);printf(".\n");}  
          else{SetCursorPosition(ix_7Seg+12,iy_7Seg+6);printf(" \n");} 		  
  				if (!(i7Seg & (1<<6))) //c
          {SetCursorPosition(ix_7Seg+11,iy_7Seg+5);printf("|\n");}  
          else{SetCursorPosition(ix_7Seg+11,iy_7Seg+5);printf(" \n");} 		  
  				if (!(i7Seg & (1<<7)))  //f
          {SetCursorPosition(ix_7Seg+9,iy_7Seg+3);printf("|\n");}  
          else{SetCursorPosition(ix_7Seg+9,iy_7Seg+3);printf(" \n");} 
        }					
			}
		}
	}
  return;
}





/*******************************************************************************
* Set draw window region                                                       *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        window width in pixel                            *
*                   h:        window height in pixels                          *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_SetWindow (unsigned int x, unsigned int y, unsigned int w, unsigned int h) 
{
	return;
}


/*******************************************************************************
* Set draw window region to whole screen                                       *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_WindowMax (void) 
{
  return;
}


/*******************************************************************************
* Draw a pixel in foreground color                                             *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_PutPixel (unsigned int x, unsigned int y) 
{
  return;
}



/*******************************************************************************
* Clear display                                                                *
*   Parameter:      color:    display clearing color                           *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_Clear (unsigned short color) 
{
	unsigned int iz1;
	switch (color)
	{
		case	0x0000:
			ibgCol=0;
		break;
		case	0x000F:
			ibgCol=1;
		break;
		case	0x03E0:
			ibgCol=2;
		break;
		case	0x03EF:
			ibgCol=3;
		break;
		case	0x7800:
			ibgCol=4;
		break;
		case	0x780F:
			ibgCol=5;
		break;
		case	0x7BE0:
			ibgCol=6;
		break;
		case	0xC618:
			ibgCol=7;
		break;
		case	0x7BEF:
			ibgCol=8;
		break;
		case	0x001F:
			ibgCol=9;
		break;
		case	0x07E0:
			ibgCol=10;
		break;
		case	0x07FF:
			ibgCol=11;
		break;
		case	0xF800:
			ibgCol=12;
		break;
		case	0xF81F:
			ibgCol=13;
		break;
		case	0xFFE0:
			ibgCol=14;
		break;
		case	0xFFFF:
			ibgCol=15;
		break;
		default:
		  ibgCol=15;
	}

  for (iz1=0;iz1<10;iz1++)GLCD_S_ClearLn (iz1,1);
}


/*******************************************************************************
* Draw character on given position                                             *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   cw:       character width in pixel                         *
*                   ch:       character height in pixels                       *
*                   c:        pointer to character bitmap                      *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_DrawChar (unsigned int ix, unsigned int iy, unsigned int cw, unsigned int ch, unsigned char *c) 
{
  GLCD_S_DisplayString (ix, iy, 1, c);
}


/*******************************************************************************
* Disply character on given line                                               *
*   Parameter:      ln:       line number                                      *
*                   col:      column number                                    *
*                   fi:       font index (0 = 6x8, 1 = 16x24)                  *
*                   c:        ascii character                                  *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_DisplayChar (unsigned int iln, unsigned int icol, unsigned char fi, unsigned char c)
{
	unsigned char buf[2];
	buf[0]=c;
	buf[1]=0;
  GLCD_S_DisplayString (iln, icol, fi, buf);
}




/*******************************************************************************
* Clear given line                                                             *
*   Parameter:      ln:       line number                                      *
*                   fi:       font index (0 = 6x8, 1 = 16x24)                  *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_ClearLn (unsigned int iln, unsigned char fi) 
{
  unsigned char iz1;
  unsigned char buf[60];

  for (iz1 = 0; iz1 < 30; iz1++)buf[iz1] = ' ';
  buf[iz1+1] = 0;
  GLCD_S_DisplayString (iln, 0, fi, buf);
}

/*******************************************************************************
* Draw bargraph                                                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        maximum width of bargraph (in pixels)            *
*                   h:        bargraph height                                  *
*                   val:      value of active bargraph (in 1/1024)             *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_Bargraph (unsigned int ix, unsigned int iy, unsigned int iw, unsigned int ih, unsigned int ival) 
{
  unsigned int i_x,i_y,idx,i_val,iz1=0;
	unsigned char text[21];
	i_x=ix/16;
	i_y=iy/24;
	if ((ix-i_x*16)>7)i_x++;
	if ((iy-i_y*24)>11)i_y++;
	idx=iw/16;
	if((i_x+idx)>20)idx=20-i_x;
  i_val = (unsigned int)((float)ival/(1024) * idx);  
	if((((float)ival/(1024) * idx)-i_val)>0.5)i_val++;
	if (i_val > idx)i_val=idx;
	if(i_val == 0)
  {
	  text[0]=124;iz1++;
		for (iz1=1;iz1<idx;iz1++)text[iz1]=32;
	}
	else
	{
	  for (iz1=0;iz1<i_val;iz1++)text[iz1]=88;
		for (iz1=i_val;iz1<idx;iz1++)text[iz1]=32;
	}
	text[idx]=0;
	GLCD_S_DisplayString(i_y,i_x,1,text);
  return;
}


/*******************************************************************************
* Dummy function Display graphical bitmap image at position x horizontally and y vertically   *
* (This function is optimized for 16 bits per pixel format, it has to be       *
*  adapted for any other bits per pixel format)                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        width of bitmap                                  *
*                   h:        height of bitmap                                 *
*                   bitmap:   address at which the bitmap data resides         *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_Bitmap (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap) 
{
 return;
}



/*******************************************************************************
* Dummy function Scroll content of the whole display for dy pixels vertically                 *
*   Parameter:      dy:       number of pixels for vertical scroll             *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_S_ScrollVertical (unsigned int dy) {
#if (LANDSCAPE == 0)
	return;
#endif
}


/*******************************************************************************
* Dummy function Write a command to the LCD controller                                        *
*   Parameter:      cmd:      command to write to the LCD                      *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_S_WrCmd (unsigned char cmd) {
  return;
}


/*******************************************************************************
* Dummy function Write a value into LCD controller register                                   *
*   Parameter:      reg:      lcd register address                             *
*                   val:      value to write into reg                          *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_S_WrReg (unsigned char reg, unsigned short val) {
  return;
}
/******************************************************************************/

/*******************************************************************************
* Dummy function Write a command to the LCD controller                                        *
*   Parameter:      cmd:      command to write to the LCD                      *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_S_WrDat (unsigned short val) {
  return;
}
