/*
 * Project name:
     RTC_Write (Demonstration on working with the RTC Module and Software I2C routines)
 * Copyright:
     (c) MikroElektronika, 2012
 * Revision History:
     20080930:
       - initial release;
     20111012;
       - revision (JK);
 * Description:
      This project is simple demonstration how to set date and time on PCF8583
      RTC (real-time clock).
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:RTC_Board on PORTC
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
    - Pull-up I2C communication lines (RC3 and RC4)  (PortC three-state switch). (board specific)
    - Turn off PORTC LEDs (SW3.3). (board specific)
    - In order to use the example, address pin A0 of PCF8583 must be set to 0V.
       (on mikroElektronika's RTC module this is done by default)
*/

// Software I2C connections
sbit Soft_I2C_Scl at RC3_bit;
sbit Soft_I2C_Sda at RC4_bit;
sbit Soft_I2C_Scl_Direction at TRISC3_bit;
sbit Soft_I2C_Sda_Direction at TRISC4_bit;
// End Software I2C connections

void main() {
   ANSELC = 0;
   
   //Delay_ms(1000);
   Soft_I2C_Init();       // Initialize full master mode
   Soft_I2C_Start();      // Issue start signal
   Soft_I2C_Write(0xA0);  // Address PCF8583, see PCF8583 datasheet
   Soft_I2C_Write(0);     // Start from address 0 (configuration memory location)
   Soft_I2C_Write(0x80);  // Write 0x80 to configuration memory location (pause counter...)
   Soft_I2C_Write(0);     // Write 0 to cents memory location
   Soft_I2C_Write(0);     // Write 0 to seconds memory location
   Soft_I2C_Write(0x30);  // Write 0x30 to minutes memory location
   Soft_I2C_Write(0x12);  // Write 0x12 to hours memory location
   Soft_I2C_Write(0x52);  // Write 0x52 to year/date memory location
   Soft_I2C_Write(0x10);  // Write 0x10 to weekday/month memory location
   Soft_I2C_Stop();       // Issue stop signal

   Soft_I2C_Start();      // Issue start signal
   Soft_I2C_Write(0xA0);  // Address PCF8530
   Soft_I2C_Write(0);     // Start from address 0
   Soft_I2C_Write(0);     // Write 0 to configuration memory location (enable counting)
   Soft_I2C_Stop();       // Issue stop signal
}