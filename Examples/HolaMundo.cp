#line 1 "C:/Users/Public/Documents/Mikroelektronika/mikroC PRO for PIC/Examples/HolaMundo.c"
void configurar(){
 TRISD = 0;
 PORTD = 0;
 INTCON = 0xC0;
 INTCON2 = 0x04;
 T0CON = 0x03;
 TMR0L = 0xDB;
 TMR0H = 0x0B;
 T0IE_bit=1;
 TMR0ON_bit = 1;

}
void interrupt(){
 TMR0ON_bit =0;
 T0IE_bit = 0;
 T0IF_bit = 0;
 TMR0L = 0xDB;
 TMR0H = 0x0B;
 RD0_bit = !(RD0_bit);

 T0IE_bit = 1;
 T0CON = 0x83;

}
void main() {
 configurar();
 TMR0ON_bit = 1;
 while(1);
}
