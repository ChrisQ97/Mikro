/*
 * Project name:
     LED_Curtain (Simple 'Hello World' project)
 * Copyright:
     (c) Mikroelektronika, 2011.
 * Revision History:
     20120116:
       - initial release (JK);
 * Description:
     This is a simple 'Hello World' project. It turns on/off LEDs connected to
     PORTA, PORTB, PORTC, PORTD and PORTE.
 * Test configuration:
     MCU:             PIC18F87K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39960b.pdf
     dev.board:       easypic pro v7 -   ac:LEDs
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS-PLL 64.0000 MHz, 16.0000 MHz Crystal
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn ON the PORT LEDs at SW6.
*/

char counter;

void wait() {
  Delay_ms(100);
}

void main() {

  TRISA = 0x00;                                 // set direction to be output
  TRISB = 0x00;                                 // set direction to be output
  TRISC = 0x00;                                 // set direction to be output
  TRISD = 0x00;                                 // set direction to be output
  TRISE = 0x00;                                 // set direction to be output
  TRISF = 0x00;                                 // set direction to be output
  TRISG = 0x00;                                 // set direction to be output
  TRISH = 0x00;                                 // set direction to be output
  TRISJ = 0x00;                                 // set direction to be output

  LATA = 0x00;                                  // turn OFF the LATA leds
  LATB = 0x00;                                  // turn OFF the LATB leds
  LATC = 0x00;                                  // turn OFF the LATC leds
  LATD = 0x00;                                  // turn OFF the LATD leds
  LATE = 0x00;                                  // turn OFF the LATE leds
  LATF = 0x00;                                  // turn OFF the LATF leds
  LATG = 0x00;                                  // turn OFF the LATG leds
  LATH = 0x00;                                  // turn OFF the LATH leds
  LATJ = 0x00;                                  // turn OFF the LATJ leds
  
  while (1) {
    for (counter=0; counter<4; counter++) {
      LATA |= 0x11 << counter;
      LATB |= 0x11 << counter;
      LATC |= 0x11 << counter;
      LATD |= 0x11 << counter;
      LATE |= 0x11 << counter;
      LATF |= 0x11 << counter;
      LATG |= 0x11 << counter;
      LATH |= 0x11 << counter;
      LATJ |= 0x11 << counter;
      wait();
    }
       
    counter = 0;
    while (counter<4) {
      LATA &= ~(0x11 << counter);
      LATB &= ~(0x11 << counter);
      LATC &= ~(0x11 << counter);
      LATD &= ~(0x11 << counter);
      LATE &= ~(0x11 << counter);
      LATF &= ~(0x11 << counter);
      LATG &= ~(0x11 << counter);
      LATH &= ~(0x11 << counter);
      LATJ &= ~(0x11 << counter);
      wait();
      counter++;
    }
  }
}