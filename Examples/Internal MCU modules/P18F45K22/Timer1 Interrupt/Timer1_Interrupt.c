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

unsigned short cnt;

void interrupt() {
  if (TMR1IF_bit) {
    cnt++;                    // increment counter
    TMR1IF_bit = 0;           // clear TMR0IF
    TMR1H = 0x80;
    TMR1L = 0x00;
  }
}

void main() {
  ANSELB = 0;                 // Configure AN pins as digital

  LATB  = 0xFF;               // Initialize PORTB
  TRISB = 0;                  // PORTB is output
  T1CON = 0x21;               // Timer1 settings
  TMR1IF_bit = 0;             // clear TMR1IF
  TMR1H = 0x80;               // Initialize Timer1 register
  TMR1L = 0x00;
  TMR1IE_bit = 1;             // enable Timer1 interrupt

  cnt =   0;                  // initialize cnt
  INTCON = 0xC0;              // Set GIE, PEIE

  do {
    if (cnt >= 72) {
      LATB  = ~PORTB;        // Toggle PORTB LEDs
      cnt = 0;                // Reset cnt
    }
  } while (1);
}