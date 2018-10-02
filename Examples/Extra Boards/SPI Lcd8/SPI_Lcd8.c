/*
 * Project name:
     Spi_Lcd8_Test (How to use SPI Lcd 8-bit interface library)
 * Copyright:
     (c) MikroElektronika, 2005-2010
 * Revision History:
     20071210:
       - initial release;
     20111013;
       - revision (JK);
 * Description:
     The code prints text on Lcd (8-bit interface) via SPI interface
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:Serial_LCD_2x16_Adapter_Board , Lcd 2x16
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     None.
 */

char *text = "mikroElektronika";

// Port Expander module connections
sbit  SPExpanderRST at LATC0_bit;
sbit  SPExpanderCS  at LATC1_bit;
sbit  SPExpanderRST_Direction at TRISC0_bit;
sbit  SPExpanderCS_Direction  at TRISC1_bit;
// End Port Expander module connections

void main() {

  ANSELC = 0;                             // Configure AN pins as digital
  SLRCON = 0;                             // Set output slew rate on all ports at standard rate

  // If Port Expander Library uses SPI1 module
  SPI1_Init();                                   // Initialize SPI module used with PortExpander

//  // If Port Expander Library uses SPI2 module
//  SPI2_Init();                                   // Initialize SPI module used with PortExpander

  SPI_Lcd8_Config(0);                     // Initialize Lcd over SPI interface
  SPI_Lcd8_Cmd(_LCD_CLEAR);               // Clear display
  SPI_Lcd8_Cmd(_LCD_CURSOR_OFF);          // Turn cursor off
  SPI_Lcd8_Out(1,6, "mikroE");            // Print text to Lcd, 1st row, 6th column
  SPI_Lcd8_Chr_CP('!');                   // Append '!'
  SPI_Lcd8_Out(2,1, text);                // Print text to Lcd, 2nd row, 1st column

  // SPI_Lcd8_Out(3,1,"mikroE");          // For Lcd with more than two rows
  // SPI_Lcd8_Out(4,15,"mikroE");         // For Lcd with more than two rows
}