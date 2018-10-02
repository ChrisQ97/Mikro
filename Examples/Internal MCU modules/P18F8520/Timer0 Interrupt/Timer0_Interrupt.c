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

unsigned cnt;

void interrupt() {
  if (TMR0IF_bit) {
    cnt++;             // Increment value of cnt on every interrupt
    TMR0IF_bit = 0;    // clear TMR0IF
    TMR0L  = 96;
  }
}

void main() {
  ADCON1 |= 0x0F;      // Configure AN pins as digital
  CMCON  |= 7;         // Disable comparators
  
  T0CON  = 0xC4;       // Set TMR0 in 8bit mode, assign prescaler to TMR0
  TRISB  = 0;          // PORTB is output
  PORTB  = 0xFF;       // Initialize PORTB
  TMR0L  = 96;         // Timer0 initial value
  INTCON = 0xA0;       // Enable TMRO interrupt
  cnt = 0;             // Initialize cnt

  do {
    if (cnt >= 512) {
      PORTB = ~PORTB;  // Toggle PORTB LEDs
      cnt = 0;         // Reset cnt
    }
  } while(1);          // endless loop
}
