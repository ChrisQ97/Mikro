/*
 * Project Name:
     SPI_T6963C_240x64 (SPI_Glcd Library demo for Toshiba's T6963 Controller)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20080930:
       - initial release; Credits to Bruno Gavand.
     20111013;
       - revision (JK);
 * Description:
     This code in intended to work with GLCD's based on TOSHIBA T6963C controller
     through SPI interface. Pressing buttons RB0 .. RB5 generates commands for text and graphic displaying.
     This parts may need a -15V power supply on Vee for LCD drive,
     a simple DC/DC converter can be made with a 2N2905, 220 µH self, diode & 47 µF cap,
     transistor base is driven with PWM thrue a current limiting resistor.
     This parts have a 8 Kb built-in display RAM, this allows 2 graphics panels
     and one text panel.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:Serial_GLCD_240x64_Adapter_Board on PORTC,
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Put button jumper (J17) into Vcc position and pull-down PORTB (PortB three-state switch).
 */

#include        "__SPIT6963C.h"

// Port Expander module connections
sbit  SPExpanderRST at LATC0_bit;
sbit  SPExpanderCS  at LATC1_bit;
sbit  SPExpanderRST_Direction at TRISC0_bit;
sbit  SPExpanderCS_Direction  at TRISC1_bit;
// End Port Expander module connections

/*
 * bitmap pictures stored in ROM
 */
const code char mikroE_240x64_bmp[];
const code char einstein[];

