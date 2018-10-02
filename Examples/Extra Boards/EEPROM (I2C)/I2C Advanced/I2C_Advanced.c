/*
 * Project name:
     I2C_Advanced (Advanced I2C Example)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20080930:
       - initial release;
     20111011;
       - revision (JK);
 * Description:
     This example features the advanced communication with the 24C02 EEPROM chip
     by introducing its own library of functions for this task: init, single
     write, single and sequential read. It performs write of a sequence of bytes
     (characters) into the EEPROM and writes this out at the first row on Lcd.
     Then, data read from EEPROM is performed and the result is displayed at the
     second row on Lcd.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:Serial_EEPROM_Board (24C02), Lcd 2x16
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Connect EEPROM extra board on PORTC and Lcd.
     - Pull-up I2C communication lines (RC3 and RC4) (PORTC three-state switch). (board specific)
     - Turn off PORTC LEDs (SW3.3). (board specific)
     - Turn on Lcd backlight on SW4.6 (board specific)
*/

#include "EEPROM_24C02.h"

// Lcd module connections
sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
// End Lcd module connections

char someData[] = "I2C mikroE";
char i ,tmpdata;

//  Main
void main() {

  EEPROM_24C02_Init();                      // performs I2C initialization
  TRISB = 0;
  LATB = 0xFF;
  TRISB = 0xFF;
  ANSELB = 0;                               // Configure AN pins as digital I/O
  ANSELC = 0;
  Lcd_Init();                               // performs Lcd initialization
  Lcd_Cmd(_LCD_CLEAR);                      // clear Lcd
  Lcd_Cmd(_LCD_CURSOR_OFF);                 // set cursor off

  // Example for single-byte write
  i = 0;
  tmpdata = 1;
  while ((tmpdata = someData[i]) != 0) {
    i++;
    EEPROM_24C02_WrSingle(i, tmpdata);      // writes data, char by char, in the EEPROM
    Delay_ms(20);
    Lcd_Chr(1,i, tmpdata);                  // diplays data on the first row of the Lcd
  }
  EEPROM_24C02_WrSingle(i+1, 0);            // writes string termination
  Delay_ms(20);

//   Example for single-byte read
//  i = 1;
//  tmpdata = 1;
//  while ((tmpdata = EEPROM_24C02_RdSingle(i)) != 0) {
//    Lcd_Chr(2,i, tmpdata);                  // displays data from EEPROM on the second row of the Lcd
//    Delay_ms(20);
//    i++ ;
//  }
  
//  Example for sequential data read
  Delay_ms(1000);
  Lcd_Cmd(_LCD_CLEAR);
  EEPROM_24C02_RdSeq(1, someData, 13);
  Lcd_Out(2,1,someData);
}