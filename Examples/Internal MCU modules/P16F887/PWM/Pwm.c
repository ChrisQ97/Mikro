/*
 * Project name:
     PWM (PWM library Demonstration)
 * Copyright:
     (c) MikroElektronika, 2005-2008
 * Description:
     This is a simple demonstration of PWM library, which is being used for
     control of the PIC's CCP module. The module is initialized and started,
     after which the PWM1 ans PWM2 Duty Ratios can be adjusted by means of 4 buttons
     connected to pins RA0, RA1, RA2 and RA3. The changes can be monitored on the CCP
     output pins (RC1 and RC2).
 * Test configuration:
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Pull-down PORTA and connect button jumper (J17) to Vcc.
     - Turn on LEDs on PORTC SW9.3 (board specific)
*/

unsigned short current_duty, old_duty, current_duty1, old_duty1;

void InitMain() {
  ANSEL  = 0;                         // Configure AN pins as digital
  ANSELH = 0;
  C1ON_bit = 0;                       // Disable comparators
  C2ON_bit = 0;
  
  PORTA = 255;
  TRISA = 255;                        // configure PORTA pins as input
  PORTB = 0;                          // set PORTB to 0
  TRISB = 0;                          // designate PORTB pins as output
  PORTC = 0;                          // set PORTC to 0
  TRISC = 0;                          // designate PORTC pins as output
  PWM1_Init(5000);                    // Initialize PWM1 module at 5KHz
  PWM2_Init(5000);                    // Initialize PWM2 module at 5KHz
}

void main() {
  InitMain();
  current_duty  = 16;                 // initial value for current_duty
  current_duty1 = 16;                 // initial value for current_duty1

  PWM1_Start();                       // start PWM1
  PWM2_Start();                       // start PWM2
  PWM1_Set_Duty(current_duty);        // Set current duty for PWM1
  PWM2_Set_Duty(current_duty1);       // Set current duty for PWM2

  while (1) {                         // endless loop
    if (RA0_bit) {                    // button on RA0 pressed
      Delay_ms(40);
      current_duty++;                 // increment current_duty
      PWM1_Set_Duty(current_duty);
     }

    if (RA1_bit) {                    // button on RA1 pressed
      Delay_ms(40);
      current_duty--;                 // decrement current_duty
      PWM1_Set_Duty(current_duty);
     }

    if (RA2_bit) {                    // button on RA2 pressed
      Delay_ms(40);
      current_duty1++;                // increment current_duty1
      PWM2_Set_Duty(current_duty1);
     }

    if (RA3_bit) {                    // button on RA3 pressed
      Delay_ms(40);
      current_duty1--;                // decrement current_duty1
      PWM2_Set_Duty(current_duty1);
     }

    Delay_ms(5);                      // slow down change pace a little
  }
}