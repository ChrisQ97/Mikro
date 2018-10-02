 /*
 * Project Name:
     T6963C_240x128 (GLCD Library demo for Toshiba's T6963 Controller)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20080930:
       - initial release; Credits to Bruno Gavand.
 * Description:
     This code in intended to work with GLCD's based on TOSHIBA T6963C 
     controller via SPI communication. Pressing buttons RB0 .. RB5 generates
     commands for text and graphic displaying.
     This parts may need a -15V power supply on Vee for LCD drive,
     a simple DC/DC converter can be made with a 2N2905, 220 µH self, diode & 47 µF cap,
     transistor base is driven with PWM through a current limiting resistor.
     This parts have a 8 Kb built-in display RAM, this allows 2 graphics panels
     and one text panel.
 * Test configuration:
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    ac:GLCD_240x128_Adapter_Board on PORTC(Control) and PORTD(Data),
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Put button jumper (J17) into Vcc position and pull-down PORTB.
 */

#include        "__T6963C.h"
                            
// T6963C module connections
char T6963C_dataPort at PORTD;                   // DATA port

sbit T6963C_ctrlwr  at RC2_bit;                  // WR write signal
sbit T6963C_ctrlrd  at RC1_bit;                  // RD read signal
sbit T6963C_ctrlcd  at RC0_bit;                  // CD command/data signal
sbit T6963C_ctrlrst at RC4_bit;                  // RST reset signal
sbit T6963C_ctrlwr_Direction  at TRISC2_bit;     // WR write signal
sbit T6963C_ctrlrd_Direction  at TRISC1_bit;     // RD read signal
sbit T6963C_ctrlcd_Direction  at TRISC0_bit;     // CD command/data signal
sbit T6963C_ctrlrst_Direction at TRISC4_bit;     // RST reset signal

// Signals not used by library, they are set in main function
sbit T6963C_ctrlce at RC3_bit;                   // CE signal
sbit T6963C_ctrlfs at RC6_bit;                   // FS signal
sbit T6963C_ctrlmd at RC5_bit;                   // MD signal
sbit T6963C_ctrlce_Direction  at TRISC3_bit;     // CE signal direction
sbit T6963C_ctrlfs_Direction  at TRISC6_bit;     // FS signal direction
sbit T6963C_ctrlmd_Direction  at TRISC5_bit;     // MD signal direction
// End T6963C module connections

/*
 * bitmap pictures stored in ROM
 */
const code char mikroE_240x64_bmp[];     // PIC16F887 can't store larger picture(240x128) in ROM
const code char einstein[];

