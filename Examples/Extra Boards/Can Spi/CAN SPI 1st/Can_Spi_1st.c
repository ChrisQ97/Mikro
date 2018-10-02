/*
 * Project name:
     Can_Spi_1st (CAN Network demonstration with mikroE's CAN-SPI module)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Description:
     This project is a simple demonstration of using CAN-SPI module; with minor
     adjustments, it should work with any other MCU that has a SPI module.
     This code demonstrates how to use CANSPI library functions and procedures.
     It is used together with the Can_Spi_2nd example (on second MCU), and it can
     be used to test the connection of MCU to the CAN network.
     This node initiates the communication with the Can_2nd node by sending some
     data to its address. The 2nd node responds by sending back the data incre-
     mented by 1. This (1st) node then does the same and sends incremented data
     back to 2nd node, etc.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:CAN_SPI_Board on PORTC
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - The indicator of good communication in this example is, that the 1st
       node always displays even data on PORTB, whilst the 2nd node always
       displays odd data.
     - Consult the CAN standard about CAN bus termination resistance.
     - Turn on LEDs on PORTB SW3.2
 */

unsigned char Can_Init_Flags, Can_Send_Flags, Can_Rcv_Flags; // can flags
unsigned char Rx_Data_Len;                                   // received data length in bytes
char RxTx_Data[8];                                           // can rx/tx data buffer
char Msg_Rcvd;                                               // reception flag
const long ID_1st = 12111, ID_2nd = 3;                       // node IDs
long Rx_ID;

// CANSPI module connections
sbit CanSpi_CS            at  RC0_bit;
sbit CanSpi_CS_Direction  at  TRISC0_bit;
sbit CanSpi_Rst           at  RC2_bit;
sbit CanSpi_Rst_Direction at  TRISC2_bit;
// End CANSPI module connections

void main() {

  ANSELB  = 0;                                                // Configure AN pins as digital I/O
  ANSELC = 0;
  SLRCON = 0;                                                 // Set output slew rate on all ports at standard rate
  
  LATB = 0;                                                   // clear PORTB
  TRISB = 0;                                                  // set PORTB as output

  Can_Init_Flags = 0;                                         //
  Can_Send_Flags = 0;                                         // clear flags
  Can_Rcv_Flags  = 0;                                         //

  Can_Send_Flags = _CANSPI_TX_PRIORITY_0 &                    // form value to be used
                   _CANSPI_TX_XTD_FRAME &                     //     with CANSPIWrite
                   _CANSPI_TX_NO_RTR_FRAME;

  Can_Init_Flags = _CANSPI_CONFIG_SAMPLE_THRICE &             // Form value to be used
                   _CANSPI_CONFIG_PHSEG2_PRG_ON &             //  with CANSPIInit
                   _CANSPI_CONFIG_XTD_MSG &
                   _CANSPI_CONFIG_DBL_BUFFER_ON &
                   _CANSPI_CONFIG_VALID_XTD_MSG;
  

  SPI1_Init();                                                     // initialize SPI1 module
  
  CANSPIInitialize(1,3,3,3,1,Can_Init_Flags);                      // Initialize external CANSPI module
  CANSPISetOperationMode(_CANSPI_MODE_CONFIG,0xFF);                // set CONFIGURATION mode
  CANSPISetMask(_CANSPI_MASK_B1,-1,_CANSPI_CONFIG_XTD_MSG);        // set all mask1 bits to ones
  CANSPISetMask(_CANSPI_MASK_B2,-1,_CANSPI_CONFIG_XTD_MSG);        // set all mask2 bits to ones
  CANSPISetFilter(_CANSPI_FILTER_B2_F4,ID_2nd,_CANSPI_CONFIG_XTD_MSG);// set id of filter B2_F4 to 2nd node ID

  CANSPISetOperationMode(_CANSPI_MODE_NORMAL,0xFF);                // set NORMAL mode

  RxTx_Data[0] = 9;                                                // set initial data to be sent

  CANSPIWrite(ID_1st, RxTx_Data, 1, Can_Send_Flags);               // send initial message

  while(1) {                                                                 // endless loop
    Msg_Rcvd = CANSPIRead(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags);// receive message
    if ((Rx_ID == ID_2nd) && Msg_Rcvd) {                                     // if message received check id
      LATB = RxTx_Data[0];                                                   // id correct, output data at PORTC
      RxTx_Data[0]++ ;                                                       // increment received data
      Delay_ms(10);
      CANSPIWrite(ID_1st, RxTx_Data, 1, Can_Send_Flags);                     // send incremented data back
    }
  }
}