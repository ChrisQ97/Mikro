/* Project name:
     External Interrupt on PORTD
 * Copyright:
     (c) Mikroelektronika, 2011.
 * Revision History:
     20101006:
     - initial release;
     20110224:
     - adapted for PRO compilers (TL);
 * Description:
     This is a simple 'Hello World' project. It detects press on PORTB0 and
     shows result on diodes connected to PORTD.
 * Test configuration:
     MCU:             PIC18F4520
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC v4.60
     http://www.mikroe.com/mikroc/pic/

 * NOTES:
     - Make sure you turn ON the PORTD LEDs (SW9.4), set PORTB Pull Up Jumper in Vcc position (J2)
     and turn on PORTB0 Switch (SW2.1)
*/

unsigned short sync_flag;
char bad_synch;            // variable for detecting bad synchronization
int cnt = 0;               // Global variable cnt

void Interrupt() {
  // This is external INT0 interrupt (for sync start)
  //   - once we get falling edge on RB0 we are disabling INT0 interrupt

  if (INT0IF_bit && INT0IE_bit) {
     cnt = 0;
     sync_flag = 1;
     INT0IF_bit = 0;
     INT0IE_bit = 0;
     PORTD = 0xFF;
   }
}

void main() {

  ADCON1 = 0x0F;           // AD converter off
  CMCON = 7;
  sync_flag = 0;           // sync_flag is set when falling edge on RB0 is detected

  while(1){

  TRISB = 0xFF;            // Set PB0 as input
  TRISD = 0x00;            // Set PortD as output
  PORTD = 0x00;            // Starting value for PortD

  INTEDG0_bit = 0;         // Interrupt on falling edge on RB0
  INT0IF_bit = 0;          // Clear INT0IF
  INT0IE_bit = 0;          // turn OFF interrupt on INT0
  GIE_bit = 1;             // enable GIE

  while(1){
      bad_synch = 0;       // set bad synchronization variable to zero
      sync_flag = 0;       // reseting sync flag
      INT0IF_bit = 0;
      INT0IE_bit = 1;      // enable external interrupt on RB0 (start sync procedure)
    }
  }
}