/*
 * Project name:
      SPI (Driving external Digital-to-Analog converter)
 * Copyright:
     (c) MikroElektronika, 2012
 * Revision History:
     20080930:
       - initial release;
     20111011;
       - revision (JK);
 * Description:
     This is a sample program which demonstrates the use of the Microchip's
     MCP4921 12-bit D/A converter with PIC MCUs. This device accepts digital
     input (number from 0..4095) and transforms it to the output voltage,
     ranging from 0..Vref. In this example the DAC communicates with MCU
     through the SPI communication.
     Buttons RA0 and RA1 are used to change value sent to DAC.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:DAC_Board on PORTC
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Turn on PIC and CS0 switches on DAC extra board.
     - Put button jumper (J17) into VCC position and pull-down PORTA (PORTA three-state switch). (board specific)
 */

// DAC module connections
sbit Chip_Select at LATC1_bit;
sbit Chip_Select_Direction at TRISC1_bit;
// End DAC module connections

unsigned int value;                     

void InitMain() {
  TRISA0_bit = 1;                        // Set RA0 pin as input
  TRISA1_bit = 1;                        // Set RA1 pin as input
  Chip_Select = 1;                       // Deselect DAC
  Chip_Select_Direction = 0;             // Set CS# pin as Output
  SPI1_Init();                           // Initialize SPI module
}

// DAC increments (0..4095) --> output voltage (0..Vref)
void DAC_Output(unsigned int valueDAC) {
  char temp;
 
  Chip_Select = 0;                       // Select DAC chip
  
  // Send High Byte                                         
  temp = (valueDAC >> 8) & 0x0F;         // Store valueDAC[11..8] to temp[3..0]
  temp |= 0x30;                          // Define DAC setting, see MCP4921 datasheet
  SPI1_Write(temp);                      // Send high byte via SPI
  
  // Send Low Byte
  temp = valueDAC;                       // Store valueDAC[7..0] to temp[7..0]
  SPI1_Write(temp);                      // Send low byte via SPI
  
  Chip_Select = 1;                       // Deselect DAC chip
}

void main() {
  ANSELA = 0;
  ANSELC = 0;
  SLRCON = 0;                            // Set output slew rate on all ports at standard rate
  
  InitMain();                            // Perform main initialization

  value = 2048;                          // When program starts, DAC gives
                                         //   the output in the mid-range
                                          
 while (1) {                             // Endless loop

    if ((RA0_bit) && (value < 4095)) {   // If RA0 button is pressed
      value++;                           //   increment value
      }
    else {
      if ((RA1_bit) && (value > 0)) {    // If RA1 button is pressed
        value--;                         //   decrement value
        }
      }
    DAC_Output(value);                   // Send value to DAC chip
    Delay_ms(1);                         // Slow down key repeat pace
  }
}