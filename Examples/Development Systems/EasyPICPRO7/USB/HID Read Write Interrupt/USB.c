/*
 * Project name:
     HID Read Write Interrupt (Testing the USB HID connection)
 * Copyright:
     (c) MikroElektronika, 2010
 * Revision History:
     20120116:
       - initial release (JK);
 * Description:
     This example establishes connection with the HID terminal that is active
     on the PC. Upon connection establishment, the HID Device Name will appear
     in the respective window, and the software will start transmitting fixed
     message over the USB HID connection, for eternity.
 * Test configuration:
     MCU:             PIC18F87J50
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39775c.pdf
     dev.board:       easypic pro v7 - ac:USB
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS, 8.000 MHz  (USB osc. is raised with PLL to 48.000MHz)
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Be VERY careful about the oscillator configuration flags,
       there's so much place for mistake!
*/

unsigned char readbuff[64]  absolute 0x500; // place the arrays to USB section
unsigned char writebuff[64] absolute 0x540;

char cnt;
char kk;

void interrupt(){
   USB_Interrupt_Proc();                 // USB servicing is done inside the interrupt
}

void main(void){
  PLLEN_bit=1;                           // PLL turned on
  Delay_ms(150);                         // wait for a while to oscillator stabilizes

  ANCON0 = 0xFF;                         // Default all pins to digital
  ANCON1 = 0xFF;

  HID_Enable(&readbuff,&writebuff);      // Enable HID communication

  while(1){
    while(!HID_Read());                  // wait for data on USB

    for(cnt=0;cnt<64;cnt++)
      writebuff[cnt]=readbuff[cnt];      // move data to output buffer

    while(!HID_Write(&writebuff,64));    // echo the data back
  }
}