/*
 * Project name:
     Can_2nd (CAN Network demonstration with mikroE's CAN module)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Description:
     This project is a simple demonstration of CAN on PIC18F448 with minor
     adjustments, it should work with any other MCU that has a CAN module.
     This code demonstrates how to use CAN library functions and procedures.
     It is used together with the Can_1st example (on second MCU), and it can
     be used to test the connection of MCU to the CAN network.
     This node receives data, increments it by 1 and send it back to the 1st node.
 * Test configuration:
     MCU:             PIC18F448
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 8.0000 MHz
     Ext. Modules:    ac:CAN1_Board on PORTB
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
    - Consult the CAN standard about CAN bus termination resistance.
    - Turn OFF LEDs SW3.2 and pull-up (PortB htree-state switch)  (board specific)
      lines on PORTB. mE CAN extra board should be connected to PORTB.
    - Turn on LEDs on PORTC (SW3.3) (board specific)
    - PORTB.B2-> CAN_TX and PORTB.B3-> CAN_RX
 */

unsigned char Can_Init_Flags, Can_Send_Flags, Can_Rcv_Flags; // can flags
unsigned char Rx_Data_Len;                                   // received data length in bytes
char RxTx_Data[8];                                           // can rx/tx data buffer
char Msg_Rcvd;                                               // reception flag
const long ID_1st = 12111, ID_2nd = 3;                       // node IDs
long Rx_ID;

void main() {

  PORTC = 0;                                                // clear PORTC
  TRISC = 0;                                                // set PORTC as output

  Can_Init_Flags = 0;                                       //
  Can_Send_Flags = 0;                                       // clear flags
  Can_Rcv_Flags  = 0;                                       //

  Can_Send_Flags = _CAN_TX_PRIORITY_0 &                     // form value to be used
                   _CAN_TX_XTD_FRAME &                      //     with CANWrite
                   _CAN_TX_NO_RTR_FRAME;

  Can_Init_Flags = _CAN_CONFIG_SAMPLE_THRICE &              // form value to be used
                   _CAN_CONFIG_PHSEG2_PRG_ON &              // with CANInit
                   _CAN_CONFIG_XTD_MSG &
                   _CAN_CONFIG_DBL_BUFFER_ON &
                   _CAN_CONFIG_VALID_XTD_MSG &
                   _CAN_CONFIG_LINE_FILTER_OFF;

  CANInitialize(1,3,3,3,1,Can_Init_Flags);                  // initialize external CAN module
  CANSetOperationMode(_CAN_MODE_CONFIG,0xFF);               // set CONFIGURATION mode
  CANSetMask(_CAN_MASK_B1,-1,_CAN_CONFIG_XTD_MSG);          // set all mask1 bits to ones
  CANSetMask(_CAN_MASK_B2,-1,_CAN_CONFIG_XTD_MSG);          // set all mask2 bits to ones
  CANSetFilter(_CAN_FILTER_B2_F3,ID_1st,_CAN_CONFIG_XTD_MSG);// set id of filter B2_F3 to 1st node ID

  CANSetOperationMode(_CAN_MODE_NORMAL,0xFF);               // set NORMAL mode

  while (1) {                                                              // endless loop
    Msg_Rcvd = CANRead(&Rx_ID , RxTx_Data , &Rx_Data_Len, &Can_Rcv_Flags); // receive message
    if ((Rx_ID == ID_1st) && Msg_Rcvd) {                                   // if message received check id
      PORTC = RxTx_Data[0];                                                // id correct, output data at PORTC
      RxTx_Data[0]++ ;                                                     // increment received data
      CANWrite(ID_2nd, RxTx_Data, 1, Can_Send_Flags);                      // send incremented data back
    }
  }
}