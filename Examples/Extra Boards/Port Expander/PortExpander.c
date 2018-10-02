/*
 * Project name:
     PortExpander (Demonstration of the Port Expander library routines)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20080930:
       - initial release;
     20111012;
       - revision (JK);
 * Description:
     This project is simple demonstration how to use Port Expander Library functions.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:Port_Expander_Board on PORTC
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on LEDs on PORTB SW3.2 (board specific).
 */

// Port Expander module connections
sbit  SPExpanderRST at LATC0_bit;
sbit  SPExpanderCS  at LATC1_bit;
sbit  SPExpanderRST_Direction at TRISC0_bit;
sbit  SPExpanderCS_Direction  at TRISC1_bit;
// End Port Expander module connections

unsigned char i = 0;

void main() {
  ANSELB = 0;
  ANSELC = 0;                            // Configure AN pins as digital I/O
  
  TRISB = 0;                             // Set PORTB as output
  LATB  = 0xFF;

  // If Port Expander Library uses SPI1 module
  SPI1_Init();                                   // Initialize SPI module used with PortExpander

//  If Port Expander Library uses SPI2 module
//  SPI2_Init();                                   // Initialize SPI module used with PortExpander

  Expander_Init(0);                      // Initialize Port Expander

  Expander_Set_DirectionPortA(0, 0x00);  // Set Expander's PORTA to be output

  Expander_Set_DirectionPortB(0,0xFF);   // Set Expander's PORTB to be input
  Expander_Set_PullUpsPortB(0,0xFF);     // Set pull-ups to all of the Expander's PORTB pins

  while(1) {                             // Endless loop
    Expander_Write_PortA(0, i++);        // Write i to expander's PORTA
    LATB = Expander_Read_PortB(0);       // Read expander's PORTB and write it to LEDs
    Delay_ms(100);
  }
  
}