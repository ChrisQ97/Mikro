/*
 * Project name:
     UART (Simple usage of UART module library functions)
 * Copyright:
     (c) Mikroelektronika, 2011.
 * Revision History:
     20120116:
       - initial release (JK);
 * Description:
     This code demonstrates how to use uart library routines. Upon receiving
     data via RS232, MCU immediately sends it back to the sender.
 * Test configuration:
     MCU:             PIC18F87K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39960b.pdf
     dev.board:       easypic pro v7   ac:UART
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS-PLL 64.0000 MHz, 16.0000 MHz Crystal
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on RX and TX UART switches (SW5.3 and SW5.4).
 */

char uart_rd;

void main() {
  ANCON0 = 0x00;                  // Configure PORTC pins as digital
  ANCON1 = 0x00;                  // Configure PORTC pins as digital
  ANCON2 = 0x00;                  // Configure PORTC pins as digital

  UART2_Init(9600);               // Initialize UART module at 9600 bps
  Delay_ms(100);                  // Wait for UART module to stabilize

  UART2_Write_Text("Start");
  UART2_Write(13);
  UART2_Write(10);

  while (1) {                     // Endless loop
    if (UART2_Data_Ready()) {     // If data is received,
      uart_rd = UART2_Read();     // read the received data,
      UART2_Write(uart_rd);       // and send data via UART
    }
  }
}