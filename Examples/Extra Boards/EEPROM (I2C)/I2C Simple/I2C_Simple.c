/*
 * Project name:
     I2C_Simple (Simple test of I2C library routines)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Description:
     This program demonstrates usage of the I2C library routines. It
     establishes I2C bus communication with 24C02 EEPROM chip, writes one byte
     of data on some location, then reads it and displays it on PORTB.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:Serial_EEPROM_Board (24C02)
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Connect EEPROM extra board on PORTC.
     - Pull-up I2C communication lines (RC3 and RC4) (PORTC three-state switch) (board specific)
     - Turn off PORTC LEDs (SW3.3). (board specific)
     - Turn on  PORTB LEDs (SW3.2). (board specific)
 */

void main(){
  ANSELB  = 0;               // Configure AN pins as digital I/O
  ANSELC = 0;
  LATB = 0;
  TRISB = 0;                 // Configure PORTB as output

  I2C1_Init(100000);         // initialize I2C communication
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
}