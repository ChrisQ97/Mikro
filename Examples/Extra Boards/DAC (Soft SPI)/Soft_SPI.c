/*
 * Project name:
       Soft_SPI (Driving external Digital-to-Analog converter)
 * Copyright:
     (c) MikroElektronika, 2012.
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
     through the Soft_SPI communication.
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
sbit Chip_Select at LATC0_bit;
sbit SoftSpi_CLK at LATC3_bit;
sbit SoftSpi_SDI at RC4_bit;
sbit SoftSpi_SDO at LATC5_bit;

sbit Chip_Select_Direction at TRISC0_bit;
sbit SoftSpi_CLK_Direction at TRISC3_bit;
sbit SoftSpi_SDI_Direction at TRISC4_bit;
sbit SoftSpi_SDO_Direction at TRISC5_bit;
// End DAC module connections

unsigned int value;

void InitMain() {
  TRISA0_bit = 1;                        // Set RA0 pin as input
  TRISA1_bit = 1;                        // Set RA1 pin as input
  Chip_Select = 1;                       // Deselect DAC
  Chip_Select_Direction = 0;             // Set CS# pin as Output
  Soft_SPI_Init();                       // Initialize Soft_SPI
}

// DAC increments (0..4095) --> output voltage (0..Vref)
void DAC_Output(unsigned int valueDAC) {
  char temp;

  Chip_Select = 0;                       // Select DAC chip

  // Send High Byte
  temp = (valueDAC >> 8) & 0x0F;         // Store valueDAC[11..8] to temp[3..0]
  temp |= 0x30;                          // Define DAC setting, see MCP4921 datasheet
  Soft_SPI_Write(temp);                  // Send high byte via Soft SPI

  // Send Low Byte
  temp = valueDAC;                       // Store valueDAC[7..0] to temp[7..0]
  Soft_SPI_Write(temp);                  // Send low byte via Soft SPI

  Chip_Select = 1;                       // Deselect DAC chip
}

void main() {

  ANSELA  = 0;                            // Configure AN pins as digital
  ANSELC = 0;
  
  InitMain();                            // Perform main initialization

  value = 2048;                          // When program starts, DAC gives
                                         //   the output in the mid-range

  while (1) {                            // Endless loop

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