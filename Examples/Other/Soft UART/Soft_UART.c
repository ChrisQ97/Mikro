/*
 * Project name:
     Soft_UART (Demonstration of using Soft UART library routines) 
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20081218:
       - initial release;
 * Description:
     This code demonstrates how to use software UART library routines.
     Upon receiving data via RS232, MCU immediately sends it back to the sender.
     Bear in mind that this is a half-duplex data transfer which means that data 
     byte is sent before next data byte is received.
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
     - RX and TX UART switches on EasyPIC7 should be turned On SW1.1 SW1.1.
*/

char i, error, byte_read;                 // Auxiliary variables

void main(){

  ANSELC = 0;                             // Configure AN pins as digital I/O

  TRISB = 0x00;                           // Set PORTB as output (error signalization)
  LATB  = 0;                              // No error

  error = Soft_UART_Init(&PORTC, 7, 6, 9600, 0); // Initialize Soft UART at 14400 bps
  if (error > 0) {
    LATB = error;                         // Signalize Init error
    while(1) ;                            // Stop program
  }
  Delay_ms(100);

  for (i = 'z'; i >= 'A'; i--) {          // Send bytes from 'z' downto 'A'
    Soft_UART_Write(i);
    Delay_ms(100);
  }
   
  while(1) {                              // Endless loop
    byte_read = Soft_UART_Read(&error);   // Read byte, then test error flag
    if (error)                            // If error was detected
      LATB = error;                       //   signal it on PORTB
    else
      Soft_UART_Write(byte_read);         // If error was not detected, return byte read
    }      
}