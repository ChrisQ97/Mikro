/*
 * Project name:
     TouchPanelCalibration (Demo for working with TouchPanel Controller)
 * Copyright:
     (c) Mikroelektronika, 2011.
 * Revision History:
     20120116:
       - initial release (JK);
 * Description:
     This code works with TouchPanel and GLCD. Two digital output and
     two analog input signals are used for communication with TouchPanel.
     The example shows how to calibrate touch panel and prints aquired 
     calibration constants on GLCD.
 * Test configuration:
     MCU:             PIC18F87K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39960b.pdf
     dev.board:       easypic pro v7 - ac:GLCD
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS-PLL 64.0000 MHz, 16.0000 MHz Crystal
     Ext. Modules:    GLCD 128x64, Touch Panel
                      http://www.mikroe.com/store/components/various/
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * Notes:
     - Turn on GLCD backlight switch SW4.2. (board specific)
     - Turn on TouchPanel Controller switches SW4.5, SW4.6, SW4.7 and SW4.8. (board specific)
     - Turn OFF PORTF LEDs SW6.6. (board specific)
 */

// Glcd module connections
char GLCD_DataPort at PORTD;

sbit GLCD_CS1 at LATB0_bit;
sbit GLCD_CS2 at LATB1_bit;
sbit GLCD_RS  at LATB2_bit;
sbit GLCD_RW  at LATB3_bit;
sbit GLCD_EN  at LATB4_bit;
sbit GLCD_RST at LATB5_bit;

sbit GLCD_CS1_Direction at TRISB0_bit;
sbit GLCD_CS2_Direction at TRISB1_bit;
sbit GLCD_RS_Direction  at TRISB2_bit;
sbit GLCD_RW_Direction  at TRISB3_bit;
sbit GLCD_EN_Direction  at TRISB4_bit;
sbit GLCD_RST_Direction at TRISB5_bit;
// End Glcd module connections

// Touch Panel module connections
sbit DriveA at LATE4_bit;
sbit DriveB at LATE5_bit;
sbit DriveA_Direction at TRISE4_bit;
sbit DriveB_Direction at TRISE5_bit;
sbit ReadX_Direction at TRISF2_bit;
sbit ReadY_Direction at TRISF5_bit;
// End Touch Panel module connections

const char msg1[] = "TOUCH BOTTOM LEFT";
const char msg2[] = "                 ";
const char msg3[] = "TOUCH UPPER RIGHT";
const char msg4[] = "CALIBRATION";
const char msg5[] = "Calibration constants";
char msg[22];

unsigned int x_min, y_min, x_max, y_max;           // Calibration constants

char x_min_msg[] = "X min:";                       // GLCD text messages
char y_min_msg[] = "Y min:";
char x_max_msg[] = "X max:";
char y_max_msg[] = "Y max:";

char x_min_val[6];                                 // Calibration constants string values
char y_min_val[6];
char x_max_val[6];
char y_max_val[6];

// copy const to ram string
char * CopyConst2Ram(char * dest, const char * src){
  char * d ;
  d = dest;
  for(;*dest++ = *src++;)
    ;
  return d;
}

void Initialize() {
  ANSEL7_bit  = 1;             // Configure AN7 and AN10 pins as analog
  ANSEL10_bit = 1;
  ReadX_Direction = 1;         // Configure AN7 and AN10 pins as input
  ReadY_Direction = 1;

  Glcd_Init();                 // Initialize GLCD
  Glcd_Fill(0);                // Clear GLCD
  
  CON_bit = 0;
  ADC_Init();                  // Initialize ADC
  TP_Init(128, 64, 10, 7);     // Initialize touch panel
  TP_Set_ADC_Threshold(900);   // Set touch panel ADC threshold
}

void Calibrate() {

  Glcd_Dot(0,63,1);                                // Draw bottom left dot
  Glcd_Write_Text(CopyConst2Ram(msg,msg1),12,3,1);
  TP_Calibrate_Bottom_Left();                      // Calibration of bottom left corner
  Delay_ms(1000);

  Glcd_Dot(0,63,0);                                // Clear bottom left dot
  Glcd_Dot(127,0,1);                               // Draw upper right dot
  Glcd_Write_Text(CopyConst2Ram(msg,msg2),12,3,1);
  Glcd_Write_Text(CopyConst2Ram(msg,msg3),12,4,1);
  TP_Calibrate_Upper_Right();                      // Calibration of upper right corner

  Delay_ms(1000);
}

void main() {

  Initialize();

  Glcd_Write_Text(CopyConst2Ram(msg,msg4),32,3,1);
  Delay_ms(1000);
  Glcd_Fill(0);                                    // Clear GLCD
  Calibrate();

  TP_Get_Calibration_Consts(&x_min, &x_max, &y_min, &y_max); // Get calibration constants

  WordToStr(x_min, x_min_val);                             // Convert calibration constants into string values
  WordToStr(x_max, x_max_val);
  WordToStr(y_min, y_min_val);
  WordToStr(y_max, y_max_val);

  // Display Calibration constants on GLCD
  
  Glcd_Fill(0);                                            // Clear GLCD
  Glcd_Write_Text(CopyConst2Ram(msg,msg5),1,1,1);
  Glcd_Write_Text(x_min_msg,1,3,1);                        // Write messages on GLCD
  Glcd_Write_Text(x_max_msg,1,4,1);
  Glcd_Write_Text(y_min_msg,1,5,1);
  Glcd_Write_Text(y_max_msg,1,6,1);

  Glcd_Write_Text(x_min_val,50,3,1);                       // Write calibration constants values on GLCD
  Glcd_Write_Text(x_max_val,50,4,1);
  Glcd_Write_Text(y_min_val,50,5,1);
  Glcd_Write_Text(y_max_val,50,6,1);

}