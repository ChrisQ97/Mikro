/*
 * Project Name:
     enc28j60Demo (Ethernet Library demo for ENC28J60 mcu)
 * Target Platform:
     PIC
 * Copyright:
     (c) MikroElektronika, 2012
 * Revision History:
     20060810:
       - Initial release. Author: Bruno Gavand.
 *
 * V1.0 : first release
 * V1.1 : bad MIME type for / path request, changed to HTML instead of SCRIPT (thanks Srdjan !)
 *
 * description  :
 *      this code shows how to use the Spi_Ethernet mini library :
 *              the board will reply to ARP & ICMP echo requests
 *              the board will reply to UDP requests on any port :
 *                      returns the request in upper char with a header made of remote host IP & port number
 *              the board will reply to HTTP requests on port 80, GET method with pathnames :
 *                      /               will return the HTML main page
 *                      /s              will return board status as text string
 *                      /t0 ... /t7     will toggle RD0 to RD7 bit and return HTML main page
 *                      all other requests return also HTML main page
 *
 * target devices :
 *      any PIC with integrated SPI and more than 4 Kb ROM memory
 *      32 to 40 MHz clock is recommended to get from 8 to 10 Mhz SPI clock,
 *      otherwise PIC should be clocked by ENC clock output due to ENC silicon bug in SPI hardware
 *      if you try lower PIC clock speed, don't be surprised if the board hang or miss some requests !
 *
 * EP settings :
 *      AN2 & AN3  pots jumper on Potentiometer Board : closed
 *      RA5   : pull-down  (PortA three-state switch)  (board specific)
 *      PORTB : pull-down  (PortB three-state switch)  (board specific)
 *
 *      RC0 : !RESET    to ENC reset input pin
 *      RC1 : !CS       to ENC chip select input pin
 *      the ENC28J60 SPI bus CLK, SO, SI must be connected to the corresponding SPI pins of the PIC
 *      the INT and WOL signals from the ENC are not used
 * Test configuration:
     MCU:             PIC18F45K22
                      http://ww1.microchip.com/downloads/en/DeviceDoc/41412D.pdf
     Dev.Board:       EasyPIC7
                      http://www.mikroe.com/easypic/
     Oscillator:      HS-PLL, 32.00000 MHz
     Ext. Modules:    ac:Serial_Ethernet_Board
                      ac:Potentiometer_Board
     SW:              mikroC PRO for PIC
                      http://www.mikroe.com/mikroc/pic/
 * NOTES:
     - Since the ENC28J60 doesn't support auto-negotiation, full-duplex mode is
       not compatible with most switches/routers.  If a dedicated network is used
       where the duplex of the remote node can be manually configured, you may
       change this configuration.  Otherwise, half duplex should always be used.
     - External power supply should be used due to Serial Ethernet Board power consumption.
 */

// duplex config flags
#include  "__EthEnc28j60.h"

#define Spi_Ethernet_HALFDUPLEX     0x00  // half duplex
#define Spi_Ethernet_FULLDUPLEX     0x01  // full duplex

// mE ehternet NIC pinout
sfr sbit SPI_Ethernet_Rst at LATC0_bit;  // for writing to output pin always use latch (PIC18 family)
sfr sbit SPI_Ethernet_CS  at LATC1_bit;  // for writing to output pin always use latch (PIC18 family)
sfr sbit SPI_Ethernet_Rst_Direction at TRISC0_bit;
sfr sbit SPI_Ethernet_CS_Direction  at TRISC1_bit;
// end ethernet NIC definitions


/************************************************************
 * ROM constant strings
 */
const code unsigned char httpHeader[] = "HTTP/1.1 200 OK\nContent-type: " ;  // HTTP header
const code unsigned char httpMimeTypeHTML[] = "text/html\n\n" ;              // HTML MIME type
const code unsigned char httpMimeTypeScript[] = "text/plain\n\n" ;           // TEXT MIME type
unsigned char httpMethod[] = "GET /";
/*
 * web page, splited into 2 parts :
 * when coming short of ROM, fragmented data is handled more efficiently by linker
 *
 * this HTML page calls the boards to get its status, and builds itself with javascript
 */
const code   char    *indexPage =                   // Change the IP address of the page to be refreshed
"<meta http-equiv=\"refresh\" content=\"3;url=http://192.168.20.60\">\
<HTML><HEAD></HEAD><BODY>\
<h1>PIC + ENC28J60 Mini Web Server</h1>\
<a href=/>Reload</a>\
<script src=/s></script>\
<table><tr><td valign=top><table border=1 style=\"font-size:20px ;font-family: terminal ;\">\
<tr><th colspan=2>ADC</th></tr>\
<tr><td>AN2</td><td><script>document.write(AN2)</script></td></tr>\
<tr><td>AN3</td><td><script>document.write(AN3)</script></td></tr>\
</table></td><td><table border=1 style=\"font-size:20px ;font-family: terminal ;\">\
<tr><th colspan=2>PORTB</th></tr>\
<script>\
var str,i;\
str=\"\";\
for(i=0;i<8;i++)\
{str+=\"<tr><td bgcolor=pink>BUTTON #\"+i+\"</td>\";\
if(PORTB&(1<<i)){str+=\"<td bgcolor=red>ON\";}\
else {str+=\"<td bgcolor=#cccccc>OFF\";}\
str+=\"</td></tr>\";}\
document.write(str) ;\
</script>\
" ;

