/*
 * Project name:
     Eeprom (Demonstration of using EEPROM Library) 
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release;
 * Description:
     This is a demonstration of using library functions for handling of the
     MCU's internal EEPROM module. First, some data is written to EEPROM
     in byte and block mode; then the data is read from the same locations and 
     displayed on PORTB, PORTC and PORTD.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     -  Turn on LEDs on PORTB, PORTC, PORTD switches (SW3.2, SW3.3, SW3.4)
*/

char ii;                                 // loop variable

void main(){
  ANSELB = 0;                            // Configure AN pins as digital I/O
  ANSELC = 0;
  ANSELD = 0;

  LATB = 0;
  LATC = 0;
  LATD = 0;

  TRISB = 0;
  TRISC = 0;
  TRISD = 0;
   
  for(ii = 0; ii < 32; ii++)             // Fill data buffer
    EEPROM_Write(0x80+ii, ii);           // Write data to address 0x80+ii

  EEPROM_Write(0x02,0xAA);               // Write some data at address 2
  EEPROM_Write(0x50,0x55);               // Write some data at address 0150

  Delay_ms(1000);                        // Blink PORTB and PORTC LEDs
  LATB = 0xFF;                          //   to indicate reading start
  LATC = 0xFF;
  Delay_ms(1000);
  LATB = 0x00;
  LATC = 0x00;
  Delay_ms(1000);

  LATB = EEPROM_Read(0x02);             // Read data from address 2 and display it on PORTB
  LATC = EEPROM_Read(0x50);             // Read data from address 0x50 and display it on PORTC

  Delay_ms(1000);

  for(ii = 0; ii < 32; ii++) {           // Read 32 bytes block from address 0x80
    LATD = EEPROM_Read(0x80+ii);        //   and display data on PORTD
    Delay_ms(250);
    }
}