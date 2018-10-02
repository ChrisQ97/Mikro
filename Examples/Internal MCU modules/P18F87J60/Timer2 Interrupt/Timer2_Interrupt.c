/*
 * Project name:
     Timer2_Interrupt (Using Timer2 to obtain interrupts)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20081218:
       - initial release;
 * Description:
     This code demonstrates how to use Timer2 and it's interrupt.
     Program toggles LEDs on PORTB.
 * Test configuration:
     MCU:             PIC18F87J60
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39762d.pdf
     Dev.Board:       EasyPIC PRO v7
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS, 25.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on LEDs on PORTB SW10.2. (board specific)
*/

unsigned cnt;

void interrupt() {
  if (TMR2IF_bit) {
    cnt++;             // Increment value of cnt on every interrupt
    TMR2IF_bit = 0;    // clear TMR2IF
  }
}

void main() {

  ADCON1 |= 0x0F;      // Configure AN pins as digital
  CMCON  |= 7;         // Disable comparators

  cnt = 0;             // Initialize cnt
  TRISB = 0;           // PORTB is output
  PORTB = 0xFF;        // Initialize PORTB

  T2CON = 0xFF;        // Timer2 settings
  INTCON = 0xC0;       // Set GIE, PEIE
  TMR2IE_bit = 1;      // Enable TMR2 interrupt

  do {
    if (cnt >= 90) {
      PORTB = ~PORTB;  // Toggle PORTB LEDs
      cnt = 0;         // Reset cnt
    }
  } while(1);          // endless loop
}
