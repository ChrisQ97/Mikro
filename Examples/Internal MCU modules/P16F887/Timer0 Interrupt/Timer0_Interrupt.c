/*
 * Project name:
     Timer0_Interrupt (Using Timer0 to obtain interrupts)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release;
 * Description:
     This code demonstrates how to use Timer0 and it's interrupt.
     Program toggles LEDs on PORTB.
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
     - Turn on LEDs on PORTB switch SW9.2 (board specific).
*/

unsigned cnt;

void interrupt() {
  if (TMR0IF_bit) {
    cnt++;                 // increment counter
    TMR0IF_bit = 0;        // clear TMR0IF
    TMR0   = 96;
  }
}

void main() {
  OPTION_REG = 0x84;       // Assign prescaler to TMR0
  ANSEL  = 0;              // Configure AN pins as digital
  ANSELH = 0;
  C1ON_bit = 0;            // Disable comparators
  C2ON_bit = 0;
  TRISB = 0;               // PORTB is output
  PORTB = 0xFF;            // Initialize PORTB
  TMR0  = 96;              // Timer0 initial value
  INTCON = 0xA0;           // Enable TMRO interrupt
  cnt = 0;                 // Initialize cnt

  do {
    if (cnt >= 400) {
      PORTB = ~PORTB;      // Toggle PORTB LEDs
      cnt = 0;             // Reset cnt
    }
  } while(1);
}