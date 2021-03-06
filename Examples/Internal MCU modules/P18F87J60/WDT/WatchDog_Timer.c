/*
 * Project name:
     WatchDog_Timer (Demonstration of the Watchdog Timer usage)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20081218:
       - initial release;
 * Description:
     This code demonstrates how to embed Assembly language blocks
     and how to use hardware controlled Watchdog timer.
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
     - Turn on Watchdog Timer and set WDT postscaler in Edit Project window.
     - Turn on LEDs on PORTB SW10.2. (board specific)
*/

void main() {
  ADCON1 |= 0x0F;    // Configure AN pins as digital
  CMCON  |= 7;       // Disable comparators
  
  asm CLRWDT;        // asm line, clear WatchDog Timer
  PORTB = 0x0F;      // Initialize PORTB
  TRISB = 0;         // Configure PORTB as output
  Delay_ms(300);     // Wait 0.3 seconds
  PORTB = 0xF0;      // Change PORTB value
  
  while (1)          // endless loop, WatchDog_Timer will reset MCU
    ;
}
