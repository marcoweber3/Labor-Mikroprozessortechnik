#include <lpc17xx.h>
#define SUCCESS 0
#define ERROR !SUCCESS
void    I2C1_Init(void);
int32_t I2C1Write(uint8_t addr, uint8_t *tx_data, uint8_t tx_length);
int32_t I2C1Read(uint8_t addr,uint8_t *rx_data, uint8_t rx_length);


