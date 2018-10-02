/*
 * Project name:
     Timer1_Interrupt (Using Timer1 to obtain interrupts)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20081218:
       - initial release;
 * Description:
     This code demonstrates how to use Timer1 and it's interrupt.
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
  if (TMR1IF_bit) {
    cnt++;             // Increment value of cnt on every interrupt
    TMR1IF_bit = 0;    // clear TMR1IF
  }
}

void main() {

  ADCON1 |= 0x0F;      // Configure AN pins as digital
  CMCON  |= 7;         // Disable comparators

  cnt = 0;             // Initialize cnt
  TRISB = 0;           // PORTB is output
  PORTB = 0xFF;        // Initialize PORTB

  T1CON = 1;           // Timer1 settings
  INTCON = 0xC0;       // Set GIE, PEIE
  TMR1IE_bit = 1;      // Enable TMR1 interrupt

  do {
    if (cnt >= 128) {
      PORTB = ~PORTB;  // Toggle PORTB LEDs
      cnt = 0;         // Reset cnt
    }
  } while(1);          // endless loop
}
