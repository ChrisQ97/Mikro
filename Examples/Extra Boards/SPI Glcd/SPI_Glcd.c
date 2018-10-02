/*
 * Project name:
     SPI_Glcd (Demonstration of using Spi_Glcd Library)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20080930:
       - initial release;
     20111012;
       - revision (JK);
 * Description:
     This is a simple demonstration of the serial Glcd library routines:
     - Init and Clear (pattern fill)
     - Image display
     - Drawing shapes
     - Writing text           
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:Serial_GLCD_128x64_Adapter_Board on PORTC, Glcd 128x64(KS108/107 controller)
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * Notes:
     None.
*/

const code char truck_bmp[1024];

// Port Expander module connections
sbit  SPExpanderRST at RC0_bit;
sbit  SPExpanderCS  at RC1_bit;
sbit  SPExpanderRST_Direction at TRISC0_bit;
sbit  SPExpanderCS_Direction  at TRISC1_bit;
// End Port Expander module connections

void Delay2s(){                         // 2 seconds delay function
  Delay_ms(2000);
}

void main() {

  unsigned short counter;
  char *someText;

  ANSELC = 0;                           // Configure AN pins as digital
  SLRCON = 0;                           // Set output slew rate on all ports at standard rate

  // If Port Expander Library uses SPI1 module
  SPI1_Init();                                         // Initialize SPI module used with PortExpander

  //  // If Port Expander Library uses SPI2 module
  //  SPI2_Init();                                     // Initialize SPI module used with PortExpander

  SPI_Glcd_Init(0);                                    // Initialize Glcd via SPI
  SPI_Glcd_Fill(0x00);                                 // Clear Glcd

  while(1) {
    SPI_Glcd_Image(truck_bmp);                         // Draw image
    Delay2s(); Delay2s();
    SPI_Glcd_fill(0x00);                               // Clear GLCD
    SPI_Glcd_PartialImage(0,0,68,30,128,64,truck_bmp); // Partial image
    Delay_ms(500);
    SPI_Glcd_PartialImage(24,16,68,30,128,64,truck_bmp);
    Delay_ms(500);
    SPI_Glcd_PartialImage(56,34,68,30,128,64,truck_bmp);
    Delay2s(); Delay2s();
    SPI_Glcd_Fill(0x00);                               // Clear GLCD

      SPI_Glcd_Box(62,40,124,56,1);                    // Draw box
      SPI_Glcd_Rectangle(5,5,84,35,1);                 // Draw rectangle
      Delay_ms(1000);
      SPI_Glcd_Rectangle_Round_Edges(2,2,87,38,7,1);
      Delay_ms(1000);
      SPI_Glcd_Line(0, 0, 127, 63, 1);                 // Draw line
      Delay2s();

      for(counter = 5; counter < 60; counter+=5 ){     // Draw horizontal and vertical lines
        Delay_ms(250);
        SPI_Glcd_V_Line(2, 54, counter, 1);
        SPI_Glcd_H_Line(2, 120, counter, 1);
      }
      Delay2s();

      SPI_Glcd_Fill(0x00);                             // Clear Glcd

      for (counter = 1; counter <= 10; counter++)      // Draw circles
        SPI_Glcd_Circle(63,32, 3*counter, 1);
      Delay2s();

      SPI_Glcd_Circle_Fill(63,32, 30, 1);              // Draw circles
      Delay2s();

      SPI_Glcd_Box(12,20, 70,57, 2);                   // Draw box
      Delay2s();

      SPI_Glcd_Fill(0xFF);                             // Fill Glcd

      SPI_Glcd_Set_Font(Character8x7, 8, 7, 32);       // Choose font, see __Lib_GLCDFonts.c in Uses folder
      SPI_Glcd_Write_Text("TEXT DEMO", 24, 3, 2);      // Write string
      Delay2s();
      SPI_Glcd_Fill(0x00);                             // Clear Glcd

      SPI_Glcd_Set_Font(Character8x7, 8, 7, 32);       // Change font
      someText = "8x7 Font";
      SPI_Glcd_Write_Text(someText, 5, 0, 2);          // Write string
      Delay2s();

      SPI_Glcd_Set_Font(System3x5, 3, 5, 32);          // Change font
      someText = "3X5 CAPITALS ONLY";
      SPI_Glcd_Write_Text(someText, 60, 2, 2);         // Write string
      Delay2s();

      SPI_Glcd_Set_Font(font5x7, 5, 7, 32);            // Change font
      someText = "5x7 Font";
      SPI_Glcd_Write_Text(someText, 5, 4, 2);          // Write string
      Delay2s();

      SPI_Glcd_Set_Font(FontSystem5x7_v2, 5, 7, 32);   // Change font
      someText = "5x7 Font (v2)";
      SPI_Glcd_Write_Text(someText, 50, 6, 2);         // Write string
      Delay2s();
  }
}