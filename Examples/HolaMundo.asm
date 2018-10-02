
_configurar:

;HolaMundo.c,1 :: 		void configurar(){
;HolaMundo.c,2 :: 		TRISD = 0;
	CLRF        TRISD+0 
;HolaMundo.c,3 :: 		PORTD = 0;
	CLRF        PORTD+0 
;HolaMundo.c,4 :: 		INTCON = 0xC0;
	MOVLW       192
	MOVWF       INTCON+0 
;HolaMundo.c,5 :: 		INTCON2 = 0x04;
	MOVLW       4
	MOVWF       INTCON2+0 
;HolaMundo.c,6 :: 		T0CON = 0x03;
	MOVLW       3
	MOVWF       T0CON+0 
;HolaMundo.c,7 :: 		TMR0L = 0xDB;
	MOVLW       219
	MOVWF       TMR0L+0 
;HolaMundo.c,8 :: 		TMR0H = 0x0B;
	MOVLW       11
	MOVWF       TMR0H+0 
;HolaMundo.c,9 :: 		T0IE_bit=1;
	BSF         T0IE_bit+0, BitPos(T0IE_bit+0) 
;HolaMundo.c,10 :: 		TMR0ON_bit = 1;
	BSF         TMR0ON_bit+0, BitPos(TMR0ON_bit+0) 
;HolaMundo.c,12 :: 		}
L_end_configurar:
	RETURN      0
; end of _configurar

_interrupt:

;HolaMundo.c,13 :: 		void interrupt(){
;HolaMundo.c,14 :: 		TMR0ON_bit =0;
	BCF         TMR0ON_bit+0, BitPos(TMR0ON_bit+0) 
;HolaMundo.c,15 :: 		T0IE_bit = 0;
	BCF         T0IE_bit+0, BitPos(T0IE_bit+0) 
;HolaMundo.c,16 :: 		T0IF_bit = 0;
	BCF         T0IF_bit+0, BitPos(T0IF_bit+0) 
;HolaMundo.c,17 :: 		TMR0L = 0xDB;
	MOVLW       219
	MOVWF       TMR0L+0 
;HolaMundo.c,18 :: 		TMR0H = 0x0B;
	MOVLW       11
	MOVWF       TMR0H+0 
;HolaMundo.c,19 :: 		RD0_bit = !(RD0_bit);
	BTG         RD0_bit+0, BitPos(RD0_bit+0) 
;HolaMundo.c,21 :: 		T0IE_bit = 1;
	BSF         T0IE_bit+0, BitPos(T0IE_bit+0) 
;HolaMundo.c,22 :: 		T0CON = 0x83;
	MOVLW       131
	MOVWF       T0CON+0 
;HolaMundo.c,24 :: 		}
L_end_interrupt:
L__interrupt4:
	RETFIE      1
; end of _interrupt

_main:

;HolaMundo.c,25 :: 		void main() {
;HolaMundo.c,26 :: 		configurar();
	CALL        _configurar+0, 0
;HolaMundo.c,27 :: 		TMR0ON_bit = 1;
	BSF         TMR0ON_bit+0, BitPos(TMR0ON_bit+0) 
;HolaMundo.c,28 :: 		while(1);
L_main0:
	GOTO        L_main0
;HolaMundo.c,29 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
