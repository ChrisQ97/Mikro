/*
 * Project name:
     WatchDog_Timer (Demonstration of the Watchdog Timer usage)
 * Copyright:
     (c) MikroElektronika, 2005-2008
 * Description:
     This code demonstrates how to embed Assembly language blocks
     and how to clear the Watchdog timer.
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
     - Turn on Watchdog Timer in Edit Project window.
     - Turn on LEDs on PORTB switch SW3.2 (board specific).
*/

void main() {

  ANSELB = 0;        // Configure AN pins as digital
  asm CLRWDT;        // asm line, clear WatchDog Timer
  LATB  = 0x0F;      // Initialize PORTB
  TRISB = 0;         // Configure PORTB as output
  Delay_ms(300);     // Wait 0.3 seconds
  LATB  = 0xF0;      // Change PORTB value
  
  while (1)          // endless loop, WatchDog_Timer will reset PIC
    ;
}