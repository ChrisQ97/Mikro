/*
 * Project name:
     Sprintf  
 * Copyright:
     (c) Mikroelektronika, 2007.
 * Revision History:
     20071210:
       - initial release;
 * Description:
     This is a demonstration of the standard C library sprintf routine usage.
     Three different representations of the same floating poing number obtained 
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

double ww = -1.2587538e+1;
char  buffer[15];

void main(){
  ANSELC = 0;

  UART1_Init(9600);                         // Initialize UART module at 4800 bps
  Delay_ms(10);
  
  UART1_Write_Text("\rFloating point number representation"); // Write message on UART

  sprintf(buffer, "%12e", ww);             // Format ww and store it to buffer
  UART1_Write_Text("\r\ne format:");       // Write message on UART
  UART1_Write_Text(buffer);                // Write buffer on UART

  sprintf(buffer, "%12f", ww);             // Format ww and store it to buffer
  UART1_Write_Text("\r\nf format:");       // Write message on UART
  UART1_Write_Text(buffer);                // Write buffer on UART
  
  sprintf(buffer, "%12g", ww);             // Format ww and store it to buffer
  UART1_Write_Text("\r\ng format:");       // Write message on UART
  UART1_Write_Text(buffer);                // Write buffer on UART
}