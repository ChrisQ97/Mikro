/*
 * Project name:
     ManchesterTransmitter (Demonstration of usage of Manchester code library functions)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release;
 * Description:
     This code shows how to use Manchester Library for sending data. The
     example works in conjuction with Receiver example. This node sends the
     word "mikroElektronika" using Manchester encoding.
 * Test configuration:
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    Superhet transmitter on some household-use frequency
                      (e.g. 433MHz) - OPTIONAL
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - If you decide to try this example(s) with transmitter/receiver modules,
       make sure that both transmitter and a receiver work on the same frequency!
 */

// Manchester module connections
sbit MANRXPIN at RC0_bit;
sbit MANRXPIN_Direction at TRISC0_bit;
sbit MANTXPIN at RC1_bit;
sbit MANTXPIN_Direction at TRISC1_bit;
// End Manchester module connections

char index, character;
char s1[] = "mikroElektronika";

void main() {

  ANSEL  = 0;                      // Configure AN pins as digital I/O
  ANSELH = 0;
  C1ON_bit = 0;                    // Disable comparators
  C2ON_bit = 0;

  Man_Send_Init();                 // Initialize transmitter

  while (1) {                      // Endless loop
    Man_Send(0x0B);                // Send "start" byte
    Delay_ms(100);                 // Wait for a while

    character = s1[0];             // Take first char from string
    index = 0;                     // Initialize index variable  
    while (character) {            // String ends with zero
      Man_Send(character);         // Send character
      Delay_ms(90);                // Wait for a while 
      index++;                     // Increment index variable
      character = s1[index];       // Take next char from string 
      }
    Man_Send(0x0E);                // Send "end" byte
    Delay_ms(1000);
  }
}