/*
 * Project name:
     Boot_Test (using mikroC Bootloader on PIC18's)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20111017:
       - initial release
 * Description:
     This is a serial port Bootloader implementation. All required bootloader
     routines are placed in the boot18_32K file, the only thing that is
     user-configurable is the baudrate of the UART communication, which is set
     in the main() through appropriate call to Uart_Init(brg_reg).
     Once started in PIC, the bootloader waits for a while (approx. 5 seconds)
     to establish UART communication with the MikroBootloader application on the
     PC. If it fails to do so, the bootloader starts the programme already
     loaded in the MCU (initially it is just a NOP). If the communication is
     established, the bootloader receives the hex file from the PC and places it
     where requred (the MikroBootloader application reads out the hex file and
     takes care of the location where hex is to be placed). When hex download
     has finished, the user is notified by the MikroBootloader to reset the MCU,
     and MCU enters the described bootload sequence again.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - It's recommended not to alter the start address of the main().
       Otherwise, less space in ROM will be available for the application being bootloaded.
     - RX and TX UART switches SW1.1, SW2.1 on EasyPIC7 should be turned On (board specific).
 */

#pragma orgall 0x7CC0

#define BOOTLOADER_START_ADDR 0x7CC0
#define START_PROGRAM_ADDR 0x7FC0

static char block[64];

void Start_Program() org START_PROGRAM_ADDR{

}

unsigned short UART_Write_Loop(char send, char receive){
  unsigned int rslt = 0;

  while(1){
    Delay_5ms();
    UART1_Write(send);
    Delay_5ms();

    rslt++;
    if (rslt == 0x0200)
      return 0;
    if (UART1_Read() == receive)
      return 1;
  }
}

void Write_Begin(){
  FLASH_Erase_Write_64(START_PROGRAM_ADDR, block);
  //--- goto main
  block[0] = 0x60;  //0xF03EEF60
  block[1] = 0xEF;
  block[2] = 0x3E;
  block[3] = 0xF0;
}

void Start_Bootload(){
  char i = 0, xx, yy;
  long j = 0;

  while (1) {
    if (i == 64) {
      //--- If 32 words (64 bytes) recieved then write to flash
      if (!j)
        Write_Begin();
      if (j<BOOTLOADER_START_ADDR){
        FLASH_Erase_Write_64(j, block);
      }

      i = 0;
      j += 0x40;
    }
    //--- Ask for yy
    UART1_Write('y');
    while (!UART1_Data_Ready()) ;
    //--- Read yy
    yy = UART1_Read();
    //--- Ask for xx
    UART1_Write('x');
    while (!UART1_Data_Ready()) ;
    //--- Read xx
    xx = UART1_Read();
    //--- Save xxyy in block[i]
    block[i++] = yy;
    block[i++] = xx;
  }
}

void main() org BOOTLOADER_START_ADDR{
  ANSELC = 0;                         // Configure PORTC pins as digital
  UART1_Init(115200);                 // Init USART at 115200
  if (UART_Write_Loop('g','r')) {     // Send 'g' for ~5 sec, if 'r'
    Start_Bootload();                 //   received start bootload
  }
  else {
    Start_Program();                  //   else start program
  }
}