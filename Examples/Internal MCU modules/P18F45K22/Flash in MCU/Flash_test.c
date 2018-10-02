/*
 * Project name:
     Flash_Test (Demonstration of writing to PIC's internal flash memory)
 * Copyright:
     (c) MikroElektronika, 2005-2008.
 * Description:
     This is a simple demonstration how to use to PIC's internal flash memory to
     store data. The data is being written starting from the given location;
     then, the same locations are read and the data is displayed on PORTB and PORTC.
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
     - Turn ON PORTB LEDs at SW3.2 (board specific)
*/
 
char i = 0;
unsigned short dataWr[64];
unsigned short dataRd;
unsigned int addr;

void main() {
  ANSELB = 0;                         // Configure AN pins as digital
  
  LATB = 0;                          // Initial PORTB value
  TRISB = 0;                          // Set PORTB as output
  Delay_ms(500);

  // All block writes
  // to program memory are done as 16-word erase by
  // eight-word write operations. The write operation is
  // edge-aligned and cannot occur across boundaries.
  // Therefore it is recommended to perform flash writes in 16-word chunks.
  // That is why lower 4 bits of start address [3:0] must be zero.

  addr = 0x4000;                      // starting Flash address, valid for P18F45K22

  for (i=0; i<64; i++)                // Write some data to Flash
    dataWr[i] = i+1;
  Delay_ms(500);
  FLASH_Erase_Write_64(addr, dataWr); // Write some data to Flash
  
  addr = 0x4000;
  for (i = 0; i < 64; i++){
    dataRd = FLASH_Read(addr++);
    Delay_us(10);
    LATB = dataRd;                     // Display data on PORTB
    Delay_ms(200);
  }
}