void main() {

  char txt1[] = " EINSTEIN WOULD HAVE LIKED mE";
  char txt[] =  " GLCD LIBRARY DEMO, WELCOME !";
  char txt2[] = "Partial image demo!";

  unsigned char  panel;         // Current panel
  unsigned int   i;             // General purpose register
  unsigned char  curs;          // Cursor visibility
  unsigned int   cposx, cposy;  // Cursor x-y position
  unsigned short s;             // counter

  ANSELB = 0;
  ANSELC = 0;                   // Configure AN pins as digital I/O
  SLRCON = 0;                   // Set output slew rate on all ports at standard rate

  TRISB0_bit = 1;               // Set RB0 as input
  TRISB1_bit = 1;               // Set RB1 as input
  TRISB2_bit = 1;               // Set RB2 as input
  TRISB3_bit = 1;               // Set RB3 as input
  TRISB4_bit = 1;               // Set RB4 as input
  TRISB5_bit = 1;               // Set RB5 as input

  // If Port Expander Library uses SPI1 module
  SPI1_Init();                                   // Initialize SPI module used with PortExpander

  //  // If Port Expander Library uses SPI2 module
  //  SPI2_Init();                                   // Initialize SPI module used with PortExpander

   /*
   * init display for 240 pixel width and 64 pixel height
   * 8 bits character width
   * data bus on MCP23S17 portB
   * control bus on MCP23S17 portA
   * bit 0 is !WR
   * bit 1 is !RD
   * bit 3 is !CD
   * bit 4 is RST
   * chip enable, reverse on, 8x8 font internaly set in library
   */

  SPI_T6963C_Config(240, 64, 8, 0, 0, 1, 3, 4);
  Delay_ms(1000);

  /*
   * Enable both graphics and text display at the same time
   */
  SPI_T6963C_graphics(1);
  SPI_T6963C_text(1);

  panel = 0;
  i = 0;
  curs = 0;
  cposx = cposy = 0;

  /*
  * Text messages
  */
  SPI_T6963C_write_text(txt, 0, 0, SPI_T6963C_ROM_MODE_XOR);
  SPI_T6963C_write_text(txt1, 0, 7, SPI_T6963C_ROM_MODE_XOR);
  
  /*
  * Cursor
  */
  SPI_T6963C_cursor_height(8);       // 8 pixel height
  SPI_T6963C_set_cursor(0, 0);       // Move cursor to top left
  SPI_T6963C_cursor(0);              // Cursor off

  /*
  * Draw solid boxes
  */
  SPI_T6963C_box(0, 0, 239, 8, SPI_T6963C_WHITE);
  SPI_T6963C_box(0, 55, 239, 63, SPI_T6963C_WHITE);
  
  /*
   * Draw rectangles
   */

    SPI_T6963C_rectangle(0, 0, 239, 63, SPI_T6963C_WHITE);
    SPI_T6963C_rectangle(20, 11, 219, 53, SPI_T6963C_WHITE);
    SPI_T6963C_rectangle(40, 21, 199, 43, SPI_T6963C_WHITE);
    SPI_T6963C_rectangle(60, 30, 179, 34, SPI_T6963C_WHITE);

  /*
   * Draw rounded edge rectangle
   */

    SPI_T6963C_Rectangle_Round_Edges(30,16, 209, 48, 12, SPI_T6963C_WHITE);
    SPI_T6963C_Rectangle_Round_Edges(50,25, 189, 39, 5, SPI_T6963C_WHITE);

  /*
   * Draw filled rounded edge rectangle
   */

    SPI_T6963C_Rectangle_Round_Edges_Fill(10, 10, 229, 53, 12, SPI_T6963C_WHITE);
    SPI_T6963C_Rectangle_Round_Edges_Fill(15, 15, 224, 49, 12, SPI_T6963C_BLACK);
    SPI_T6963C_Rectangle_Round_Edges_Fill(20, 20, 219, 44, 9, SPI_T6963C_WHITE);
    SPI_T6963C_Rectangle_Round_Edges_Fill(25, 25, 214, 39, 7, SPI_T6963C_BLACK);
    SPI_T6963C_Rectangle_Round_Edges_Fill(30, 30, 209, 34, 2, SPI_T6963C_WHITE);
  
  /*
   * Draw a cross
   */

    SPI_T6963C_line(0, 0, 239, 63, SPI_T6963C_WHITE);
    SPI_T6963C_line(0, 63, 239, 0, SPI_T6963C_WHITE);

  /*
   * Draw circles
   */

    SPI_T6963C_circle(120, 32, 10, SPI_T6963C_WHITE);
    SPI_T6963C_circle(120, 32, 30, SPI_T6963C_WHITE);
    SPI_T6963C_circle(120, 32, 50, SPI_T6963C_WHITE);
    SPI_T6963C_circle(120, 32, 70, SPI_T6963C_WHITE);
    SPI_T6963C_circle(120, 32, 90, SPI_T6963C_WHITE);
    SPI_T6963C_circle(120, 32, 110, SPI_T6963C_WHITE);
    SPI_T6963C_circle(120, 32, 130, SPI_T6963C_WHITE);


  /*
   * Draw filled circles
   */

    SPI_T6963C_circle_fill(120, 32, 40, SPI_T6963C_WHITE);
    SPI_T6963C_circle_fill(120, 32, 35, SPI_T6963C_BLACK);
    SPI_T6963C_circle_fill(120, 32, 30, SPI_T6963C_WHITE);
    SPI_T6963C_circle_fill(120, 32, 25, SPI_T6963C_BLACK);
    SPI_T6963C_circle_fill(120, 32, 20, SPI_T6963C_WHITE);
    SPI_T6963C_circle_fill(120, 32, 15, SPI_T6963C_BLACK);
    SPI_T6963C_circle_fill(120, 32, 10, SPI_T6963C_WHITE);
    SPI_T6963C_circle_fill(120, 32, 5, SPI_T6963C_BLACK);


  Delay_ms(1000);
  SPI_T6963C_sprite(60, 0, einstein, 120, 64);  // Draw a sprite
  Delay_ms(1000);

  SPI_T6963C_setGrPanel(1);                     // Select other graphic panel
  SPI_T6963C_image(mikroE_240x64_bmp);

  SPI_T6963C_displayGrPanel(1);
  Delay_ms(1000);

    SPI_T6963C_grFill(0);
    SPI_T6963C_PartialImage(0, 0, 64, 64, 240, 64, mikroE_240x64_bmp);   // Display partial image
    Delay_ms(1000);
    SPI_T6963C_graphics(0);
    SPI_T6963C_image(mikroE_240x64_bmp);

  SPI_T6963C_graphics(1);
  SPI_T6963C_displayGrPanel(0);
  
  for(;;) {                                       // Endless loop
    
    /*
     * If RB0 is pressed, display only graphic panel
     */
    if(RB0_bit) {
      SPI_T6963C_graphics(1);
      SPI_T6963C_text(0);
      Delay_ms(300);
      }
    
    /*
     * If RB1 is pressed, toggle the display between graphic panel 0 and graphic panel 1
     */
    else if(RB1_bit) {
      panel++;
      panel &= 1;
      SPI_T6963C_displayGrPanel(panel);
      Delay_ms(300);
    }
    
    /*
     * If RB2 is pressed, display only text panel
     */
    else if(RB2_bit) {
      SPI_T6963C_graphics(0);
      SPI_T6963C_text(1);
      Delay_ms(300);
    }

    /*
     * If RB3 is pressed, display text and graphic panels
     */
    else if(RB3_bit) {
      SPI_T6963C_graphics(1);
      SPI_T6963C_text(1);
      Delay_ms(300);
    }

    /*
     * If RB4 is pressed, change cursor
     */
    else if(RB4_bit) {
      curs++;
      if(curs == 3) curs = 0;
      switch(curs) {
        case 0:
          // no cursor
          SPI_T6963C_cursor(0);
          break;
        case 1:
          // blinking cursor
          SPI_T6963C_cursor(1);
          SPI_T6963C_cursor_blink(1);
          break;
        case 2:
          // non blinking cursor
          SPI_T6963C_cursor(1);
          SPI_T6963C_cursor_blink(0);
          break;
        }
      Delay_ms(300);
      }

    /*
     * If RB5 is pressed, perform the "Partial image" demostration
     */
    else if(RB5_bit) {
      SPI_T6963C_setGrPanel(0);
      SPI_T6963C_setTxtPanel(0);
      SPI_T6963C_txtFill(0);
      SPI_T6963C_setGrPanel(1);
      SPI_T6963C_setTxtPanel(0);
      SPI_T6963C_graphics(1);
      SPI_T6963C_text(1);
      SPI_T6963C_displayGrPanel(1);
      SPI_T6963C_write_text(txt2, 5, 7, SPI_T6963C_ROM_MODE_XOR);
      Delay_1sec();

      for(s = 0; s < 3; s++){
        SPI_T6963C_grFill(0);
        SPI_T6963C_PartialImage(s*80 + 10, 0, 64, 64, 240, 64, mikroE_240x64_bmp); // Partial image
        Delay_ms(500);
      }

      SPI_T6963C_txtFill(0);
      //SPI_T6963C_image(mikroE_240x64_bmp);
      SPI_T6963C_write_text(txt, 0, 0, SPI_T6963C_ROM_MODE_XOR);
      SPI_T6963C_write_text(txt1, 0, 7, SPI_T6963C_ROM_MODE_XOR);
    }
    
    /*
     * Move cursor, even if not visible
     */
    cposx++;
    if(cposx == SPI_T6963C_txtCols) {
      cposx = 0;
      cposy++;
      if(cposy == SPI_T6963C_grHeight / SPI_T6963C_CHARACTER_HEIGHT) {
        cposy = 0;
        }
      }
    SPI_T6963C_set_cursor(cposx, cposy);

    Delay_ms(100);

    }
}