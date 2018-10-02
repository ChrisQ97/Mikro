/*
 * Project name:
     Sprintl
 * Copyright:
     (c) Mikroelektronika, 2007.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a demonstration of the standard C library sprinti routine usage.
     Two different representations of the same long integer number obtained
     by using the sprintf routine are sent via UART.
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
     - RX  and TX  UART switches(SW1.1, SW2.1) on EasyPIC7 should be turned On.
 */

unsigned long long_no = 1000000;
char  buffer[15];

void main(){

  UART1_Init(9600);                                  // Initialize UART module at 9600 bps
  Delay_ms(10);

  UART1_Write_Text("\rInteger number representation"); // Write message on UART

  sprintl(buffer, "%10ld", long_no);                 // Format long_no and store it to buffer
  UART1_Write_Text("\r\nd format:");                 // Write message on UART
  UART1_Write_Text(buffer);                          // Write buffer on UART (decimal format)

  sprintl(buffer, "%10lx", long_no);                 // Format long_no and store it to buffer
  UART1_Write_Text("\r\nx format:");                 // Write message on UART
  UART1_Write_Text(buffer);                          // Write buffer on UART (hex format)
}