const code   char    *indexPage2 =  "</table></td><td>\
<table border=1 style=\"font-size:20px ;font-family: terminal ;\">\
<tr><th colspan=3>PORTD</th></tr>\
<script>\
var str,i;\
str=\"\";\
for(i=0;i<8;i++)\
{str+=\"<tr><td bgcolor=yellow>LED #\"+i+\"</td>\";\
if(PORTD&(1<<i)){str+=\"<td bgcolor=red>ON\";}\
else {str+=\"<td bgcolor=#cccccc>OFF\";}\
str+=\"</td><td><a href=/t\"+i+\">Toggle</a></td></tr>\";}\
document.write(str) ;\
</script>\
</table></td></tr></table>\
This is HTTP request #<script>document.write(REQ)</script></BODY></HTML>\
" ;

/***********************************
 * RAM variables
 */
unsigned char   myMacAddr[6] = {0x00, 0x14, 0xA5, 0x76, 0x19, 0x3f} ;   // my MAC address
unsigned char   myIpAddr[4]  = {192, 168,  20, 60 } ;                   // my IP address
unsigned char   gwIpAddr[4]  = {192, 168,  20, 66 } ;                   // gateway (router) IP address
unsigned char   ipMask[4]    = {255, 255, 255,  0 } ;                   // network mask (for example : 255.255.255.0)
unsigned char   dnsIpAddr[4] = {192, 168,  20,  1 } ;                   // DNS server IP address

unsigned char   getRequest[15] ;                                        // HTTP request buffer
unsigned char   dyna[29] ;                                              // buffer for dynamic response
unsigned long   httpCounter = 0 ;                                       // counter of HTTP requests

/*******************************************
 * functions
 */

/*
 * put the constant string pointed to by s to the ENC transmit buffer.
 */
/*unsigned int    putConstString(const code char *s)
        {
        unsigned int ctr = 0 ;

        while(*s)
                {
                Spi_Ethernet_putByte(*s++) ;
                ctr++ ;
                }
        return(ctr) ;
        }*/
/*
 * it will be much faster to use library Spi_Ethernet_putConstString routine
 * instead of putConstString routine above. However, the code will be a little
 * bit bigger. User should choose between size and speed and pick the implementation that
 * suites him best. If you choose to go with the putConstString definition above
 * the #define line below should be commented out.
 *
 */
#define putConstString  SPI_Ethernet_putConstString

/*
 * put the string pointed to by s to the ENC transmit buffer
 */
/*unsigned int    putString(char *s)
        {
        unsigned int ctr = 0 ;

        while(*s)
                {
                Spi_Ethernet_putByte(*s++) ;

                ctr++ ;
                }
        return(ctr) ;
        }*/
/*
 * it will be much faster to use library Spi_Ethernet_putString routine
 * instead of putString routine above. However, the code will be a little
 * bit bigger. User should choose between size and speed and pick the implementation that
 * suites him best. If you choose to go with the putString definition above
 * the #define line below should be commented out.
 *
 */
#define putString  SPI_Ethernet_putString

/*
 * this function is called by the library
 * the user accesses to the HTTP request by successive calls to Spi_Ethernet_getByte()
 * the user puts data in the transmit buffer by successive calls to Spi_Ethernet_putByte()
 * the function must return the length in bytes of the HTTP reply, or 0 if nothing to transmit
 *
 * if you don't need to reply to HTTP requests,
 * just define this function with a return(0) as single statement
 *
 */
