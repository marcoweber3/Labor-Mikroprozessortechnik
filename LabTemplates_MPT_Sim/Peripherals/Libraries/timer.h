#ifndef timer
#define timer

void counter_Init (uint8_t TimerNum, uint8_t CapIn, uint8_t edge);
void Timer_Init (uint8_t TimerNum, uint32_t cycle, uint32_t TimerDivid, uint8_t pclk , uint8_t ResetMR);

#endif

