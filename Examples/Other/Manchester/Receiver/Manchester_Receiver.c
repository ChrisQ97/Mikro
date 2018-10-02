/*
 * Project name:
     ManchesterReceiver (Demonstration of usage of Manchester code library functions)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release;
 * Description:
     This code shows how to use Manchester Library for receiving data. The
     example works in conjuction with Transmitter example which sends the word
     "mikroElektronika" using Manchester encoding. During the receive process,
     message letters are being written on the LCD.
 * Test configuration:
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    LCD 2x16 
                      http://www.mikroe.com/store/components/
                      Superhet receiver on some household-use frequency
                      (e.g. 433MHz) - OPTIONAL
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - If you decide to try this example(s) with transmitter/receiver modules,
       make sure that both transmitter and a receiver work on the same frequency.
     - Turn on LCD backlight switch SW4.6 (board specific)
 */

// LCD module connections
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
// End LCD module connections


// Manchester module connections
sbit MANRXPIN at RC0_bit;
sbit MANRXPIN_Direction at TRISC0_bit;
sbit MANTXPIN at RC1_bit;
sbit MANTXPIN_Direction at TRISC1_bit;
// End Manchester module connections

char error, ErrorCount, temp;

void main() {
  ErrorCount = 0;
  ANSEL  = 0;                                     // Configure AN pins as digital I/O
  ANSELH = 0;
  C1ON_bit = 0;                                   // Disable comparators
  C2ON_bit = 0;
  TRISC.F5 = 0;
  Lcd_Init();                                     // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);                            // Clear LCD display

  Man_Receive_Init();                             // Initialize Receiver
  
  while (1) {                                     // Endless loop

      Lcd_Cmd(_LCD_FIRST_ROW);                    // Move cursor to the 1st row
       
      while (1) {                                 // Wait for the "start" byte
        temp = Man_Receive(&error);               // Attempt byte receive 
        if (temp == 0x0B)                         // "Start" byte, see Transmitter example
          break;                                  // We got the starting sequence
        if (error)                                // Exit so we do not loop forever
          break;
        }
        
      do
        {
          temp = Man_Receive(&error);             // Attempt byte receive
          if (error) {                            // If error occured
            Lcd_Chr_CP('?');                      // Write question mark on LCD
            ErrorCount++;                         // Update error counter
            if (ErrorCount > 20) {                // In case of multiple errors
              temp = Man_Synchro();               // Try to synchronize again
              //Man_Receive_Init();               // Alternative, try to Initialize Receiver again
              ErrorCount = 0;                     // Reset error counter
              }
            }
          else {                                  // No error occured
            if (temp != 0x0E)                     // If "End" byte was received(see Transmitter example)
              Lcd_Chr_CP(temp);                   //   do not write received byte on LCD
              }
          Delay_ms(25);
        }
      while (temp != 0x0E) ;                      // If "End" byte was received exit do loop
   }
}