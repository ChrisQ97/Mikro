/*
 * Project name:
     Sound_Var (Usage of Sound library)
 * Copyright:
     (c) Mikroelektronika, 2011.
 * Revision History:
     20120116:
       - initial release (JK);
 * Description:
     This project is a simple demonstration of how to
     use sound library for playing tones on a piezo speaker.
 * Test configuration:
     MCU:             PIC18F87K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/39960b.pdf
     dev.board:       easypic pro v7adc :  ac:Piezo
                      http://www.mikroe.com/easypic-pro/
     Oscillator:      HS-PLL 64.0000 MHz, 16.0000 MHz Crystal
     Ext. Modules:    None.
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Put Button Press Level on PortD to Vcc possition (Three State Switch)
       pull-down pins RD7...RD3 on PORTD. (PortD Three State Switch)
     - Turn on Buzzer on SW4.4
 */

void Tone1() {
  Sound_Play(659, 250);   // Frequency = 659Hz, duration = 250ms
}

void Tone2() {
  Sound_Play(698, 250);   // Frequency = 698Hz, duration = 250ms
}

void Tone3() {
  Sound_Play(784, 250);   // Frequency = 784Hz, duration = 250ms
}

void Melody() {           // Plays the melody "Yellow house"
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3();
  Tone1(); Tone2(); Tone3(); Tone3();
  Tone1(); Tone2(); Tone3();
  Tone3(); Tone3(); Tone2(); Tone2(); Tone1();
}

void ToneA() {
  Sound_Play( 880, 50);
}
void ToneC() {
  Sound_Play(1046, 50);
}
void ToneE() {
  Sound_Play(1318, 50);
}

void Melody2() {
  unsigned short i;
  for (i = 9; i > 0; i--) {
    ToneA(); ToneC(); ToneE();
  }
}

void main() {
  ANCON0 = 0;                        // Configure PORT pins as digital
  ANCON1 = 0;
  ANCON2 = 0;

  TRISD  = 0xF8;                     // Configure RD7..RD3 as input

  Sound_Init(&PORTB, 6);
  Sound_Play(880, 1000);             // Play sound at 880Hz for 1 second

  while (1) {
    if (Button(&PORTD,7,1,1))        // RD7 plays Tone1
      Tone1();
    while (RD7_bit) ;                // Wait for button to be released

    if (Button(&PORTD,6,1,1))        // RD6 plays Tone2
      Tone2();
    while (RD6_bit) ;                // Wait for button to be released

    if (Button(&PORTD,5,1,1))        // RD5 plays Tone3
      Tone3();
    while (RD5_bit) ;                // Wait for button to be released

    if (Button(&PORTD,4,1,1))        // RD4 plays Melody2
      Melody2();
    while (RD4_bit) ;                // Wait for button to be released

    if (Button(&PORTD,3,1,1))        // RD3 plays Melody
      Melody();
    while (RD3_bit) ;                // Wait for button to be released
  }
}