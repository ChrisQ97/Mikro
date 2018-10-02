/*
 * Project name:
     ADC_on LEDs (Display the result of ADC on LEDs)
 * Copyright:
     (c) Mikroelektronika, 2012.
 * Revision History:
     20120116:
       - initial release (FJ);
 * Description:
      A simple example of using the ADC library.
      ADC results are displayed on PORTC.
 * Test configuration:
     MCU:             PIC18F87K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39960b.pdf
     Dev.Board:       EasyPIC PRO v7 - ac:ADC
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS 16.0000 MHz, 16.0000 MHz Crystal
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on PORTC LEDs on SW6.3. (board specific)
     - To simulate analog input on ADC channel 0, use on-board potentiometer P2
       and place jumper J5 to MCU pin corresponding to ADC channel 0 input. (board specific)
 */

#include <built_in.h>

unsigned int adc_rd;

void main() {
  ANSEL0_bit = 1;            // Configure RA0 pin as analog
  TRISA0_bit = 1;            // Set RA0 pin as input
  TRISC = 0x00;              // Set PORTC as output

  while (1) {
    adc_rd = ADC_Read(0);    // Get 10-bit results of AD conversion
    LATC = adc_rd >> 4;      // display eight most signifficant bits
  }
}