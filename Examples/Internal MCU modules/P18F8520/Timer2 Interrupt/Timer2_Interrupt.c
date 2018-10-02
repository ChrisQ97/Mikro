/*
 * Project name:
     Timer2_Interrupt (Using Timer1 to obtain interrupts)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release;
 * Description:
     This code demonstrates how to use Timer2 and it's interrupt.
     Program toggles LEDs on PORTB.
 * Test configuration:
     MCU:             P18F8520
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39609b.pdf
     Dev.Board:       EasyPIC PRO v7
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS, 10.0 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on LEDs on PORTB switches SW10.2 (board specific)
*/

unsigned int cnt;

void interrupt() {
  if (TMR2IF_bit) {
    cnt++;                 // increment counter
    TMR2IF_bit = 0;        // clear TMR2IF
  }
}

void main() {
  ADCON1 |= 0x0F;          // Configure AN pins as digital
  CMCON  |= 7;             // Disable comparators
                           // Initialize PORTB
  TRISB  = 0;              // PORTB is output
  T2CON  = 0x07;           // Timer2 settings
  TMR2IF_bit = 0;          // clear TMR2IF
  TMR2IE_bit = 1;          // enable Timer2 interrupt
  PORTB = 0xFF;            // Initialize PORTB
  cnt =   0;               // initialize cnt
  INTCON = 0xC0;           // Set GIE, PEIE

  do {
    if (cnt >= 512) {
      PORTB  = ~PORTB;     // toggle PORTB LEDs and
      cnt = 0;             // reset cnt
    }
  } while (1);
}
