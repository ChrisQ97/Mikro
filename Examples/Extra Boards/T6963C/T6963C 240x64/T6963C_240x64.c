/*
 * Project Name:
     T6963C_240x64 (GLCD Library demo for Toshiba's T6963 Controller)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20080930:
       - initial release; Credits to Bruno Gavand.
 * Description:
     This code in intended to work with GLCD's based on TOSHIBA T6963C controller
     Pressing buttons RB0 .. RB4 generates commands for text and graphic displaying.
     This parts may need a -15V power supply on Vee for LCD drive,
     a simple DC/DC converter can be made with a 2N2905, 220 µH self, diode & 47 µF cap,
     transistor base is driven with PWM thrue a current limiting resistor.
     This parts have a 8 Kb built-in display RAM, this allows 2 graphics panels
     and one text panel.
 * Test configuration:
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    ac:GLCD_240x64_Adapter_Board on PORTC(Control) and PORTD(Data),
                      T6963C display 240x64 pixels
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Put button jumper (J17) into Vcc position and pull-down PORTB.
 */

#include        "__T6963C.h"
                            
// T6963C module connections
char T6963C_dataPort at PORTD;                   // DATA port

sbit T6963C_ctrlwr  at LATC0_bit;                  // WR write signal
sbit T6963C_ctrlrd  at LATC1_bit;                  // RD read signal
sbit T6963C_ctrlcd  at LATC3_bit;                  // CD command/data signal
sbit T6963C_ctrlrst at LATC4_bit;                  // RST reset signal
sbit T6963C_ctrlwr_Direction  at TRISC0_bit;     // WR write signal
sbit T6963C_ctrlrd_Direction  at TRISC1_bit;     // RD read signal
sbit T6963C_ctrlcd_Direction  at TRISC3_bit;     // CD command/data signal
sbit T6963C_ctrlrst_Direction at TRISC4_bit;     // RST reset signal

// Signals not used by library, they are set in main function
sbit T6963C_ctrlce at LATC2_bit;                   // CE signal
sbit T6963C_ctrlfs at LATC5_bit;                   // FS signal
sbit T6963C_ctrlce_Direction  at TRISC2_bit;     // CE signal direction
sbit T6963C_ctrlfs_Direction  at TRISC5_bit;     // FS signal direction

