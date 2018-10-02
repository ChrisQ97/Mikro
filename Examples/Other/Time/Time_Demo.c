/*
 * Project Name:
     Time_Demo (simplified c-like time library)
 * Copyright:
     (c) Mikroelektronika, 2008.
 * Revision History:
     20080930:
       - initial release; Author: Bruno Gavand.
 * Description  :
     Just run it in watch window and watch appropriate variables.
 * Test configuration:
     MCU:             PIC16F887
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41291F.pdf
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     None.
 */

#include        "timelib.h"

TimeStruct ts1, ts2 ;
long epoch ;
long diff ;


void main() {

  ts1.ss = 0 ;
  ts1.mn = 7 ;
  ts1.hh = 17 ;
  ts1.md = 23 ;
  ts1.mo = 5 ;
  ts1.yy = 2006 ;

  /*
   * What is the epoch of the date in ts ?
   */
  epoch = Time_dateToEpoch(&ts1) ;       //  1148404020


  /*
   * What date is epoch 1234567890 ?
   */
  epoch = 1234567890 ;
  Time_epochToDate(epoch, &ts2) ;       //  {0x1E, 0x1F,0x17, 0x0D, 0x04, 0x02, 0x07D9}

  /*
   * How much seconds between this two dates ?
   */
  diff = Time_dateDiff(&ts1, &ts2) ;    //  86163870
}