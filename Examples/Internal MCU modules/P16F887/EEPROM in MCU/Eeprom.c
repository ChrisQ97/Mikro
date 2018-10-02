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
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     -  Turn on LEDs on PORTB, PORTC, PORTD switches (SW9.2, SW9.3, SW9.4)
*/

char ii;                                 // loop variable

void main(){
  ANSEL =  0;                            // Configure AN pins as digital I/O
  ANSELH = 0;
  C1ON_bit = 0;                          // Disable comparators
  C2ON_bit = 0;

  PORTB = 0;
  PORTC = 0;
  PORTD = 0;

  TRISB = 0;
  TRISC = 0;
  TRISD = 0;
   
  for(ii = 0; ii < 32; ii++)             // Fill data buffer
    EEPROM_Write(0x80+ii, ii);           // Write data to address 0x80+ii

  EEPROM_Write(0x02,0xAA);               // Write some data at address 2
  EEPROM_Write(0x50,0x55);               // Write some data at address 0150

  Delay_ms(1000);                        // Blink PORTB and PORTC LEDs
  PORTB = 0xFF;                          //   to indicate reading start
  PORTC = 0xFF;
  Delay_ms(1000);
  PORTB = 0x00;
  PORTC = 0x00;
  Delay_ms(1000);

  PORTB = EEPROM_Read(0x02);             // Read data from address 2 and display it on PORTB
  PORTC = EEPROM_Read(0x50);             // Read data from address 0x50 and display it on PORTC

  Delay_ms(1000);

  for(ii = 0; ii < 32; ii++) {           // Read 32 bytes block from address 0x80
    PORTD = EEPROM_Read(0x80+ii);        //   and display data on PORTD
    Delay_ms(250);
    }
}