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
     MCU:             PIC16F1937
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41364B.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     None.
*/
 
char i = 0;
unsigned int addr, data_, dataAR[4][4] = {{0x3FAA+0,  0x3FAA+1,  0x3FAA+2,  0x3FAA+3},
                                          {0x3FAA+4,  0x3FAA+5,  0x3FAA+6,  0x3FAA+7},
                                          {0x3FAA+8,  0x3FAA+9,  0x3FAA+10, 0x3FAA+11},
                                          {0x3FAA+12, 0x3FAA+13, 0x3FAA+14, 0x3FAA+15}};

void main() {
  ANSELA = 0;        // Configure AN pins as digital
  ANSELB = 0;
  ANSELD = 0;
  ANSELE = 0;
  
  C1ON_bit = 0;                       // Disable comparators
  C2ON_bit = 0;
  PORTB = 0;                          // Initial PORTB value
  TRISB = 0;                          // Set PORTB as output
  PORTC = 0;                          // Initial PORTC value
  TRISC = 0;                          // Set PORTC as output
  Delay_ms(500);

  // All block writes
  // to program memory are done as 16-word erase by
  // eight-word write operations. The write operation is
  // edge-aligned and cannot occur across boundaries.
  // Therefore it is recommended to perform flash writes in 16-word chunks.
  // That is why lower 4 bits of start address [3:0] must be zero.
  // Since FLASH_Write routine performs writes in 4-word chunks,
  // we need to call it 4 times in a row.
  addr = 0x0430;                      // starting Flash address, valid for P16F887
  for (i = 0; i < 4; i++){            // Write some data to Flash
    Delay_ms(100);
    FLASH_Write(addr+i*4, dataAR[i]);
  }
  Delay_ms(500);

  addr = 0x0430;
  for (i = 0; i < 16; i++){
    data_ = FLASH_Read(addr++);       // P16's FLASH is 14-bit wide, so
    Delay_us(10);                     //   two MSB's will always be '00'
    PORTB = data_;                    // Display data on PORTB (LS Byte)
    PORTC = data_ >> 8;               // and PORTC (MS Byte)
    Delay_ms(500);
  }
}