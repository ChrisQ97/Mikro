/*
 * Project name:
     Timer1_Interrupt (Using Timer1 to obtain interrupts)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release;
 * Description:
     This code demonstrates how to use Timer1 and it's interrupt.
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

unsigned short cnt;

void interrupt() {
  if (TMR1IF_bit) {
    cnt++;                 // increment counter
    TMR1IF_bit = 0;        // clear TMR0IF
  }
}

void main() {
  ADCON1 |= 0x0F;          // Configure AN pins as digital
  CMCON  |= 7;             // Disable comparators
  
                           // Initialize PORTB
  TRISB  = 0;              // PORTB is output
  T1CON  = 1;              // Timer1 settings
  TMR1IF_bit = 0;          // clear TMR1IF
  TMR1IE_bit = 1;          // enable Timer1 interrupt
  PORTB = 0xFF;            // Initialize PORTB
  cnt =   0;               // initialize cnt
  INTCON = 0xC0;           // Set GIE, PEIE

  do {
    if (cnt >= 40) {
      PORTB  = ~PORTB;     // toggle PORTB leds and
      cnt = 0;             // reset cnt
    }
  } while (1);
}
