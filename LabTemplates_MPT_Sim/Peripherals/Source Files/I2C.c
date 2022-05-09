#include <lpc17xx.h>
#include <I2C.h>

void I2C1_Init() {
  LPC_SC->PCONP |= (1 << 15)|(1<<19);	//enable GPIO and  the I2C-peripheral in PCONP	
  LPC_PINCON->PINSEL1 |= (3 << 6)|(3 << 8); // enable I2C1-function of P0.19 und P0.20
  LPC_PINCON->PINMODE1 &= ~((3 << 6)|(3 << 8));
  LPC_PINCON->PINMODE1 |= (2 << 6)|(2 << 8) ;//deactivate Pullup/ Pulldown
  LPC_PINCON->PINMODE_OD0 |= (1 << 19)|(1 << 20);// enable opendrain for P0.19, P0.20
  LPC_SC->PCLKSEL1 &= ~(3 << 6); LPC_SC->PCLKSEL1 |= (1 << 6); // PCLK of I2C1 = cclk 
  // adjust bit rate of the I²C-Bus to 100 kHz with duty-cycle of 50 %
  // SCL1-clock = 100 kHz = (PCLK_I2C1)/(I2SCLH + I2SCLL)
  // -> I2SCLH + I2SCLL = (PCLK_I2C1)/(SCL1-Takt) = 100 MHz/100 kHz = 1000
  // -> I2SCLH = I2SCLL = 1000/2 = 500
  LPC_I2C1->I2SCLL = 500;
  LPC_I2C1->I2SCLH = 500;
  //Bits 2(AA), 5(STA) and 6(I2EN) must be cleared
  LPC_I2C1->I2CONCLR = (1 << 2) | (1 << 5) | (1 << 6);
  LPC_I2C1->I2CONSET = (1 << 6); // enable I²C-Interface	
}


int32_t I2C1Write(uint8_t addr, uint8_t *tx_data, uint8_t tx_length){
  //Transmit data in master mode
  //tx_data Pointer to a buffer containing data to be transmitted.
  //tx_length Number of bytes to send
  //return SUCCESS or ERROR
  //local variables
  uint8_t ret = SUCCESS; //return value
  uint32_t code_status=0; //I2C1 status
  uint8_t tx_count=0;//transmit counter

  if (tx_data!=0){//parameters ok?
  //1. Reset the IR bit (SI) and output the start bit (STA)
  LPC_I2C1->I2CONCLR = (1<<3); //I2C interrupt Clear bit.
  LPC_I2C1->I2CONSET = (1<<5); //I2C set start bit Interrupt-Flag SI will be set to 1
  while (!(LPC_I2C1->I2CONSET & (1<<3))); // 2. Wait until the IR bit is set (SI)
  LPC_I2C1->I2CONCLR = (1<<5); //3. Reset the start bit (STA)
  //4. Verify the start bit has been successfully transmitted by checking the code “0x08” or “0x10”. //Only bits 7-3 in status register I2STAT should be evaluated.
  code_status=	LPC_I2C1->I2STAT & 0xF8;
  if((code_status == (0x08)) || (code_status == 0x10)) //start sucessful
  { // 5. Output the 7-bit slave address in bits 7-1 on the I2C bus with the register I2DAT. 
    // Bit 0 determines the transmission direction (0: transmit / 1: receive).
    LPC_I2C1->I2DAT = (((addr << 1) | 0x00)) & 0xFF; // Send slave address +WR direction bit = 0
    LPC_I2C1->I2CONCLR = (1<<3); //6. Reset the SI bit and wait until SI bit is set 
    while (!(LPC_I2C1->I2CONSET & (1<<3))); // check Interrupt flag SI, wait for complete sending
    //7. Verify the slave address and direction bit has been successfully transmitted.
    if((LPC_I2C1->I2STAT & 0xF8) == 0x18) /* SLA+W has been transmitted, ACK has been received */
      {//8. Transmit tx_length data bytes by writing register I2DAT and resetting the IR bit (SI)
	   if (tx_length>0)//send only data bytes, if tx_length>0
	   { tx_count=tx_length;//transmit tx_length data Bytes tx_length>=1
       do {// Repeat steps 8-10 until all data has been sent.
         LPC_I2C1->I2DAT=(*(tx_data+(tx_length-tx_count))&0xFF);
         LPC_I2C1->I2CONCLR = (1<<3); /** I2C interrupt Clear bit */
         while (!(LPC_I2C1->I2CONSET & (1<<3))); //9. check Interrupt flag SI Wait for complete sending
         // 10. Verify data has been successfully transmitted and acknowledge has been received by
         //checking the code “0x28” in the I2SSTAT register. Only bits 7-3 in status register I2STAT should
         //be evaluated. Abort the transmission if this code is incorrect.
         if (((LPC_I2C1->I2STAT & 0xF8) != 0x28))  ret =ERROR; //Data and ACK has been received
         tx_count--;
         } while ((tx_count>0)&&(ret!=ERROR)); 
	   }
       } else ret= ERROR;
    } else ret= ERROR;
  } else ret=ERROR;

  //12.send STOP condition: Output the stop bit (ST0) and reset the SI bit. 
  LPC_I2C1->I2CONSET = (1<<4); //Send Stop Bit
  LPC_I2C1->I2CONCLR = (1<<3); //I2C interrupt Clear bit
  return ret;
}


