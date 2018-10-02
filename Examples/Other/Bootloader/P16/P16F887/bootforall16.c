static unsigned block[32], rcv_1, rcv_2;

void Susart_Init(unsigned short brg_reg) org  0x1DCF {
  unsigned short i;

  RCSTA = 0x90;
  TXSTA = 0x26;
  TRISC.B7 = 1;
  TRISC.B6 = 0;

  while (PIR1.RCIF)
    i = RCREG;

  SPBRG = brg_reg;
}


void Susart_Write(char data_) org 0x1DB5  {

  while (!TXSTA.TRMT)
    ;
  TXREG = data_;
}

unsigned short Susart_Data_Ready() org 0x1DA2 {
  return (PIR1.RCIF);
}

unsigned short Susart_Read() org 0x1D8C {
  unsigned short rslt;
  rslt = RCREG;

  if (RCSTA.OERR) {
     RCSTA.CREN = 0;
     RCSTA.CREN = 1;
  }
  return rslt;
}

//------------------------------------------------------------------------------}
// After bootloading nops are replaced with page setting and goto to the location
// of the main of loaded program.
void Start_Program() org 0x1FA0  {
  asm nop;
  asm nop;
  asm nop;
  asm nop;
}

//------------------------------------------------------------------------------}
// After bootloading reset vector is adjusted before writing it to new location
// (address of Start_program, 0x1FA0)
void AdjustGoto()               org 0x1D50 {

     rcv_1    = block[3];            // rcv variables are used as temps
     rcv_2    = block[4];            // for saving block[3..4]

     block[4] = block[2];            // page setting and goto to
     block[3] = block[1];            // the main of user's (loaded) program
     block[2] = block[0];            // (assuming that page is set to zero)
     
     block[0] = 0x118A;              // ensuring that PCLATH page bits are cleared
     block[1] = 0x120A;              // as after reset (requred by code block above)
}

//------------------------------------------------------------------------------}
// This procedure will recieve the (start address DIV 32) in the ROM where
// the 32 words will be written to.
// eg. To write to location 0x0000 - Flash_Write_Address(0x00);
//     To write to location 0x0020 - Flash_Write_Adderss(0x01);
//     To write to location 0x1FA0 - Flash_Write_Adderss(0xFD);
void Flash_Write_Address(unsigned beginorg)  org 0x1DF2 {

     unsigned total;
     unsigned temp;
     char loop;
     char SaveIntCon;

     loop = 0;
     while (loop != 32) {
          total = (beginorg << 5) + loop;
          temp  = block[loop];
          SaveIntCon = INTCON;
          EEADR   = (char)(total);
          EEADRH  = (char)(total >> 8);
          EEDATA  = (char)(temp);
          EEDATH  = (char)(temp >> 8);
          EECON1.EEPGD = 1;
          EECON1.WREN  = 1;
          INTCON.GIE   = 0;
          EECON2 = 0x55;
          EECON2 = 0xAA;
          EECON1.WR    = 1;
          asm nop;
          asm nop;
          INTCON = SaveIntCon;
          EECON1.WREN = 0;
          loop++;
     }
}
//------------------------------------------------------------------------------}
// This function will send a char over the USART until another char is recieved
// or until a timeout is reached. If the correct char is recieved the function will
// return false else it will return true

unsigned short Susart_Write_Loop(char send, char recieve)    org 0x1ED2 {
     char  stop, r;

     r    = 0;
     stop = 0;
     while (stop != 1) {
          boot16_Delay_5ms();
          Susart_Write(send);
          boot16_Delay_5ms();
          r++;
          if ( Susart_Data_Ready() ) {
            if (Susart_Read() == recieve)  stop = 1;
            }
          if (r == 255) stop = 1;
     }

     return  r;
     
}

//------------------------------------------------------------------------------}
// This procedure will recover the bootlocation 0x0000, 0x0001 and 0x0002 to point
// to the bootloaer's main.
// It will also move the reset vector of the program that is uploaded to a new
// location. In this case it is address of Start_program, 0x1FA0.
void Write_Begin()                 org 0x1E56    {

     AdjustGoto();                   // Set page and goto to user's main

     Flash_Write_Address(0xFD);      // write 0xFD shl 5 = 0x1FA0
     block[0] = 0x160A;              // page setting
     block[1] = 0x158A;              // page setting
     block[2] = 0x2E7D;              // points to main procedure
     block[3] = rcv_1;               // rcv variables are used as temps
     block[4] = rcv_2;               // for saving block[3..4]
}

//------------------------------------------------------------------------------}
// Handles comunication between PIC and PC
void Start_Bootload()               org 0x1F10  {

     char     i;
     unsigned j;

    i = 0;
    j = 0;


     for ( ; ; )  {
          if (i == 32) {             // If 32 words recieved then write to flash
               if (j == 0)  Write_Begin();
               Flash_Write_Address(j);
               i = 0;
               j++;
          }

          Susart_Write('y');                        // Ask for rcv_2
          do ; while (Susart_Data_Ready() != 1);
          rcv_2 = Susart_Read();                        // Read rcv_2

          Susart_Write('x');                        // Ask for rcv_1
          do ; while (Susart_Data_Ready() != 1);
          rcv_1 = Susart_Read();                        // Read rcv_1


          block[i] = rcv_1 << 8;                     // Save rcv_1rcv_2 in block[i]
          block[i] = block[i] + rcv_2;
          i++;
                               // Next word
     }
}
