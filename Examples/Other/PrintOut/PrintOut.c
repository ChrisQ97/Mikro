/*
 * Project name:
     PrintOutExample (Sample usage of PrintOut() function)
 * Copyright:
     (c) MikroElektronika, 2006.
 * Revision History:
     20060710:
       - Initial release
 * Description:
     Simple demonstration on usage of the PrintOut() function
 * Test configuration:
     MCU:             PIC18F4520
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39631E.pdf
     Oscillator:      HS, 8.0000 MHz
     Ext. Modules:    None
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     None.
 */

void PrintHandler(char c) {
  UART1_Write(c);
}

void main() {
  UART1_Init(9600);
  Delay_ms(100);

  PrintOut(PrintHandler, "/*\r\n"
                         " * Project name:\r\n"
                         "     PrintOutExample (Sample usage of PrintOut() function)\r\n"
                         " * Copyright:\r\n"
                         "     (c) MikroElektronika, 2006.\r\n"
                         " * Revision History:\r\n"
                         "     20060710:\r\n"
                         "       - Initial release\r\n"
                         " * Description:\r\n"
                         "     Simple demonstration on usage of the PrintOut() function\r\n"
                         " * Test configuration:\r\n"
                         "     MCU:             PIC18F4520\r\n"
                         "     Dev.Board:       EasyPIC7\r\n"
                         "     Oscillator:      HS, %6.3fMHz\r\n"
                         "     Ext. Modules:    None.\r\n"
                         "     SW:              mikroC PRO for PIC\r\n"
                         " * NOTES:\r\n"
                         "     None.\r\n"
                         " */\r\n", Get_Fosc_kHz()/1000.);

}