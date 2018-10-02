/*
 * Project name:
     WatchDog_Timer (Demonstration of the Watchdog Timer usage)
 * Copyright:
     (c) MikroElektronika, 2005-2008
 * Description:
     This code demonstrates how to embed Assembly language blocks
     and how to clear the Watchdog timer.
 * Test configuration:
     MCU:             PIC16F1937
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41364B.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on Watchdog Timer in Edit Project window.
     - Turn on LEDs on PORTB switch SW9.2 (board specific).
*/

void main() {

  ANSELA = 0;        // Configure AN pins as digital
  ANSELB = 0;
  ANSELD = 0;
  ANSELE = 0;
  
  C1ON_bit = 0;      // Disable comparators
  C2ON_bit = 0;
  OPTION_REG = 0x0E; // assing prescaler to the WDT, with 1:64 rate
  asm CLRWDT;        // asm line, clear WatchDog Timer
  PORTB = 0x0F;      // Initialize PORTB
  TRISB = 0;         // Configure PORTB as output
  Delay_ms(300);     // Wait 0.3 seconds
  PORTB = 0xF0;      // Change PORTB value
  
  while (1)          // endless loop, WatchDog_Timer will reset PIC
    ;
}