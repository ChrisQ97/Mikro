/*
 * Project name:
     SetjmpDemo (Example on using the mikroC's setjmp library)
 * Copyright:
     (c) mikroElektronika
 * Revision History:
     20061127:
       - initial release;
 * Description:
     Example demonstrates function cross calling using setjmp and longjmp functions.
     When called, Setjmp() saves its calling environment in its jmp_buf argument
     for later use by the Longjmp().
     Longjmp(), on the other hand, restores the environment saved by the most
     recent invocation of the Setjmp() with the corresponding jmp_buf argument.

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
     -  Invocation of Longjmp must occur before return from the function in which
        Setjmp was called encounters.
     -  Due to pic16 family specific of not being able to read/write stack pointer,
        the program execution after Longjmp ivocation occurs depends on the
        stack content. That is why, for pic16 family only, implementation of
        Setjmp and Longjmp functions is not ANSI C standard compliant.
 */

#include <setjmp16.h>

jmp_buf buf;             // Note: Program flow diagrams are indexed according
                         //       to the sequence of execution

void func33(){           //  2<----------|
  Delay_ms(1000);        //              |
                         //              |
  asm nop;               //              |
  longjmp(buf, 2);       //  3-------------->|
  asm nop;               //              |   |
                         //              |   |
}                        //              |   |
                         //              |   |
void func(){             //  1<------|   |   |
                         //          |   |   |
  PORTB = 3;             //          |   |   |
  if (setjmp(buf) == 2)  //  3<--------------|
    PORTB = 1;           //  4-->|   |   |
  else                   //      |   |   |
    func33();            //  2---------->|
                         //      |   |
  asm nop;               //  4<--|   |
}                        //  5-------|------->   depends on stack content
                         //          |
void main() {            //          |
                         //          |
  PORTB = 0;             //          |
  TRISB = 0;             //          |
                         //          |
  asm nop;               //          |
                         //          |
  func();                //  1------>|
                         //
  asm nop;               //
  Delay_ms(1000);
  PORTB = 0xFF;
}