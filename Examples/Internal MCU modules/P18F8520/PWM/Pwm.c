/*
 * Project name:
     PWM (PWM library Demonstration)
 * Copyright:
     (c) MikroElektronika, 2005-2008
 * Description:
     This is a simple demonstration of PWM library, which is being used for
     control of the PIC's CCP module. The module is initialized and started,
     after which the PWM4 ans PWM5 Duty Ratios can be adjusted by means of 4 buttons
     connected to pins RA0, RA1, RA2 and RA3. The changes can be monitored on the CCP
     output pins (RG3 and RG4).
 * Test configuration:
     MCU:             P18F8520
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39609b.pdf
     Dev.Board:       EasyPIC PRO v7
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS, 10.0 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Place jumper J12 to upper position, connect buttons to VCC. (board specific)
     - Pull down PORTA
     - Turn on LEDs on PORTG SW10.6 (board specific)
*/

unsigned short current_duty, old_duty, current_duty1, old_duty1;

void InitMain() {
  ADCON1 |= 0x0F;                     // Configure AN pins as digital
  CMCON  |= 7;                        // Disable comparators

  PORTA = 0;
  TRISA = 255;                        // configure PORTA pins as input
  PORTG = 0;                          // set PORTG to 0
  TRISG = 0;                          // designate PORTG pins as output
  PWM4_Init(5000);                    // Initialize PWM4 module at 5KHz
  PWM5_Init(5000);                    // Initialize PWM5 module at 5KHz
}

void main() {
  InitMain();
  current_duty  = 16;                 // initial value for current_duty
  current_duty1 = 16;                 // initial value for current_duty1

  PWM4_Start();                       // start PWM4
  PWM5_Start();                       // start PWM5
  PWM4_Set_Duty(current_duty);        // Set current duty for PWM4
  PWM5_Set_Duty(current_duty1);       // Set current duty for PWM5

  while (1) {                         // endless loop
    if (RA0_bit) {                    // button on RA0 pressed
      Delay_ms(40);
      current_duty++;                 // increment current_duty
      PWM4_Set_Duty(current_duty);
     }

    if (RA1_bit) {                    // button on RA1 pressed
      Delay_ms(40);
      current_duty--;                 // decrement current_duty
      PWM4_Set_Duty(current_duty);
     }

    if (RA2_bit) {                    // button on RA2 pressed
      Delay_ms(40);
      current_duty1++;                // increment current_duty1
      PWM5_Set_Duty(current_duty1);
     }

    if (RA3_bit) {                    // button on RA3 pressed
      Delay_ms(40);
      current_duty1--;                // decrement current_duty1
      PWM5_Set_Duty(current_duty1);
     }

    Delay_ms(5);                      // slow down change pace a little
  }
}