#ifndef keys
#define keys


//Swich
void Switch_Init(void);
unsigned char Get_SwitchPos(void);


//Button
void button_Init(void);
unsigned int Get_TA12Stat(void);
unsigned int Get_TA10Stat(void);
unsigned int Get_TA11Stat(void);

//JoyStick
void Joystick_Init(void);
unsigned int Get_LeftStat(void);
unsigned int Get_RightStat(void);
unsigned int Get_UpStat(void);
unsigned int Get_DownStat(void);
unsigned int Get_CenterStat(void);
void JoyStick_IRQ_Init(void);

unsigned int KeyFlipFlop(unsigned int stat, unsigned int statBefore);

void Matrix_Init(void);
unsigned char Get_Mkey(void);

void Encoder_Init(void);

#endif


