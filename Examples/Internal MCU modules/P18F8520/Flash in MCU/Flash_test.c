/*
 * Project name:
     Flash_Test (Demonstration of writing to PIC's internal flash memory)
 * Copyright:
     (c) MikroElektronika, 2005-2008.
 * Description:
     This is a simple demonstration how to use to PIC's internal flash memory to
     store data. The data is being written starting from the given location;
     then, the same locations are read and the data is displayed on PORTB.
 * Test configuration:
     MCU:             P18F8520
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39609b.pdf
     Dev.Board:       EasyPIC PRO v7
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS, 10.0 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     -  Turn on LEDs on PORTB switches SW10.2 (board specific)
*/
 
char i;
long addr;
unsigned short dataRd;
unsigned short dataWr[64];

void main() {
  ADCON1 |= 0x0F;                     // Configure AN pins as digital
  CMCON  |= 7;                        // Disable comparators

  PORTB = 0;
  TRISB = 0;

  for (i=0; i<64; i++)
    dataWr[i] = i+1;

  addr = 0x00000A40;                  // valid for P18F8520
  FLASH_Erase_Write_64(addr, dataWr);

  addr = 0x00000A40;
  for (i = 0; i < 64; i++) {
    dataRd = FLASH_Read(addr++);
    PORTB = dataRd;
    Delay_ms(200);
  }
}