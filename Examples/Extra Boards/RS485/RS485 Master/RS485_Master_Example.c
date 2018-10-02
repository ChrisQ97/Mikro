/*
 * Project name:
     RS485_Master_Example (RS485 Library demo - Master side)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20080930:
       - initial release;
     20111012;
       - revision (JK);
 * Description:
     This is a simple demonstration on how to use the mikroC's RS485 library.
     It is being used in pair with the RS485_Slave_Example project. Master (this
     machine) initiates communication with slave by sending 1 byte of data to
     the slave with designated slave address (160). The slave accepts data,
     increments it and sends it back to the master.
     The data received is shown on PORTB, Error on receive on PORTC and number of
     consecutive unsuccessful retries on PORTA.
     Several situations are shown here:
       - RS485 Master Init sequence;
       - Data sending master-to-slave with designated slave address;
       - Data sending master-to-slave with broadcast slave address (50);
       - Handling of unsuccessful master-slave communication (connection reset);
     Also shown here, but not strictly related to RS485 library, is:
       - Function calling from the interrupt routine - which data is to be saved,
         and how.
     For further explanations on RS485 library, please consult the mikroC Help.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:RS485_Board on PORTC
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Initialize the UART module before performing RS485 init.
     - RS485 module is connected to PORTC, i.e. where the UART module is.
     - Turn on LEDs on PORTB and PORTD switches SW3.2, SW3.4. (board specific)
 */

char dat[10];                          // buffer for receving/sending messages
char i,j;

sbit  rs485_rxtx_pin  at RC2_bit;               // set transcieve pin
sbit  rs485_rxtx_pin_direction at TRISC2_bit;   // set transcieve pin direction

// Interrupt routine
void interrupt() {
  RS485Master_Receive(dat);
}

void main(){
  long cnt = 0;

  ANSELB = 0;                          // Configure AN pins as digital I/O
  ANSELC = 0;
  ANSELD = 0;
  
  LATB   = 0;
  LATD   = 0;
  TRISB  = 0;
  TRISD  = 0;


  UART1_Init(9600);                    // initialize UART1 module
  Delay_ms(100);

  RS485Master_Init();                  // initialize MCU as Master
  dat[0] = 0xAA;
  dat[1] = 0xF0;
  dat[2] = 0x0F;
  dat[4] = 0;                          // ensure that message received flag is 0
  dat[5] = 0;                          // ensure that error flag is 0
  dat[6] = 0;

  RS485Master_Send(dat,1,160);


  RCIE_bit = 1;                        // enable interrupt on UART1 receive
  TXIE_bit = 0;                        // disable interrupt on UART1 transmit
  PEIE_bit = 1;                        // enable peripheral interrupts
  GIE_bit = 1;                         // enable all interrupts

  while (1){
                                       // upon completed valid message receiving
                                       //   data[4] is set to 255
    cnt++;
    if (dat[5])  {                     // if an error detected, signal it
      LATD = 0xAA;                    //   by setting portd to 0xAA
    }
    if (dat[4]) {                      // if message received successfully
      cnt = 0;
      dat[4] = 0;                      // clear message received flag
      j = dat[3];
      for (i = 1; i <= dat[3]; i++) {  // show data on PORTB
        LATB = dat[i-1];
      }                                // increment received dat[0]
      dat[0] = dat[0]+1;               // send back to master
      Delay_ms(1);
      RS485Master_Send(dat,1,160);

    }
   if (cnt > 100000) {
      LATD ++;
      cnt = 0;
      RS485Master_Send(dat,1,160);
      if (PORTD > 10)                  // if sending failed 10 times
        RS485Master_Send(dat,1,50);    //   send message on broadcast address
     }
  }

}