/*
 * Project name:
     Conversions
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release;
 * Description:
     This program demonstrates usage of mikroC Conversion library routines. 
     Compile and run the code through software simulator.
 * Test configuration:
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - None.
*/

char res_ch;
int  res_int;
char txt[14];

void main() {
  char txt1[] = " mikroelektronika  ";
  char txt_sub[10] = " mikroe  ";
  
  Rtrim(txt1);
  Ltrim(txt_sub);

  ByteToStr(234,txt);
  WordToStr(432,txt);
  WordToStr(5679,txt);
  WordToStr(0xFFFF,txt);
  ShortToStr(12,txt);
  ShortToStr(-1,txt);
  ShortToStr(-127,txt);
  IntToStr(1224,txt);
  IntToStr(-1,txt);
  IntToStr(-12787,txt);
  LongWordToStr(12,txt);
  LongWordToStr(0xFFFFFFFF,txt);
  LongToStr(12,txt);
  LongToStr(-1,txt);
  LongToStr(0x7FFFFFFF,txt);

  FloatToStr(123.567,txt);
  FloatToStr(-123.567,txt);
  FloatToStr(14.67e12,txt);
  FloatToStr(89.77e-5,txt);
  FloatToStr(-14.67e12,txt);
  FloatToStr(-89.77e-5,txt);

  ByteToHex(2, txt);
  ByteToHex(255, txt);

  ShortToHex(-100, txt);    // txt is '9C'
  ShortToHex(100, txt);     // txt is '64'
  WordToHex(1111, txt);     // txt is '0457'

  IntToHex(-32768, txt);    // txt is '8000'
  IntToHex(32767, txt);     // txt is '7FFF'

  LongIntToHex(-2147483648, txt);     // txt is '80000000'
  LongIntToHex(2147483647, txt);      // txt is '7FFFFFFF'
  LongWordToHex(65535, txt);          // txt is '0000FFFF'
  LongWordToHex(4294967295, txt);     // txt is 'FFFFFFFF'

  WordToStrWithZeros(437, txt);       // txt is '00437'
  IntToStrWithZeros(-3276, txt);      // txt is '-03276'
  IntToStrWithZeros(-1, txt);         // txt is '-00001'

  LongWordToStrWithZeros(12345678, txt);    // txt is '0012345678'
  LongIntToStrWithZeros(-12345678, txt);    // txt is '-0012345678'

  res_ch  = Dec2Bcd(23);
  res_int = Dec2Bcd16(2345);
  res_int = Bcd2Dec16(0x4325);

}