unsigned int  SPI_Ethernet_UserTCP(unsigned char *remoteHost, unsigned int remotePort, unsigned int localPort, unsigned int reqLength, TEthPktFlags *flags)
        {
        unsigned int    len;            // my reply length

        // should we close tcp socket after response is sent?
        // library closes tcp socket by default if canClose flag is not reset here
        // *canClose = 0; // 0 - do not close socket
                          // otherwise - close socket

        if(localPort != 80)                         // I listen only to web request on port 80
                {
                return(0) ;
                }

        // get 10 first bytes only of the request, the rest does not matter here
        for(len = 0 ; len < 10 ; len++)
        {
        getRequest[len] = SPI_Ethernet_getByte() ;
        }
        getRequest[len] = 0 ;
        len = 0;

        if(memcmp(getRequest, httpMethod, 5))       // only GET method is supported here
                {
                return(0) ;
                }

        httpCounter++ ;                             // one more request done

        if(getRequest[5] == 's')                    // if request path name starts with s, store dynamic data in transmit buffer
                {
                // the text string replied by this request can be interpreted as javascript statements
                // by browsers

                len = putConstString(httpHeader) ;              // HTTP header
                len += putConstString(httpMimeTypeScript) ;     // with text MIME type

                // add AN2 value to reply
                WordToStr(ADC_Read(2), dyna) ;
                len += putConstString("var AN2=") ;
                len += putString(dyna) ;
                len += putConstString(";") ;

                // add AN3 value to reply
                WordToStr(ADC_Read(3), dyna) ;
                len += putConstString("var AN3=") ;
                len += putString(dyna) ;
                len += putConstString(";") ;

                // add PORTB value (buttons) to reply
                len += putConstString("var PORTB=") ;
                WordToStr(PORTB, dyna) ;
                len += putString(dyna) ;
                len += putConstString(";") ;

                // add PORTD value (LEDs) to reply
                len += putConstString("var PORTD=") ;
                WordToStr(PORTD, dyna) ;
                len += putString(dyna) ;
                len += putConstString(";") ;

                // add HTTP requests counter to reply
                WordToStr(httpCounter, dyna) ;
                len += putConstString("var REQ=") ;
                len += putString(dyna) ;
                len += putConstString(";") ;
                }
        else if(getRequest[5] == 't')                           // if request path name starts with t, toggle PORTD (LED) bit number that comes after
                {
                unsigned char   bitMask = 0 ;                   // for bit mask

                if(isdigit(getRequest[6]))                      // if 0 <= bit number <= 9, bits 8 & 9 does not exist but does not matter
                        {
                        bitMask = getRequest[6] - '0' ;         // convert ASCII to integer
                        bitMask = 1 << bitMask ;                // create bit mask
                        LATD ^= bitMask ;                      // toggle PORTD with xor operator
                        }
                }

        if(len == 0)                                            // what do to by default
                {
                len =  putConstString(httpHeader) ;             // HTTP header
                len += putConstString(httpMimeTypeHTML) ;       // with HTML MIME type
                len += putConstString(indexPage) ;              // HTML page first part
                len += putConstString(indexPage2) ;             // HTML page second part
                }

        return(len) ;                                           // return to the library with the number of bytes to transmit
        }

/*
 * this function is called by the library
 * the user accesses to the UDP request by successive calls to Spi_Ethernet_getByte()
 * the user puts data in the transmit buffer by successive calls to Spi_Ethernet_putByte()
 * the function must return the length in bytes of the UDP reply, or 0 if nothing to transmit
 *
 * if you don't need to reply to UDP requests,
 * just define this function with a return(0) as single statement
 *
 */
unsigned int  SPI_Ethernet_UserUDP(unsigned char *remoteHost, unsigned int remotePort, unsigned int destPort, unsigned int reqLength, TEthPktFlags *flags)
        {
        unsigned int    len ;                           // my reply length

        // reply is made of the remote host IP address in human readable format
        ByteToStr(remoteHost[0], dyna) ;                // first IP address byte
        dyna[3] = '.' ;
        ByteToStr(remoteHost[1], dyna + 4) ;            // second
        dyna[7] = '.' ;
        ByteToStr(remoteHost[2], dyna + 8) ;            // third
        dyna[11] = '.' ;
        ByteToStr(remoteHost[3], dyna + 12) ;           // fourth

        dyna[15] = ':' ;                                // add separator

        // then remote host port number
        WordToStr(remotePort, dyna + 16) ;
        dyna[21] = '[' ;
        WordToStr(destPort, dyna + 22) ;
        dyna[27] = ']' ;
        dyna[28] = 0 ;

        // the total length of the request is the length of the dynamic string plus the text of the request
        len = 28 + reqLength;

        // puts the dynamic string into the transmit buffer
        SPI_Ethernet_putBytes(dyna, 28) ;

        // then puts the request string converted into upper char into the transmit buffer
        while(reqLength--)
                {
                SPI_Ethernet_putByte(toupper(SPI_Ethernet_getByte())) ;
                }

        return(len) ;           // back to the library with the length of the UDP reply
        }

/*
 * main entry
 */
void    main()
        {
        ANSELA = 0x0C;          // ADC convertors will be used with AN2 and AN3
        ANSELB = 0;
        ANSELC = 0;
        ANSELD = 0;

        PORTA = 0 ;
        TRISA = 0xff ;          // set PORTA as input for ADC

        PORTB = 0 ;
        TRISB = 0xff ;          // set PORTB as input for buttons

        LATD  = 0 ;
        TRISD = 0 ;             // set PORTD as output

        SLRCON = 0;             // Set output slew rate on all ports at standard rate

        /*
         * starts ENC28J60 with :
         * reset bit on RC0
         * CS bit on RC1
         * my MAC & IP address
         * full duplex
         */
        SPI1_Init();
        SPI_Rd_Ptr = SPI1_Read;
        SPI_Ethernet_Init(myMacAddr, myIpAddr, Spi_Ethernet_FULLDUPLEX) ;

        // dhcp will not be used here, so use preconfigured addresses
        SPI_Ethernet_confNetwork(ipMask, gwIpAddr, dnsIpAddr) ;

        while(1)                            // do forever
                {
                /*
                 * if necessary, test the return value to get error code
                 */
                SPI_Ethernet_doPacket() ;   // process incoming Ethernet packets

                /*
                 * add your stuff here if needed
                 * Spi_Ethernet_doPacket() must be called as often as possible
                 * otherwise packets could be lost
                 */
                }
        }