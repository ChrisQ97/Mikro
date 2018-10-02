/*
 * Project name:
     CFlash_Common (Basic use of Compact Flash common library)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20081218:
       - initial release;
 * Description:
     This project is a simple demonstration of CF(Compact Flash) Library which
     shows how to use CF card ( http://en.wikipedia.org/wiki/Compact_flash )
     data accessing routines. With minor adjustments,
     this example should work with any other MCU.
     Data access routines need two ports for communication with CF card.
     Before write operation make sure that you do not overwrite boot or FAT
     sector, because it could make your card unreadable by a PC or by a digital
     photo camera.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:Compact_Flash_Board on PORTB(Control) and PORTD(Data)
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - turn ON LED on PORTC (switch 3.3) (board specific)
     - This example does NOT cover writing/reading of FILES on the CF media. This
       topic is covered in CF_FAT16 examples.
     - For some CF cards external power supply may be required.
 */

// set compact flash pinout
char Cf_Data_Port at PORTD;

sbit CF_RDY at RB7_bit;
sbit CF_WE  at LATB6_bit;  // for writing to output pin always use latch (PIC18 family)
sbit CF_OE  at LATB5_bit;  // for writing to output pin always use latch (PIC18 family)
sbit CF_CD1 at RB4_bit;
sbit CF_CE1 at LATB3_bit;  // for writing to output pin always use latch (PIC18 family)
sbit CF_A2  at LATB2_bit;  // for writing to output pin always use latch (PIC18 family)
sbit CF_A1  at LATB1_bit;  // for writing to output pin always use latch (PIC18 family)
sbit CF_A0  at LATB0_bit;  // for writing to output pin always use latch (PIC18 family)

sbit CF_RDY_direction at TRISB7_bit;
sbit CF_WE_direction  at TRISB6_bit;
sbit CF_OE_direction  at TRISB5_bit;
sbit CF_CD1_direction at TRISB4_bit;
sbit CF_CE1_direction at TRISB3_bit;
sbit CF_A2_direction  at TRISB2_bit;
sbit CF_A1_direction  at TRISB1_bit;
sbit CF_A0_direction  at TRISB0_bit;
// end of cf pinout

char SignalPort           at LATC;
char SignalPort_direction at TRISC;

void InitCF() {
  CF_CD1_direction = 1;
  while (Cf_Detect() == 0)                // wait until CF card is inserted
    ;
  Cf_Init();                              // initialize CF
  while (!CF_RDY)
    ;
  Delay_ms(2000);                         // wait for a while until the card is stabilized
}                                         //   period depends on used CF card

void TestBytes() {
  unsigned int i;

  ///// Write numbers 0..511 to sector 590
  Cf_Write_Init(590,1);                   // Initialize write at sector address 590
                                          //     for 1 sector
  SignalPort = 0x03;                      // Notify that write has started
  Delay_ms(1000);
  for (i=0; i<=511; i++)                  // Write 512 bytes to sector 590
    Cf_Write_Byte(i);

  SignalPort = 0x07;                      // Notify that write end and read start
  Delay_ms(1000);
  
  Cf_Read_Init(590,1);                    // Initialize read from sector address 590
                                          //    for 1 sector
  for (i=0; i<=511; i++) {                // Read 512 bytes from sector address 590
    SignalPort = Cf_Read_Byte();          // Read one byte at time and display
                                          //    readings on signal port
    Delay_ms(5);                          // Wait for a while to see results
  }
  Delay_ms(1000);

  ///// Write numbers 511..0 to sector 590
  Cf_Write_Init(590,1);                   // Initialize write at sector address 590
                                          //     for 1 sector
  SignalPort = 0x03;                      // Notify that write has started
  Delay_ms(1000);
  for (i=0; i<=511; i++)                  // Write 512 bytes to sector 590
    Cf_Write_Byte(511-i);

  SignalPort = 0x07;                      // Notify that write end and read start
  Delay_ms(1000);

  Cf_Read_Init(590,1);                    // Initialize read from sector address 590
                                          //    for 1 sector
  for (i=0; i<=511; i++) {                // Read 512 bytes from sector address 590
    SignalPort = Cf_Read_Byte();          // Read one byte at time and display
                                          //    readings on signal port
    Delay_ms(5);                          // Wait for a while to see results
  }
  Delay_ms(1000);
}

// Main program
void main() {
  ANSELB = 0;                             // Configure AN pins as digital
  ANSELC = 0;
  ANSELD = 0;
  
  SignalPort_direction = 0;               // designate PORTC as output
  SignalPort = 0x01;                      // Notify test start
  InitCF();

  TestBytes();
  SignalPort = 0x0F;                      // Notify test end
}