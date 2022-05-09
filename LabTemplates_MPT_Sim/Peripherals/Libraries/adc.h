#ifndef adc
#define adc

void ADC_Init (uint8_t chsel, uint8_t intEn);
void ADC_StartCnv (uint8_t chsel, uint8_t burst);	
void ADC_StopCnv (void); 
uint32_t ADC_Stat (void); 	
uint32_t ADC_GetValue(unsigned int channel);

#endif

