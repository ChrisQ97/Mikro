/*
 * Project name:
     PWM (PWM library Demonstration)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20081218:
       - initial release;
 * Description:
     This is a simple demonstration of PWM library, which is being used for
     control of the MCU's PWM module. The module is initialized and started,
     after which the PWM1 ans PWM2 Duty Ratios can be adjusted by means of 4 buttons
     connected to pins RA0, RA1, RA2 and RA3. The changes can be monitored
     on the PWM output pins.
 * Test configuration:
     MCU:             PIC18F87J60
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39762d.pdf
     Dev.Board:       EasyPIC PRO v7
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS, 25.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Connect button jumper (J12) to Vcc
       and pull-down PORTA (place jumper J1 in lower position). (board specific)
     - Turn on LEDs on PORTC switch SW10.3. (board specific)
*/

unsigned short current_duty1, old_duty1, current_duty2, old_duty2;

void InitMain() {

  ADCON1 |= 0x0F;                     // Configure AN pins as digital
  CMCON  |= 7;                        // Disable comparators

  PORTA = 0;
  TRISA = 255;                        // configure PORTA pins as input
  PWM1_Init(5000);                    // Initialize PWM1 module at 5KHz
  PWM2_Init(5000);                    // Initialize PWM2 module at 5KHz
}

void main() {
  InitMain();
  current_duty1  = 127;               // initial value for current_duty1
  current_duty2 = 127;                // initial value for current_duty2

  PWM1_Start();                       // start PWM1
  PWM2_Start();                       // start PWM2
  PWM1_Set_Duty(current_duty1);       // Set current duty for PWM1
  PWM2_Set_Duty(current_duty2);       // Set current duty for PWM2

  while (1) {                         // endless loop
    if (RA0_bit) {                    // button on RA0 pressed
      current_duty1--;                // decrement current_duty1
      PWM1_Set_Duty(current_duty1);
     }

    if (RA1_bit) {                    // button on RA1 pressed
      current_duty1++;                // increment current_duty1
      PWM1_Set_Duty(current_duty1);
     }

    if (RA2_bit) {                    // button on RA2 pressed
      current_duty2--;                // decrement current_duty2
      PWM2_Set_Duty(current_duty2);
     }

    if (RA3_bit) {                    // button on RA3 pressed
      current_duty2++;                // increment current_duty2
      PWM2_Set_Duty(current_duty2);
     }

    Delay_ms(5);                      // slow down change pace a little
  }
}
