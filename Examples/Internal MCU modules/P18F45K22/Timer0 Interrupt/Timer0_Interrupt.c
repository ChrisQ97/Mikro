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
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on LEDs on PORTB switch SW3.2 (board specific).
*/

unsigned cnt;

void interrupt() {
  if (TMR0IF_bit) {
    cnt++;                 // increment counter
    TMR0IF_bit = 0;        // clear TMR0IF
    TMR0L = 0;             // set TMR0 for aproximetly 1 sec
  }
}

void main() {
  ANSELB = 0;              // Configure AN pins as digital
  TRISB  = 0;              // PORTB is output
  LATB = 0xFF;             // Initialize PORTB

  TMR0L = 0;               // Timer0 initial value
  T0CON = 0xC7;            // Set TMR0 to 8bit mode and prescaler to 256
  GIE_bit = 1;             // Enable global interrupt
  TMR0IE_bit = 1;          // Enable Timer0 interrupt
  cnt = 0;                 // Initialize cnt

  do {
    if (cnt >= 122) {
      LATB = ~PORTB;      // Toggle PORTB LEDs
      cnt = 0;             // Reset cnt
    }
  } while(1);
}