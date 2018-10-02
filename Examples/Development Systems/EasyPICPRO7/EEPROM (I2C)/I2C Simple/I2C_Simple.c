/*
 * Project name:
     I2C_Simple (Simple test of I2C library routines)
 * Copyright:
     (c) Mikroelektronika, 2012.
 * Revision History:
     20120116:
       - initial release (FJ);
 * Description:
     This program demonstrates usage of the I2C library routines. It
     establishes I2C bus communication with 24C02 EEPROM chip, writes one byte
     of data on some location, then reads it and displays it on PORTB.
 * Test configuration:
     MCU:             PIC18F87K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39960b.pdf
     Dev.Board:       EasyPIC PRO v7 - ac:Serial_EEPROM
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS-PLL 64.0000 MHz, 16.0000 MHz Crystal
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on I2C switches SW5.7 and SW5.8. (board specific)
     - Turn off PORTC LEDs (SW6.3). (board specific)
     - Turn on PORTB LEDs (SW6.2). (board specific)
 */

void main(){
  ANCON0 = 0;                // Configure PORTB pins as digital
  ANCON1 = 0;                // Configure PORTC pins as digital
  ANCON2 = 0;
  
  TRISB = 0;                 // Configure PORTB as output
  LATB = 0;                  // Clear PORTB

  I2C1_Init(100000);         // initialize I2C communication
  I2C2_Init(100000);
  Delay_ms(500);
//  TRISD5_bit = 0;
  while(1){
  I2C1_Start();              // issue I2C start signal
  I2C1_Wr(0xA2);             // send byte via I2C  (device address + W)
  I2C1_Wr(2);                // send byte (address of EEPROM location)
  I2C1_Wr(0xAA);             // send data (data to be written)
  I2C1_Stop();               // issue I2C stop signal

  Delay_100ms();

  I2C1_Start();              // issue I2C start signal
  I2C1_Wr(0xA2);             // send byte via I2C  (device address + W)
  I2C1_Wr(2);                // send byte (data address)
  I2C1_Repeated_Start();     // issue I2C signal repeated start
  I2C1_Wr(0xA3);             // send byte (device address + R)
  LATB = I2C1_Rd(0u);        // Read the data (NO acknowledge)
  I2C1_Stop();               // issue I2C stop signal
  Delay_ms(1000);

  I2C2_Start();              // issue I2C start signal
  I2C2_Wr(0xA2);             // send byte via I2C  (device address + W)
  I2C2_Wr(2);                // send byte (address of EEPROM location)
  I2C2_Wr(0x55);             // send data (data to be written)
  I2C2_Stop();               // issue I2C stop signal

  Delay_100ms();

  I2C2_Start();              // issue I2C start signal
  I2C2_Wr(0xA2);             // send byte via I2C  (device address + W)
  I2C2_Wr(2);                // send byte (data address)
  I2C2_Repeated_Start();     // issue I2C signal repeated start
  I2C2_Wr(0xA3);             // send byte (device address + R)
  LATB = I2C2_Rd(0u);        // Read the data (NO acknowledge)
  I2C2_Stop();               // issue I2C stop signal
  Delay_ms(1000);
  }
}