void main() {

  //#define LINE_DEMO             // Uncomment to demonstrate line drawing routines
  //#define FILL_DEMO           // Uncomment to demonstrate fill routines
  #define PARTIAL_IMAGE_DEMO  // Uncomment to demonstrate partial image routine

  char txt1[] = " EINSTEIN WOULD HAVE LIKED mE";
  char txt[] =  " GLCD LIBRARY DEMO, WELCOME !";
  char txt2[] = " Partial image demo!";

  unsigned char  panel;         // Current panel
  unsigned int   i;             // General purpose register
  unsigned char  curs;          // Cursor visibility
  unsigned int   cposx, cposy;  // Cursor x-y position
  unsigned short s;             // counter
  
  ANSEL  = 0;                   // Configure AN pins as digital I/O
  ANSELH = 0;
  C1ON_bit = 0;                 // Disable comparators
  C2ON_bit = 0;

  TRISB0_bit = 1;               // Set RB0 as input
  TRISB1_bit = 1;               // Set RB1 as input
  TRISB2_bit = 1;               // Set RB2 as input
  TRISB3_bit = 1;               // Set RB3 as input
  TRISB4_bit = 1;               // Set RB4 as input
  TRISB5_bit = 1;               // Set RB4 as input

  T6963C_ctrlce_Direction = 0;
  T6963C_ctrlce = 0;            // Enable T6963C
  T6963C_ctrlfs_Direction = 0;
  T6963C_ctrlfs = 0;            // Font Select 8x8
  T6963C_ctrlmd_Direction = 0;
  T6963C_ctrlmd = 0;            // Column number select

  panel = 0;
  i = 0;
  curs = 0;
  cposx = cposy = 0;

  // Initialize T6963C
  T6963C_init(240, 128, 8);

  /*
   * Enable both graphics and text display at the same time
   */
  T6963C_graphics(1);
  T6963C_text(1);

  /*
   * Text messages
   */
  T6963C_write_text(txt, 0, 0, T6963C_ROM_MODE_XOR);
  T6963C_write_text(txt1, 0, 15, T6963C_ROM_MODE_XOR);

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
  T6963C_box(0, 119, 239, 127, T6963C_WHITE);

  /*
   * Draw rectangles
   */
  #ifdef LINE_DEMO
    T6963C_rectangle(0, 0, 239, 127, T6963C_WHITE);
    T6963C_rectangle(20, 20, 219, 107, T6963C_WHITE);
    T6963C_rectangle(40, 40, 199, 87, T6963C_WHITE);
    T6963C_rectangle(60, 60, 179, 67, T6963C_WHITE);
  #endif

  /*
   * Draw filled rounded edge rectangle
   */
  #ifdef FILL_DEMO
    T6963C_Rectangle_Round_Edges_Fill(30, 30, 209, 97, 12, T6963C_WHITE);
    T6963C_Rectangle_Round_Edges_Fill(40, 40, 199, 87, 12, T6963C_BLACK);
    T6963C_Rectangle_Round_Edges_Fill(50, 50, 189, 77, 12, T6963C_WHITE);
  #endif

  /*
   * Draw a cross
   */
  #ifdef LINE_DEMO
    T6963C_line(0, 0, 239, 127, T6963C_WHITE);
    T6963C_line(0, 127, 239, 0, T6963C_WHITE);
  #endif

  /*
   * Draw circles
   */
  #ifdef LINE_DEMO
    T6963C_circle(120, 64, 10, T6963C_WHITE);
    T6963C_circle(120, 64, 30, T6963C_WHITE);
    T6963C_circle(120, 64, 50, T6963C_WHITE);
    T6963C_circle(120, 64, 70, T6963C_WHITE);
    T6963C_circle(120, 64, 90, T6963C_WHITE);
    T6963C_circle(120, 64, 110, T6963C_WHITE);
    T6963C_circle(120, 64, 130, T6963C_WHITE);
  #endif

  /*
   * Draw filled circles
   */
  #ifdef FILL_DEMO
    T6963C_circle_fill(120, 64, 30, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 25, T6963C_BLACK);
    T6963C_circle_fill(120, 64, 20, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 15, T6963C_BLACK);
    T6963C_circle_fill(120, 64, 10, T6963C_WHITE);
    T6963C_circle_fill(120, 64, 5, T6963C_BLACK);
  #endif

  Delay_ms(1000);
  T6963C_sprite(76, 4, einstein, 88, 119);           // Draw a sprite
  Delay_ms(1000);

  T6963C_setGrPanel(1);                              // Select other graphic panel
  T6963C_sprite(0, 0,  mikroE_240x64_bmp, 240, 64);  // 240x128 can't be stored in most of PIC16 MCUs
  T6963C_sprite(0, 64, mikroE_240x64_bmp, 240, 64);  //   it is replaced with smaller picture 240x64
                                                     //   Smaller picture is drawn two times
  
  T6963C_displayGrPanel(1);
  Delay_ms(1000);
  #ifdef PARTIAL_IMAGE_DEMO
    T6963C_grFill(0);
    T6963C_PartialImage(0, 0, 64, 64, 240, 128, mikroE_240x64_bmp);  // Display partial image
    Delay_ms(1000);
    T6963C_graphics(0);
    T6963C_sprite(0, 0,  mikroE_240x64_bmp, 240, 64);  // 240x128 can't be stored in most of PIC16 MCUs
    T6963C_sprite(0, 64, mikroE_240x64_bmp, 240, 64);  //   it is replaced with smaller picture 240x64
  #endif
  T6963C_graphics(1);
  T6963C_displayGrPanel(0);                            //   Smaller picture is drawn two times

  for(;;) {                                            // Endless loop

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

    #ifdef PARTIAL_IMAGE_DEMO
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
      T6963C_write_text(txt2, 5, 15, T6963C_ROM_MODE_XOR);
      Delay_1sec();
      T6963C_grFill(0);
      T6963C_PartialImage(0, 0, 64, 64, 240, 128, mikroE_240x64_bmp);
      Delay_1sec();
      T6963C_PartialImage(0, 0, 128, 64, 240, 128, mikroE_240x64_bmp);
      Delay_1sec();
      T6963C_PartialImage(0, 0, 240, 64, 240, 128, mikroE_240x64_bmp);
      Delay_1sec();
      T6963C_txtFill(0);
      T6963C_write_text(txt, 0, 0, T6963C_ROM_MODE_XOR);
      T6963C_write_text(txt1, 0, 15, T6963C_ROM_MODE_XOR);
    }
    #endif
    
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