int32_t I2C1Read(uint8_t addr,uint8_t *rx_data, uint8_t rx_length){
  // Receive data in master mode
  // rx_data Pointer to a buffer where the received data must be stored.
  // rx_length Number of bytes to receive
  // return SUCCESS or ERROR
  //local variables
  uint8_t ret = SUCCESS; //return value
  uint32_t code_status = 0; //I2C1 status
  uint8_t rx_count=0; //receive counter

  if ((rx_length !=0)&&(rx_data!=0)) { //wrong parameters?
  //1. Reset the IR bit (SI) and output the start bit (STA)
  LPC_I2C1->I2CONCLR = (1<<3); //I2C interrupt Clear bit.
  LPC_I2C1->I2CONSET = (1<<5); //I2C set start bit Interrupt-Flag SI will be set to 1
  while (!(LPC_I2C1->I2CONSET & (1<<3))); // 2. Wait until the IR bit is set (SI)
  LPC_I2C1->I2CONCLR = (1<<5); // 3. Reset the start bit (STA)
  code_status=LPC_I2C1->I2STAT & 0xF8;	 //get bus status
  //4. Verify the start bit has been successfully transmitted by checking the code “0x08” or “0x10”. //Only bits 7-3 in status register I2STAT should be evaluated..
  if((code_status == (0x08)) || (code_status == 0x10)) { //start complete
    //5. Output the 7-bit slave address in bits 7-1 on the I2C bus with the register I2DAT. Bit 0 
    //determines the transmission direction (0: transmit/ 1: receive).
    LPC_I2C1->I2DAT = (((addr << 1) | 0x01)) & 0xFF; // Send slave address + RD direction bit = 1 
    LPC_I2C1->I2CONCLR = (1<<3); //I2C interrupt Clear bit
    while (!(LPC_I2C1->I2CONSET & (1<<3))); // 6. wait for complete sending
    if((LPC_I2C1->I2STAT & 0xF8) == 0x40) { // 7. SLA+R has been transmitted, ACK has been received
      //8. Receive length data bytes. If data length is only one, the master should not issue an ACK signal
      // on bus after reading to avoid of next data frame on slave side
      rx_count=rx_length;
      do {//Repeat steps 8-11 until all data have been received
         if (rx_count==1) LPC_I2C1->I2CONCLR = (1<<2); //Assert Not acknowledge flag at last Data Byte
         else                      LPC_I2C1->I2CONSET = (1<<2); //Assert acknowledge
         LPC_I2C1->I2CONCLR = (1<<3); //9.clear I2C interrupt bit
         while (!(LPC_I2C1->I2CONSET & (1<<3))); //wait for complete off receiving
         //Data has been received, ACK/ NACK has been return
         //10. Read the data byte from the read register I2DAT.
         *(rx_data+(rx_length-rx_count))=(uint8_t) (LPC_I2C1->I2DAT & 0xFF);
         //Verify data has been received by checking the code “0x50”. Check code “0x58” with the last
         //data byte. Only bits 7-3 in status register I2STAT should be evaluated. 
         if (((LPC_I2C1->I2STAT & 0xF8) != 0x50)&& (rx_count>1))  ret =ERROR;
         if (((LPC_I2C1->I2STAT & 0xF8) != 0x58)&& (rx_count==1)) ret =ERROR; rx_count--;
         } while ((rx_count>0)&&(ret!=ERROR));
      } else ret= ERROR; // SLA+R has not been transmitted, ACK has not been received
    } else ret= ERROR;  // wrong start condition
    // 12. Send STOP condition: Output the stop bit (ST0) and reset the SI bit.
    LPC_I2C1->I2CONSET = (1<<4); //Send Stop Bit
    LPC_I2C1->I2CONCLR = (1<<3); /**clear  I2C interrupt bit */
  } else ret=ERROR; //wrong parameters
  return ret;
} //end of I2C1Read()





