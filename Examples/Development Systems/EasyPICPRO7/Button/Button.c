/*
 * Project name:
     Button (Demonstration of using Button Library)
 * Copyright:
     (c) Mikroelektronika, 2012.
 * Revision History:
     20120116:
       - initial release (FJ);
 * Description:
     This program demonstrates usage on-board button as PORTB input.
     On every RB0 one-to-zero transition PORTD is inverted.
 * Test configuration:
     MCU:             PIC18F87K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39960b.pdf
     Dev.Board:       EasyPIC PRO v7 - ac:Buttons
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS-PLL 64.0000 MHz, 16.0000 MHz Crystal
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn ON the PORTD LEDs at SW6.4. (board specific)
     - Put PB Button Level Switch into VCC position and pull-down PORTB. (board specific)
*/

bit oldstate;                                    // Old state flag

void main() {

  ANCON0 = 0;                                    // Configure PORTB pins as digital
  ANCON1 = 0;                                    // Configure PORTC pins as digital
  ANCON2 = 0;

  TRISB0_bit = 1;                                // set RB0 pin as input
  
  TRISD = 0x00;                                  // Configure PORTD as output
  LATD = 0xAA;                                   // Initial PORTD value
  
  oldstate = 0;
  
  do {
    if (Button(&PORTB, 0, 1, 1)) {               // Detect logical one
      oldstate = 1;                              // Update flag
    }
    if (oldstate && Button(&PORTB, 0, 1, 0)) {   // Detect one-to-zero transition
      LATD = ~LATD;                              // Invert PORTD
      oldstate = 0;                              // Update flag
    }
  } while(1);                                    // Endless loop
}