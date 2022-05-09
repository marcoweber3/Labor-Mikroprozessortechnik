/*================================================================================
HEADER FILE GLCD_S_S.h:
--------------------------------------------------------------------------------
Datum: 
--------------------------------------------------------------------------------
Autor: 
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
Beschreibung: Funktionsprotoytpen/ Deklarationen v. Bibliotheksfunktionen
           -> LED_Init()
           -> LED_On()
					 -> LED_Off()

--------------------------------------------------------------------------------
Hinweise:     Definitionen/ Implementierungen v. Bibliotheksfunktionen
           -> siehe Source File delay.c
================================================================================
*/

#ifndef __GLCD_S_S_H //Anfang bedingte Kompilierung
#define __GLCD_S_S_H


//================================================================================
//Einbinden v. Header Files:
//================================================================================


//================================================================================
//Definition v. Konstanten:
//================================================================================
#define ix_offset 1
#define iy_offset 2


//================================================================================
//Globale Variable festlegen:
//================================================================================
static volatile unsigned short ibgCol=1,itextCol=1;
static char cCol[16][10];
static unsigned short int iS_S0=0,iS_S1=0,iS_S2=0,iS_S3=0,iS_S4=0,iS_S5=0,iS_S6=0,iS_S7=0;
static unsigned short int iS_JST_L=0,iS_JST_R=0,iS_JST_U=0,iS_JST_D=0;
static unsigned short int iS_TA10=0,iS_TA11=0,iS_TA12=0;
static unsigned short int iS_TA1=0,iS_TA2=0,iS_TA3=0,iS_TA4=0,iS_TA5=0,iS_TA6=0,iS_TA7=0,iS_TA8=0,iS_TA9=0,iS_Enc=0;
static unsigned  int iFlag_Sim;
static unsigned short i7Seg=255;
//================================================================================
//Funktionsprototypen/ Deklarationen v. Bibliotheksfunktionen:
//================================================================================
//Debug printf-Bildschirm löschen 
//--------------------------------------------------------------------------------
extern void ClearScreen(void);

//================================================================================
//Funktionsprototypen/ Deklarationen v. Bibliotheksfunktionen:
//================================================================================
//Debug printf-Bildschirm: Cursor-Position setzen 
//--------------------------------------------------------------------------------
extern void SetCursorPosition(int x, int y);

//================================================================================
//Funktionsprototypen/ Deklarationen v. Bibliotheksfunktionen:
//================================================================================
//Debug printf-Bildschirm: Linie rechts von der Cursor-Position slöschen 
//--------------------------------------------------------------------------------
extern void DeleteLineRight(void);

// Definition der GLCD_S Simulationsfunktionen
/* GLCD_S RGB color definitions                                                 */
#define Black           0x0000      /*   0,   0,   0 */
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Blue            0x001F      /*   0,   0, 255 */
#define Green           0x07E0      /*   0, 255,   0 */
#define Cyan            0x07FF      /*   0, 255, 255 */
#define Red             0xF800      /* 255,   0,   0 */
#define Magenta         0xF81F      /* 255,   0, 255 */
#define Yellow          0xFFE0      /* 255, 255, 0   */
#define White           0xFFFF      /* 255, 255, 255 */

extern void GLCD_S_Init           (void);
extern void GLCD_S_WindowMax      (void);
extern void GLCD_S_PutPixel       (unsigned int x, unsigned int y);
extern void GLCD_S_SetTextColor   (unsigned short color);
extern void GLCD_S_SetBackColor   (unsigned short color);
extern void GLCD_S_Clear          (unsigned short color);
extern void GLCD_S_DrawChar       (unsigned int x,  unsigned int y, unsigned int cw, unsigned int ch, unsigned char *c);
extern void GLCD_S_DisplayChar    (unsigned int ln, unsigned int col, unsigned char fi, unsigned char  c);
extern void GLCD_S_DisplayString  (unsigned int ln, unsigned int col, unsigned char fi, unsigned char *s);
extern void GLCD_S_ClearLn        (unsigned int ln, unsigned char fi);
extern void GLCD_S_Bargraph       (unsigned int x,  unsigned int y, unsigned int w, unsigned int h, unsigned int val);
extern void GLCD_S_Bitmap         (unsigned int x,  unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap);
extern void GLCD_S_ScrollVertical (unsigned int dy);

extern void GLCD_S_WrCmd          (unsigned char cmd);
extern void GLCD_S_WrReg          (unsigned char reg, unsigned short val); 
extern void GLCD_S_WrDat          (unsigned short val);

extern void GLCD_S_Simulation (void);
#endif //Ende bedingte Kompilierung

