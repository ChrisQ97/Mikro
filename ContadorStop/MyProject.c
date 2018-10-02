int contador;
int ejecuta;
   int var;
void configurar()
{
     ADCON1 = 0xFF;
     TRISB = 0xFF;
     TRISD =0;
     PORTD=0;
     PORTB = 0;
     INTCON = 0xD0;
     INTCON2 = 0xF4;
     contador =0;
     ejecuta =0;
}
void interrupt(){
     if(INT0IF_bit==1){
      INT0IF_bit = 0;
      if(ejecuta==0) ejecuta=1;
      else  ejecuta = 0;
      
     }

}
void main() {
     configurar();

     do{


               while(ejecuta){
               PORTD=contador;
               if (contador<=255) contador++;
               else contador =0;
               for(var =0;var<5000;var++){
               }
               }
     }while(1);

}