/*
 * Project name:
     RTC_Read (Demonstration on working with the RTC Module and Software I2C routines)
 * Copyright:
     (c) MikroElektronika, 2012.
 * Revision History:
     20080930:
       - initial release;
     20111012;
       - revision (JK);
 * Description:
      This project is simple demonstration how to read date and time from
      PCF8583 RTC (real-time clock).
      Date and time are read from the RTC every 1 second and printed on LCD.
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:RTC_Board on PORTC
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Pull-up I2C communication lines (RC3 and RC4)  (PortC three-state switch) (board specific)
     - Turn off PORTC LEDs (SW3.3). (board specific)
     - In order to use the example, address pin A0 of PCF8583 must be set to 0V.
       (on mikroElektronika's RTC module this is done by default)
*/

char seconds, minutes, hours, day, month, year;    // Global date/time variables

// Software I2C connections
sbit Soft_I2C_Scl           at RC3_bit;
sbit Soft_I2C_Sda           at RC4_bit;
sbit Soft_I2C_Scl_Direction at TRISC3_bit;
sbit Soft_I2C_Sda_Direction at TRISC4_bit;
// End Software I2C connections

// LCD module connections
sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;
// End LCD module connections

//--------------------- Reads time and date information from RTC (PCF8583)
void Read_Time() {

  Soft_I2C_Start();               // Issue start signal
  Soft_I2C_Write(0xA0);           // Address PCF8583, see PCF8583 datasheet
  Soft_I2C_Write(2);              // Start from address 2
  Soft_I2C_Start();               // Issue repeated start signal
  Soft_I2C_Write(0xA1);           // Address PCF8583 for reading R/W=1
  
  seconds = Soft_I2C_Read(1);     // Read seconds byte
  minutes = Soft_I2C_Read(1);     // Read minutes byte
  hours = Soft_I2C_Read(1);       // Read hours byte
  day = Soft_I2C_Read(1);         // Read year/day byte
  month = Soft_I2C_Read(0);       // Read weekday/month byte
  Soft_I2C_Stop();                // Issue stop signal
  
}

//-------------------- Formats date and time
void Transform_Time() {
  seconds  =  ((seconds & 0xF0) >> 4)*10 + (seconds & 0x0F);  // Transform seconds
  minutes  =  ((minutes & 0xF0) >> 4)*10 + (minutes & 0x0F);  // Transform months
  hours    =  ((hours & 0xF0)  >> 4)*10  + (hours & 0x0F);    // Transform hours
  year     =   (day & 0xC0) >> 6;                             // Transform year
  day      =  ((day & 0x30) >> 4)*10    + (day & 0x0F);       // Transform day
  month    =  ((month & 0x10)  >> 4)*10 + (month & 0x0F);     // Transform month
}

//-------------------- Output values to LCD
void Display_Time() {

   Lcd_Chr(1, 6, (day / 10)   + 48);    // Print tens digit of day variable
   Lcd_Chr(1, 7, (day % 10)   + 48);    // Print oness digit of day variable
   Lcd_Chr(1, 9, (month / 10) + 48);
   Lcd_Chr(1,10, (month % 10) + 48);
   Lcd_Chr(1,15,  year        + 48);    // Print year variable  (start from year 2010)


   Lcd_Chr(2, 6, (hours / 10)   + 48);
   Lcd_Chr(2, 7, (hours % 10)   + 48);
   Lcd_Chr(2, 9, (minutes / 10) + 48);
   Lcd_Chr(2,10, (minutes % 10) + 48);
   Lcd_Chr(2,12, (seconds / 10) + 48);
   Lcd_Chr(2,13, (seconds % 10) + 48);
}


//------------------ Performs project-wide init
void Init_Main() {

  TRISB = 0;
  LATB = 0xFF;
  TRISB = 0xff;
  ANSELB  = 0;                // Configure AN pins as digital I/O
  ANSELC = 0;
  
  Soft_I2C_Init();           // Initialize Soft I2C communication
  Lcd_Init();                // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);       // Clear LCD display
  Lcd_Cmd(_LCD_CURSOR_OFF);  // Turn cursor off

  Lcd_Out(1,1,"Date:");      // Prepare and output static text on LCD
  Lcd_Chr(1,8,'.');
  Lcd_Chr(1,11,'.');
  Lcd_Chr(1,16,'.');
  Lcd_Out(2,1,"Time:");
  Lcd_Chr(2,8,':');
  Lcd_Chr(2,11,':');
  Lcd_Out(1,12,"201");       // start from year 2010
}

//----------------- Main procedure
void main() {
  Delay_ms(500);
   
  Init_Main();               // Perform initialization

  while (1) {                // Endless loop
    Read_Time();             // Read time from RTC(PCF8583)
    Transform_Time();        // Format date and time
    Display_Time();          // Prepare and display on LCD
  }
}