// End T6963C module connections

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
  ANSELD = 0;

  TRISB0_bit = 1;               // Set RB0 as input
  TRISB1_bit = 1;               // Set RB1 as input
  TRISB2_bit = 1;               // Set RB2 as input
  TRISB3_bit = 1;               // Set RB3 as input
  TRISB4_bit = 1;               // Set RB4 as input
  TRISB5_bit = 1;               // Set RB5 as input

  T6963C_ctrlce_Direction = 0;
  T6963C_ctrlce = 0;            // Enable T6963C
  T6963C_ctrlfs_Direction = 0;
  T6963C_ctrlfs = 0;            // Font Select 8x8

  panel = 0;
  i = 0;
  curs = 0;
  cposx = cposy = 0;

  // Initialize T6963C
  T6963C_init(240, 64, 8);

  /*
   * Enable both graphics and text display at the same time
   */
  T6963C_graphics(1);
  T6963C_text(1);

  /*
   * Text messages
   */
  T6963C_write_text(txt, 0, 0, T6963C_ROM_MODE_XOR);
  T6963C_write_text(txt1, 0, 7, T6963C_ROM_MODE_XOR);

  /*
   * Cursor
   */
  T6963C_cursor_height(8);       // 8 pixel height
  T6963C_set_cursor(0, 0);       // Move cursor to top left
  T6963C_cursor(0);              // Cursor off

  /*
   * Draw solid boxes
   */
  T6963C_box(0, 0, 239, 8, T6963C_WHITE);
  T6963C_box(0, 55, 239, 63, T6963C_WHITE);

  /*
   * Draw rectangles
   */
    T6963C_rectangle(0, 0, 239, 63, T6963C_WHITE);
    T6963C_rectangle(20, 11, 219, 53, T6963C_WHITE);
    T6963C_rectangle(40, 21, 199, 43, T6963C_WHITE);
    T6963C_rectangle(60, 30, 179, 34, T6963C_WHITE);

  /*
   * Draw rounded edge rectangle
   */
    T6963C_Rectangle_Round_Edges(30,16, 209, 48, 12, T6963C_WHITE);
    T6963C_Rectangle_Round_Edges(50,25, 189, 39, 5, T6963C_WHITE);

  /*
   * Draw filled rounded edge rectangle
   */
    T6963C_Rectangle_Round_Edges_Fill(10, 10, 229, 53, 12, T6963C_WHITE);
    T6963C_Rectangle_Round_Edges_Fill(15, 15, 224, 49, 12, T6963C_BLACK);
    T6963C_Rectangle_Round_Edges_Fill(20, 20, 219, 44, 9, T6963C_WHITE);
    T6963C_Rectangle_Round_Edges_Fill(25, 25, 214, 39, 7, T6963C_BLACK);
    T6963C_Rectangle_Round_Edges_Fill(30, 30, 209, 34, 2, T6963C_WHITE);

  /*
   * Draw a cross
   */
    T6963C_line(0, 0, 239, 63, T6963C_WHITE);
    T6963C_line(0, 63, 239, 0, T6963C_WHITE);

  /*
   * Draw circles
   */
    T6963C_circle(120, 32, 10, T6963C_WHITE);
    T6963C_circle(120, 32, 30, T6963C_WHITE);
    T6963C_circle(120, 32, 50, T6963C_WHITE);
    T6963C_circle(120, 32, 70, T6963C_WHITE);
    T6963C_circle(120, 32, 90, T6963C_WHITE);
    T6963C_circle(120, 32, 110, T6963C_WHITE);
    T6963C_circle(120, 32, 130, T6963C_WHITE);

  /*
   * Draw filled circles
   */
    T6963C_circle_fill(120, 32, 40, T6963C_WHITE);
    T6963C_circle_fill(120, 32, 35, T6963C_BLACK);
    T6963C_circle_fill(120, 32, 30, T6963C_WHITE);
    T6963C_circle_fill(120, 32, 25, T6963C_BLACK);
    T6963C_circle_fill(120, 32, 20, T6963C_WHITE);
    T6963C_circle_fill(120, 32, 15, T6963C_BLACK);
    T6963C_circle_fill(120, 32, 10, T6963C_WHITE);
    T6963C_circle_fill(120, 32, 5, T6963C_BLACK);

  Delay_ms(1000);
  T6963C_sprite(60, 0, einstein, 120, 64);     // Draw a sprite
  Delay_ms(1000);

  T6963C_setGrPanel(1);                        // Select other graphic panel

  T6963C_image(mikroE_240x64_bmp);
  T6963C_displayGrPanel(1);
  Delay_ms(1000);
    T6963C_grFill(0);
    T6963C_PartialImage(0, 0, 64, 64, 240, 64, mikroE_240x64_bmp);   // Display partial image
    Delay_ms(1000);
    T6963C_graphics(0);
    T6963C_image(mikroE_240x64_bmp);
  T6963C_graphics(1);
  T6963C_displayGrPanel(0);
 
  for(;;) {                                    // Endless loop
    
    /*
     * If RB0 is pressed, display only graphic panel
     */
    if(RB0_bit) {
      T6963C_graphics(1);
      T6963C_text(0);
      Delay_ms(300);
      }

    /*
     * If RB1 is pressed, toggle the display between graphic panel 0 and graphic panel 1
     */
    else if(RB1_bit) {
      panel++;
      panel &= 1;
      T6963C_displayGrPanel(panel);
      Delay_ms(300);
    }
    
    /*
     * If RB2 is pressed, display only text panel
     */
    else if(RB2_bit) {
      T6963C_graphics(0);
      T6963C_text(1);
      Delay_ms(300);
    }

    /*
     * If RB3 is pressed, display text and graphic panels
     */
    else if(RB3_bit) {
      T6963C_graphics(1);
      T6963C_text(1);
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
          T6963C_cursor(0);
          break;
        case 1:
          // blinking cursor
          T6963C_cursor(1);
          T6963C_cursor_blink(1);
          break;
        case 2:
          // non blinking cursor
          T6963C_cursor(1);
          T6963C_cursor_blink(0);
          break;
        }
      Delay_ms(300);
      }
   
    /*
     * If RB5 is pressed, perform the "Partial image" demostration
     */
    else if(RB5_bit) {
      T6963C_setGrPanel(0);
      T6963C_setTxtPanel(0);
      T6963C_txtFill(0);
      T6963C_setGrPanel(1);
      T6963C_setTxtPanel(0);
      T6963C_graphics(1);
      T6963C_text(1);
      T6963C_displayGrPanel(1);
      T6963C_write_text(txt2, 5, 7, T6963C_ROM_MODE_XOR);
      Delay_1sec();

      for(s = 0; s < 3; s++){
        T6963C_grFill(0);
        T6963C_PartialImage(s*80 + 10, 0, 64, 64, 240, 64, mikroE_240x64_bmp); // Partial image
        Delay_ms(500);
       }

      T6963C_txtFill(0);
      T6963C_image(mikroE_240x64_bmp);
      T6963C_write_text(txt, 0, 0, T6963C_ROM_MODE_XOR);
      T6963C_write_text(txt1, 0, 7, T6963C_ROM_MODE_XOR);
    }

    /*
     * Move cursor, even if not visible
     */
    cposx++;
    if(cposx == T6963C_txtCols) {
      cposx = 0;
      cposy++;
      if(cposy == T6963C_grHeight / T6963C_CHARACTER_HEIGHT) {
        cposy = 0;
        }
      }
    T6963C_set_cursor(cposx, cposy);

    Delay_ms(100);
    }
}