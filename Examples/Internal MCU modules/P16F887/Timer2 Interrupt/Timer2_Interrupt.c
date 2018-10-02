/*
 * Project name:
     Timer2_Interrupt (Using Timer2 to obtain interrupts)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release;
 * Description:
     This code demonstrates how to use Timer2 and it's interrupt.
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

unsigned short cnt;

void interrupt() {
  if (TMR2IF_bit) {
    cnt++;                    // increment counter
    TMR2IF_bit = 0;           // clear TMR2IF
    TMR2 = 0;
  }
}

// main
void main() {
  cnt = 0;                    // initialize cnt
  ANSEL  = 0;                 // Configure AN pins as digital
  ANSELH = 0;
  C1ON_bit = 0;               // Disable comparators
  C2ON_bit = 0;
  PORTB = 0xFF;               // Initialize PORTB
  TRISB =   0;                // PORTB is output
  T2CON = 0xFF;               // Timer2 settings
  TMR2  =   0;                // Initialize Timer2 register
  TMR2IE_bit = 1;             // enable interupt
  INTCON = 0xC0;              // Set GIE, PEIE

  while (1) {                 // endless loop
    if (cnt >= 32) {
      PORTB = ~PORTB;         // Toggle PORTB LEDs
      cnt = 0;                // Reset cnt
    }
  }
}