
_configurar:

;MyProject.c,8 :: 		void configurar()
;MyProject.c,10 :: 		TRISD =   0;                          // Colocamos todo el puerto D de salida
	CLRF        TRISD+0 
;MyProject.c,11 :: 		PORTD =   0;                          // Inicializamos el puerto D
	CLRF        PORTD+0 
;MyProject.c,13 :: 		TRISA =   0xFF;                       // Colocamos todo el puerto A como entrada
	MOVLW       255
	MOVWF       TRISA+0 
;MyProject.c,14 :: 		PORTA =   0;                          // Inicializamos el puerto A
	CLRF        PORTA+0 
;MyProject.c,16 :: 		INTCON =  0xC0;                       // Habilitamos todas las interrupciones unmasked en el bit 7 y las interrupciones unmasked perifericas en el bit 6
	MOVLW       192
	MOVWF       INTCON+0 
;MyProject.c,19 :: 		T0CON = 0x68;                         // Encendemos el bit 6, 5 y 3 en el TMR0. 6 = Contador de 8 bits. 5 = Se ubica externamente en el pin T0CKI. 3 = NO usa valores de prescala
	MOVLW       104
	MOVWF       T0CON+0 
;MyProject.c,20 :: 		TMR0L = 0xFF;                         // Colocamos el timer con un valor inicial de 255 para que asi solo cuente 1 hasta llegar al desbordamiento en 256
	MOVLW       255
	MOVWF       TMR0L+0 
;MyProject.c,21 :: 		TMR0IE_bit = 1;                       // Activamos la opcion de que se sea permitido llamar la interrupcion por overflow
	BSF         TMR0IE_bit+0, BitPos(TMR0IE_bit+0) 
;MyProject.c,22 :: 		TMR0ON_bit = 1;                       // Encendemos el timer
	BSF         TMR0ON_bit+0, BitPos(TMR0ON_bit+0) 
;MyProject.c,25 :: 		TMR1H = 0x0A;                        // Valor inicial de TMR1
	MOVLW       10
	MOVWF       TMR1H+0 
;MyProject.c,26 :: 		TMR1L = 0xFF;
	MOVLW       255
	MOVWF       TMR1L+0 
;MyProject.c,27 :: 		TMR1CS_bit = 0;                      // Utilizamos el contador interno y no uno externo
	BCF         TMR1CS_bit+0, BitPos(TMR1CS_bit+0) 
;MyProject.c,28 :: 		T1CKPS1_bit = T1CKPS0_bit = 1;       // Asignamos una escala de 1:8 poniendo como 1 el bit 5 y 4 de T1CON
	BSF         T1CKPS0_bit+0, BitPos(T1CKPS0_bit+0) 
	BTFSC       T1CKPS0_bit+0, BitPos(T1CKPS0_bit+0) 
	GOTO        L__configurar157
	BCF         T1CKPS1_bit+0, BitPos(T1CKPS1_bit+0) 
	GOTO        L__configurar158
L__configurar157:
	BSF         T1CKPS1_bit+0, BitPos(T1CKPS1_bit+0) 
L__configurar158:
;MyProject.c,29 :: 		TMR1IE_bit = 1;                      // Habilitamos la interrupcion por OVERFLOW del TMR1
	BSF         TMR1IE_bit+0, BitPos(TMR1IE_bit+0) 
;MyProject.c,30 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,31 :: 		}
L_end_configurar:
	RETURN      0
; end of _configurar

_EncenderApagar:

;MyProject.c,33 :: 		EncenderApagar()
;MyProject.c,35 :: 		externa = 0;
	CLRF        _externa+0 
	CLRF        _externa+1 
;MyProject.c,36 :: 		continuar = 0;                       // Inicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,37 :: 		RD0_bit = 1;                         // Encendemos el led
	BSF         RD0_bit+0, BitPos(RD0_bit+0) 
;MyProject.c,38 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,39 :: 		while (continuar == 0);              // Esperamos el retraso de 1 segundo
L_EncenderApagar0:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__EncenderApagar160
	MOVLW       0
	XORWF       _continuar+0, 0 
L__EncenderApagar160:
	BTFSS       STATUS+0, 2 
	GOTO        L_EncenderApagar1
	GOTO        L_EncenderApagar0
L_EncenderApagar1:
;MyProject.c,40 :: 		RD0_bit = 0;                         // Apagamos el led
	BCF         RD0_bit+0, BitPos(RD0_bit+0) 
;MyProject.c,41 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,42 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,43 :: 		while (continuar == 0);              // Esperamos el retraso de 1 segundo
L_EncenderApagar2:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__EncenderApagar161
	MOVLW       0
	XORWF       _continuar+0, 0 
L__EncenderApagar161:
	BTFSS       STATUS+0, 2 
	GOTO        L_EncenderApagar3
	GOTO        L_EncenderApagar2
L_EncenderApagar3:
;MyProject.c,44 :: 		}
L_end_EncenderApagar:
	RETURN      0
; end of _EncenderApagar

_BasculacionConIncremento:

;MyProject.c,46 :: 		void BasculacionConIncremento()
;MyProject.c,48 :: 		externa = 0;
	CLRF        _externa+0 
	CLRF        _externa+1 
;MyProject.c,49 :: 		repeticiones = 0;
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
;MyProject.c,50 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
L_BasculacionConIncremento4:
	MOVLW       128
	XORWF       _repeticiones+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento163
	MOVLW       2
	SUBWF       _repeticiones+0, 0 
L__BasculacionConIncremento163:
	BTFSC       STATUS+0, 0 
	GOTO        L_BasculacionConIncremento5
;MyProject.c,52 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento164
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento164:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento7
;MyProject.c,53 :: 		SPP0_bit = 1;                        // Encendemos el led
	BSF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,55 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,56 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,57 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento8:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento165
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento165:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento9
	GOTO        L_BasculacionConIncremento8
L_BasculacionConIncremento9:
;MyProject.c,59 :: 		SPP0_bit = 0;                        // Apagamos el led
	BCF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,61 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,62 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,63 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento10:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento166
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento166:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento11
	GOTO        L_BasculacionConIncremento10
L_BasculacionConIncremento11:
;MyProject.c,64 :: 		}
L_BasculacionConIncremento7:
;MyProject.c,50 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	INFSNZ      _repeticiones+0, 1 
	INCF        _repeticiones+1, 1 
;MyProject.c,65 :: 		}
	GOTO        L_BasculacionConIncremento4
L_BasculacionConIncremento5:
;MyProject.c,66 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento167
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento167:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento12
;MyProject.c,67 :: 		SPP0_bit = 1;                             // Encendemos el led
	BSF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,68 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,69 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,70 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento13:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento168
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento168:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento14
	GOTO        L_BasculacionConIncremento13
L_BasculacionConIncremento14:
;MyProject.c,71 :: 		}
L_BasculacionConIncremento12:
;MyProject.c,72 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
L_BasculacionConIncremento15:
	MOVLW       128
	XORWF       _repeticiones+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento169
	MOVLW       2
	SUBWF       _repeticiones+0, 0 
L__BasculacionConIncremento169:
	BTFSC       STATUS+0, 0 
	GOTO        L_BasculacionConIncremento16
;MyProject.c,74 :: 		if(externa != 1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento170
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento170:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento18
;MyProject.c,75 :: 		SPP1_bit = 1;                        // Encendemos el led
	BSF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,77 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,78 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,79 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento19:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento171
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento171:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento20
	GOTO        L_BasculacionConIncremento19
L_BasculacionConIncremento20:
;MyProject.c,81 :: 		SPP1_bit = 0;                        // Apagamos el led
	BCF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,83 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,84 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,85 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento21:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento172
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento172:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento22
	GOTO        L_BasculacionConIncremento21
L_BasculacionConIncremento22:
;MyProject.c,86 :: 		}
L_BasculacionConIncremento18:
;MyProject.c,72 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	INFSNZ      _repeticiones+0, 1 
	INCF        _repeticiones+1, 1 
;MyProject.c,87 :: 		}
	GOTO        L_BasculacionConIncremento15
L_BasculacionConIncremento16:
;MyProject.c,88 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento173
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento173:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento23
;MyProject.c,89 :: 		SPP1_bit = 1;                             // Encendemos el led
	BSF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,90 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,91 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,92 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento24:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento174
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento174:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento25
	GOTO        L_BasculacionConIncremento24
L_BasculacionConIncremento25:
;MyProject.c,93 :: 		}
L_BasculacionConIncremento23:
;MyProject.c,94 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
L_BasculacionConIncremento26:
	MOVLW       128
	XORWF       _repeticiones+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento175
	MOVLW       2
	SUBWF       _repeticiones+0, 0 
L__BasculacionConIncremento175:
	BTFSC       STATUS+0, 0 
	GOTO        L_BasculacionConIncremento27
;MyProject.c,96 :: 		if(externa != 1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento176
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento176:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento29
;MyProject.c,97 :: 		SPP2_bit = 1;                        // Encendemos el led
	BSF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,99 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,100 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,101 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento30:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento177
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento177:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento31
	GOTO        L_BasculacionConIncremento30
L_BasculacionConIncremento31:
;MyProject.c,103 :: 		SPP2_bit = 0;                        // Apagamos el led
	BCF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,105 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,106 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,107 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento32:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento178
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento178:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento33
	GOTO        L_BasculacionConIncremento32
L_BasculacionConIncremento33:
;MyProject.c,108 :: 		}
L_BasculacionConIncremento29:
;MyProject.c,94 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	INFSNZ      _repeticiones+0, 1 
	INCF        _repeticiones+1, 1 
;MyProject.c,109 :: 		}
	GOTO        L_BasculacionConIncremento26
L_BasculacionConIncremento27:
;MyProject.c,110 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento179
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento179:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento34
;MyProject.c,111 :: 		SPP2_bit = 1;                             // Encendemos el led
	BSF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,112 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,113 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,114 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento35:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento180
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento180:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento36
	GOTO        L_BasculacionConIncremento35
L_BasculacionConIncremento36:
;MyProject.c,115 :: 		}
L_BasculacionConIncremento34:
;MyProject.c,116 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
L_BasculacionConIncremento37:
	MOVLW       128
	XORWF       _repeticiones+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento181
	MOVLW       2
	SUBWF       _repeticiones+0, 0 
L__BasculacionConIncremento181:
	BTFSC       STATUS+0, 0 
	GOTO        L_BasculacionConIncremento38
;MyProject.c,118 :: 		if(externa != 1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento182
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento182:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento40
;MyProject.c,119 :: 		SPP3_bit = 1;                        // Encendemos el led
	BSF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,121 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,122 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,123 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento41:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento183
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento183:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento42
	GOTO        L_BasculacionConIncremento41
L_BasculacionConIncremento42:
;MyProject.c,125 :: 		SPP3_bit = 0;                        // Apagamos el led
	BCF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,127 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,128 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,129 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento43:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento184
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento184:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento44
	GOTO        L_BasculacionConIncremento43
L_BasculacionConIncremento44:
;MyProject.c,130 :: 		}
L_BasculacionConIncremento40:
;MyProject.c,116 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	INFSNZ      _repeticiones+0, 1 
	INCF        _repeticiones+1, 1 
;MyProject.c,131 :: 		}
	GOTO        L_BasculacionConIncremento37
L_BasculacionConIncremento38:
;MyProject.c,132 :: 		if(externa!=1)
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento185
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento185:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento45
;MyProject.c,134 :: 		SPP3_bit = 1;                             // Encendemos el led
	BSF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,135 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,136 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,137 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento46:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento186
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento186:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento47
	GOTO        L_BasculacionConIncremento46
L_BasculacionConIncremento47:
;MyProject.c,138 :: 		}
L_BasculacionConIncremento45:
;MyProject.c,140 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
L_BasculacionConIncremento48:
	MOVLW       128
	XORWF       _repeticiones+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento187
	MOVLW       2
	SUBWF       _repeticiones+0, 0 
L__BasculacionConIncremento187:
	BTFSC       STATUS+0, 0 
	GOTO        L_BasculacionConIncremento49
;MyProject.c,142 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento188
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento188:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento51
;MyProject.c,143 :: 		SPP4_bit = 1;                        // Encendemos el led
	BSF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,145 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,146 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,147 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento52:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento189
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento189:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento53
	GOTO        L_BasculacionConIncremento52
L_BasculacionConIncremento53:
;MyProject.c,149 :: 		SPP4_bit = 0;                        // Apagamos el led
	BCF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,151 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,152 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,153 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento54:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento190
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento190:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento55
	GOTO        L_BasculacionConIncremento54
L_BasculacionConIncremento55:
;MyProject.c,154 :: 		}
L_BasculacionConIncremento51:
;MyProject.c,140 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	INFSNZ      _repeticiones+0, 1 
	INCF        _repeticiones+1, 1 
;MyProject.c,155 :: 		}
	GOTO        L_BasculacionConIncremento48
L_BasculacionConIncremento49:
;MyProject.c,156 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento191
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento191:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento56
;MyProject.c,157 :: 		SPP4_bit = 1;                             // Encendemos el led
	BSF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,158 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,159 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,160 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento57:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento192
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento192:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento58
	GOTO        L_BasculacionConIncremento57
L_BasculacionConIncremento58:
;MyProject.c,161 :: 		}
L_BasculacionConIncremento56:
;MyProject.c,162 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
L_BasculacionConIncremento59:
	MOVLW       128
	XORWF       _repeticiones+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento193
	MOVLW       2
	SUBWF       _repeticiones+0, 0 
L__BasculacionConIncremento193:
	BTFSC       STATUS+0, 0 
	GOTO        L_BasculacionConIncremento60
;MyProject.c,164 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento194
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento194:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento62
;MyProject.c,165 :: 		SPP5_bit = 1;                        // Encendemos el led
	BSF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,167 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,168 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,169 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento63:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento195
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento195:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento64
	GOTO        L_BasculacionConIncremento63
L_BasculacionConIncremento64:
;MyProject.c,171 :: 		SPP5_bit = 0;                        // Apagamos el led
	BCF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,173 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,174 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,175 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento65:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento196
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento196:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento66
	GOTO        L_BasculacionConIncremento65
L_BasculacionConIncremento66:
;MyProject.c,176 :: 		}
L_BasculacionConIncremento62:
;MyProject.c,162 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	INFSNZ      _repeticiones+0, 1 
	INCF        _repeticiones+1, 1 
;MyProject.c,177 :: 		}
	GOTO        L_BasculacionConIncremento59
L_BasculacionConIncremento60:
;MyProject.c,178 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento197
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento197:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento67
;MyProject.c,179 :: 		SPP5_bit = 1;                             // Encendemos el led
	BSF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,180 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,181 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,182 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento68:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento198
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento198:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento69
	GOTO        L_BasculacionConIncremento68
L_BasculacionConIncremento69:
;MyProject.c,183 :: 		}
L_BasculacionConIncremento67:
;MyProject.c,185 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
L_BasculacionConIncremento70:
	MOVLW       128
	XORWF       _repeticiones+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento199
	MOVLW       2
	SUBWF       _repeticiones+0, 0 
L__BasculacionConIncremento199:
	BTFSC       STATUS+0, 0 
	GOTO        L_BasculacionConIncremento71
;MyProject.c,187 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento200
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento200:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento73
;MyProject.c,188 :: 		SPP6_bit = 1;                        // Encendemos el led
	BSF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,190 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,191 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,192 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento74:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento201
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento201:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento75
	GOTO        L_BasculacionConIncremento74
L_BasculacionConIncremento75:
;MyProject.c,194 :: 		SPP6_bit = 0;                        // Apagamos el led
	BCF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,196 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,197 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,198 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento76:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento202
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento202:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento77
	GOTO        L_BasculacionConIncremento76
L_BasculacionConIncremento77:
;MyProject.c,199 :: 		}
L_BasculacionConIncremento73:
;MyProject.c,185 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	INFSNZ      _repeticiones+0, 1 
	INCF        _repeticiones+1, 1 
;MyProject.c,200 :: 		}
	GOTO        L_BasculacionConIncremento70
L_BasculacionConIncremento71:
;MyProject.c,201 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento203
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento203:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento78
;MyProject.c,202 :: 		SPP6_bit = 1;                             // Encendemos el led
	BSF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,203 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,204 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,205 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento79:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento204
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento204:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento80
	GOTO        L_BasculacionConIncremento79
L_BasculacionConIncremento80:
;MyProject.c,206 :: 		}
L_BasculacionConIncremento78:
;MyProject.c,208 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	CLRF        _repeticiones+0 
	CLRF        _repeticiones+1 
L_BasculacionConIncremento81:
	MOVLW       128
	XORWF       _repeticiones+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento205
	MOVLW       2
	SUBWF       _repeticiones+0, 0 
L__BasculacionConIncremento205:
	BTFSC       STATUS+0, 0 
	GOTO        L_BasculacionConIncremento82
;MyProject.c,210 :: 		if(externa!=1){
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento206
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento206:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento84
;MyProject.c,211 :: 		SPP7_bit = 1;                        // Encendemos el led
	BSF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,213 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,214 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,215 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento85:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento207
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento207:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento86
	GOTO        L_BasculacionConIncremento85
L_BasculacionConIncremento86:
;MyProject.c,217 :: 		SPP7_bit = 0;                        // Apagamos el led
	BCF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,219 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,220 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,221 :: 		while (continuar == 0);              // Esperamos el retraso de un segundo
L_BasculacionConIncremento87:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento208
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento208:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento88
	GOTO        L_BasculacionConIncremento87
L_BasculacionConIncremento88:
;MyProject.c,222 :: 		}
L_BasculacionConIncremento84:
;MyProject.c,208 :: 		for (repeticiones = 0; repeticiones < 2; repeticiones ++)
	INFSNZ      _repeticiones+0, 1 
	INCF        _repeticiones+1, 1 
;MyProject.c,223 :: 		}
	GOTO        L_BasculacionConIncremento81
L_BasculacionConIncremento82:
;MyProject.c,224 :: 		if(externa!=1)
	MOVLW       0
	XORWF       _externa+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento209
	MOVLW       1
	XORWF       _externa+0, 0 
L__BasculacionConIncremento209:
	BTFSC       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento89
;MyProject.c,226 :: 		SPP7_bit = 1;                             // Encendemos el led
	BSF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,227 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,228 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,229 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento90:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento210
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento210:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento91
	GOTO        L_BasculacionConIncremento90
L_BasculacionConIncremento91:
;MyProject.c,230 :: 		}
L_BasculacionConIncremento89:
;MyProject.c,233 :: 		SPP0_bit = 0;
	BCF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,234 :: 		SPP1_bit = 0;
	BCF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,235 :: 		SPP2_bit = 0;
	BCF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,236 :: 		SPP3_bit = 0;
	BCF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,237 :: 		SPP4_bit = 0;
	BCF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,238 :: 		SPP5_bit = 0;
	BCF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,239 :: 		SPP6_bit = 0;
	BCF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,240 :: 		SPP7_bit = 0;
	BCF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,243 :: 		continuar = 0;                            // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,244 :: 		TMR1ON_bit = 1;                           // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,245 :: 		while (continuar == 0);                   // Esperamos el retraso de un segundo
L_BasculacionConIncremento92:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__BasculacionConIncremento211
	MOVLW       0
	XORWF       _continuar+0, 0 
L__BasculacionConIncremento211:
	BTFSS       STATUS+0, 2 
	GOTO        L_BasculacionConIncremento93
	GOTO        L_BasculacionConIncremento92
L_BasculacionConIncremento93:
;MyProject.c,246 :: 		}
L_end_BasculacionConIncremento:
	RETURN      0
; end of _BasculacionConIncremento

_CorrimientoDeLedsDeIzquierdaADerecha:

;MyProject.c,248 :: 		void CorrimientoDeLedsDeIzquierdaADerecha()
;MyProject.c,251 :: 		externa = 0;
	CLRF        _externa+0 
	CLRF        _externa+1 
;MyProject.c,252 :: 		SPP0_bit = 1;
	BSF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,253 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,255 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,256 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha94:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha213
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha213:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha95
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha94
L_CorrimientoDeLedsDeIzquierdaADerecha95:
;MyProject.c,258 :: 		SPP0_bit = 0;
	BCF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,259 :: 		SPP1_bit = 1;
	BSF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,260 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,262 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,263 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha96:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha214
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha214:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha97
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha96
L_CorrimientoDeLedsDeIzquierdaADerecha97:
;MyProject.c,265 :: 		SPP1_bit = 0;
	BCF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,266 :: 		SPP2_bit = 1;
	BSF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,267 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,269 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,270 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha98:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha215
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha215:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha99
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha98
L_CorrimientoDeLedsDeIzquierdaADerecha99:
;MyProject.c,272 :: 		SPP2_bit = 0;
	BCF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,273 :: 		SPP3_bit = 1;
	BSF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,274 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,276 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,277 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha100:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha216
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha216:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha101
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha100
L_CorrimientoDeLedsDeIzquierdaADerecha101:
;MyProject.c,279 :: 		SPP3_bit = 0;
	BCF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,280 :: 		SPP4_bit = 1;
	BSF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,281 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,283 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,284 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha102:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha217
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha217:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha103
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha102
L_CorrimientoDeLedsDeIzquierdaADerecha103:
;MyProject.c,286 :: 		SPP4_bit = 0;
	BCF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,287 :: 		SPP5_bit = 1;
	BSF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,288 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,290 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,291 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha104:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha218
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha218:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha105
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha104
L_CorrimientoDeLedsDeIzquierdaADerecha105:
;MyProject.c,293 :: 		SPP5_bit = 0;
	BCF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,294 :: 		SPP6_bit = 1;
	BSF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,295 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,297 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,298 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha106:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha219
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha219:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha107
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha106
L_CorrimientoDeLedsDeIzquierdaADerecha107:
;MyProject.c,300 :: 		SPP6_bit = 0;
	BCF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,301 :: 		SPP7_bit = 1;
	BSF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,302 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,304 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,305 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha108:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha220
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha220:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha109
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha108
L_CorrimientoDeLedsDeIzquierdaADerecha109:
;MyProject.c,307 :: 		SPP7_bit = 0;
	BCF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,308 :: 		SPP6_bit = 1;
	BSF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,309 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,311 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,312 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha110:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha221
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha221:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha111
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha110
L_CorrimientoDeLedsDeIzquierdaADerecha111:
;MyProject.c,315 :: 		SPP6_bit = 0;
	BCF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,316 :: 		SPP5_bit = 1;
	BSF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,317 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,319 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,320 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha112:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha222
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha222:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha113
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha112
L_CorrimientoDeLedsDeIzquierdaADerecha113:
;MyProject.c,322 :: 		SPP5_bit = 0;
	BCF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,323 :: 		SPP4_bit = 1;
	BSF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,324 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,326 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,327 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha114:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha223
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha223:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha115
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha114
L_CorrimientoDeLedsDeIzquierdaADerecha115:
;MyProject.c,329 :: 		SPP4_bit = 0;
	BCF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,330 :: 		SPP3_bit = 1;
	BSF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,331 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,333 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,334 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha116:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha224
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha224:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha117
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha116
L_CorrimientoDeLedsDeIzquierdaADerecha117:
;MyProject.c,336 :: 		SPP3_bit = 0;
	BCF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,337 :: 		SPP2_bit = 1;
	BSF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,338 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,340 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,341 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha118:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha225
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha225:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha119
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha118
L_CorrimientoDeLedsDeIzquierdaADerecha119:
;MyProject.c,343 :: 		SPP2_bit = 0;
	BCF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,344 :: 		SPP1_bit = 1;
	BSF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,345 :: 		continuar = 0;
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,347 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,348 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoDeLedsDeIzquierdaADerecha120:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoDeLedsDeIzquierdaADerecha226
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoDeLedsDeIzquierdaADerecha226:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha121
	GOTO        L_CorrimientoDeLedsDeIzquierdaADerecha120
L_CorrimientoDeLedsDeIzquierdaADerecha121:
;MyProject.c,350 :: 		SPP1_bit = 0;
	BCF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,351 :: 		}
L_end_CorrimientoDeLedsDeIzquierdaADerecha:
	RETURN      0
; end of _CorrimientoDeLedsDeIzquierdaADerecha

_ContadorAutomaticoHasta20:

;MyProject.c,353 :: 		void ContadorAutomaticoHasta20()
;MyProject.c,356 :: 		for (numero = 1; numero <= 20; numero++)
	MOVLW       1
	MOVWF       R1 
	MOVLW       0
	MOVWF       R2 
L_ContadorAutomaticoHasta20122:
	MOVLW       128
	MOVWF       R0 
	MOVLW       128
	XORWF       R2, 0 
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ContadorAutomaticoHasta20228
	MOVF        R1, 0 
	SUBLW       20
L__ContadorAutomaticoHasta20228:
	BTFSS       STATUS+0, 0 
	GOTO        L_ContadorAutomaticoHasta20123
;MyProject.c,358 :: 		PORTD = numero;
	MOVF        R1, 0 
	MOVWF       PORTD+0 
;MyProject.c,359 :: 		continuar = 0;                       // Reinicializamos la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,360 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,361 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_ContadorAutomaticoHasta20125:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ContadorAutomaticoHasta20229
	MOVLW       0
	XORWF       _continuar+0, 0 
L__ContadorAutomaticoHasta20229:
	BTFSS       STATUS+0, 2 
	GOTO        L_ContadorAutomaticoHasta20126
	GOTO        L_ContadorAutomaticoHasta20125
L_ContadorAutomaticoHasta20126:
;MyProject.c,356 :: 		for (numero = 1; numero <= 20; numero++)
	INFSNZ      R1, 1 
	INCF        R2, 1 
;MyProject.c,362 :: 		}
	GOTO        L_ContadorAutomaticoHasta20122
L_ContadorAutomaticoHasta20123:
;MyProject.c,363 :: 		}
L_end_ContadorAutomaticoHasta20:
	RETURN      0
; end of _ContadorAutomaticoHasta20

_CorrimientoImparRegresoPar:

;MyProject.c,365 :: 		void CorrimientoImparRegresoPar()
;MyProject.c,367 :: 		SPP0_bit = 1;                        // Encendemos el led
	BSF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,369 :: 		continuar = 0;                       // Inicializamos el valor de la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,370 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,371 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoImparRegresoPar127:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoImparRegresoPar231
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoImparRegresoPar231:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoImparRegresoPar128
	GOTO        L_CorrimientoImparRegresoPar127
L_CorrimientoImparRegresoPar128:
;MyProject.c,373 :: 		SPP0_bit = 0;                        // Apagamos el led
	BCF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,374 :: 		SPP2_bit = 1;                        // Encendemos el led
	BSF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,376 :: 		continuar = 0;                       // Inicializamos el valor de la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,377 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,378 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoImparRegresoPar129:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoImparRegresoPar232
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoImparRegresoPar232:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoImparRegresoPar130
	GOTO        L_CorrimientoImparRegresoPar129
L_CorrimientoImparRegresoPar130:
;MyProject.c,380 :: 		SPP2_bit = 0;                        // Apagamos el led
	BCF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,381 :: 		SPP4_bit = 1;                        // Encendemos el led
	BSF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,383 :: 		continuar = 0;                       // Inicializamos el valor de la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,384 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,385 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoImparRegresoPar131:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoImparRegresoPar233
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoImparRegresoPar233:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoImparRegresoPar132
	GOTO        L_CorrimientoImparRegresoPar131
L_CorrimientoImparRegresoPar132:
;MyProject.c,387 :: 		SPP4_bit = 0;                        // Apagamos el led
	BCF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,388 :: 		SPP6_bit = 1;                        // Encendemos el led
	BSF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,390 :: 		continuar = 0;                       // Inicializamos el valor de la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,391 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,392 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoImparRegresoPar133:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoImparRegresoPar234
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoImparRegresoPar234:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoImparRegresoPar134
	GOTO        L_CorrimientoImparRegresoPar133
L_CorrimientoImparRegresoPar134:
;MyProject.c,394 :: 		SPP6_bit = 0;                        // Apagamos el led
	BCF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,395 :: 		SPP7_bit = 1;                        // Encendemos el led
	BSF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,397 :: 		continuar = 0;                       // Inicializamos el valor de la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,398 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,399 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoImparRegresoPar135:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoImparRegresoPar235
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoImparRegresoPar235:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoImparRegresoPar136
	GOTO        L_CorrimientoImparRegresoPar135
L_CorrimientoImparRegresoPar136:
;MyProject.c,401 :: 		SPP7_bit = 0;                        // Apagamos el led
	BCF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,402 :: 		SPP5_bit = 1;                        // Encendemos el led
	BSF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,404 :: 		continuar = 0;                       // Inicializamos el valor de la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,405 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,406 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoImparRegresoPar137:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoImparRegresoPar236
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoImparRegresoPar236:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoImparRegresoPar138
	GOTO        L_CorrimientoImparRegresoPar137
L_CorrimientoImparRegresoPar138:
;MyProject.c,408 :: 		SPP5_bit = 0;                        // Apagamos el led
	BCF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,409 :: 		SPP3_bit = 1;                        // Encendemos el led
	BSF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,411 :: 		continuar = 0;                       // Inicializamos el valor de la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,412 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,413 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoImparRegresoPar139:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoImparRegresoPar237
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoImparRegresoPar237:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoImparRegresoPar140
	GOTO        L_CorrimientoImparRegresoPar139
L_CorrimientoImparRegresoPar140:
;MyProject.c,415 :: 		SPP3_bit = 0;                        // Apagamos el led
	BCF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,416 :: 		SPP1_bit = 1;                        // Encendemos el led
	BSF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,418 :: 		continuar = 0;                       // Inicializamos el valor de la variable continuar
	CLRF        _continuar+0 
	CLRF        _continuar+1 
;MyProject.c,419 :: 		TMR1ON_bit = 1;                      // Encendemos el timer de TMR1
	BSF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,420 :: 		while (continuar == 0){}             // Esperamos el retraso de un segundo
L_CorrimientoImparRegresoPar141:
	MOVLW       0
	XORWF       _continuar+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__CorrimientoImparRegresoPar238
	MOVLW       0
	XORWF       _continuar+0, 0 
L__CorrimientoImparRegresoPar238:
	BTFSS       STATUS+0, 2 
	GOTO        L_CorrimientoImparRegresoPar142
	GOTO        L_CorrimientoImparRegresoPar141
L_CorrimientoImparRegresoPar142:
;MyProject.c,422 :: 		SPP1_bit = 0;                        // Apagamos el led
	BCF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,423 :: 		}
L_end_CorrimientoImparRegresoPar:
	RETURN      0
; end of _CorrimientoImparRegresoPar

_ApagarLeds:

;MyProject.c,425 :: 		ApagarLeds()
;MyProject.c,427 :: 		SPP0_bit = 0;
	BCF         SPP0_bit+0, BitPos(SPP0_bit+0) 
;MyProject.c,428 :: 		SPP1_bit = 0;
	BCF         SPP1_bit+0, BitPos(SPP1_bit+0) 
;MyProject.c,429 :: 		SPP2_bit = 0;
	BCF         SPP2_bit+0, BitPos(SPP2_bit+0) 
;MyProject.c,430 :: 		SPP3_bit = 0;
	BCF         SPP3_bit+0, BitPos(SPP3_bit+0) 
;MyProject.c,431 :: 		SPP4_bit = 0;
	BCF         SPP4_bit+0, BitPos(SPP4_bit+0) 
;MyProject.c,432 :: 		SPP5_bit = 0;
	BCF         SPP5_bit+0, BitPos(SPP5_bit+0) 
;MyProject.c,433 :: 		SPP6_bit = 0;
	BCF         SPP6_bit+0, BitPos(SPP6_bit+0) 
;MyProject.c,434 :: 		SPP7_bit = 0;
	BCF         SPP7_bit+0, BitPos(SPP7_bit+0) 
;MyProject.c,435 :: 		}
L_end_ApagarLeds:
	RETURN      0
; end of _ApagarLeds

_ElegirProceso:

;MyProject.c,437 :: 		void ElegirProceso()
;MyProject.c,439 :: 		switch (proceso)
	GOTO        L_ElegirProceso143
;MyProject.c,442 :: 		case 1:
L_ElegirProceso145:
;MyProject.c,443 :: 		EncenderApagar();
	CALL        _EncenderApagar+0, 0
;MyProject.c,444 :: 		break;
	GOTO        L_ElegirProceso144
;MyProject.c,446 :: 		case 2:
L_ElegirProceso146:
;MyProject.c,447 :: 		ApagarLeds();
	CALL        _ApagarLeds+0, 0
;MyProject.c,448 :: 		BasculacionConIncremento();
	CALL        _BasculacionConIncremento+0, 0
;MyProject.c,449 :: 		break;
	GOTO        L_ElegirProceso144
;MyProject.c,451 :: 		case 3:
L_ElegirProceso147:
;MyProject.c,452 :: 		ApagarLeds();
	CALL        _ApagarLeds+0, 0
;MyProject.c,453 :: 		CorrimientoDeLedsDeIzquierdaADerecha();
	CALL        _CorrimientoDeLedsDeIzquierdaADerecha+0, 0
;MyProject.c,454 :: 		break;
	GOTO        L_ElegirProceso144
;MyProject.c,456 :: 		case 4:
L_ElegirProceso148:
;MyProject.c,457 :: 		ApagarLeds();
	CALL        _ApagarLeds+0, 0
;MyProject.c,458 :: 		ContadorAutomaticoHasta20();
	CALL        _ContadorAutomaticoHasta20+0, 0
;MyProject.c,459 :: 		break;
	GOTO        L_ElegirProceso144
;MyProject.c,461 :: 		case 5:
L_ElegirProceso149:
;MyProject.c,462 :: 		ApagarLeds();
	CALL        _ApagarLeds+0, 0
;MyProject.c,463 :: 		CorrimientoImparRegresoPar();
	CALL        _CorrimientoImparRegresoPar+0, 0
;MyProject.c,464 :: 		break;
	GOTO        L_ElegirProceso144
;MyProject.c,466 :: 		case 6:
L_ElegirProceso150:
;MyProject.c,467 :: 		ApagarLeds();
	CALL        _ApagarLeds+0, 0
;MyProject.c,468 :: 		proceso = 0;
	CLRF        _proceso+0 
	CLRF        _proceso+1 
;MyProject.c,469 :: 		break;
	GOTO        L_ElegirProceso144
;MyProject.c,470 :: 		}
L_ElegirProceso143:
	MOVLW       0
	XORWF       _proceso+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ElegirProceso241
	MOVLW       1
	XORWF       _proceso+0, 0 
L__ElegirProceso241:
	BTFSC       STATUS+0, 2 
	GOTO        L_ElegirProceso145
	MOVLW       0
	XORWF       _proceso+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ElegirProceso242
	MOVLW       2
	XORWF       _proceso+0, 0 
L__ElegirProceso242:
	BTFSC       STATUS+0, 2 
	GOTO        L_ElegirProceso146
	MOVLW       0
	XORWF       _proceso+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ElegirProceso243
	MOVLW       3
	XORWF       _proceso+0, 0 
L__ElegirProceso243:
	BTFSC       STATUS+0, 2 
	GOTO        L_ElegirProceso147
	MOVLW       0
	XORWF       _proceso+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ElegirProceso244
	MOVLW       4
	XORWF       _proceso+0, 0 
L__ElegirProceso244:
	BTFSC       STATUS+0, 2 
	GOTO        L_ElegirProceso148
	MOVLW       0
	XORWF       _proceso+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ElegirProceso245
	MOVLW       5
	XORWF       _proceso+0, 0 
L__ElegirProceso245:
	BTFSC       STATUS+0, 2 
	GOTO        L_ElegirProceso149
	MOVLW       0
	XORWF       _proceso+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__ElegirProceso246
	MOVLW       6
	XORWF       _proceso+0, 0 
L__ElegirProceso246:
	BTFSC       STATUS+0, 2 
	GOTO        L_ElegirProceso150
L_ElegirProceso144:
;MyProject.c,471 :: 		}
L_end_ElegirProceso:
	RETURN      0
; end of _ElegirProceso

_interrupt:

;MyProject.c,473 :: 		void interrupt()
;MyProject.c,475 :: 		if (TMR0IF_bit == 1)                   // Si fue una interrupcion debida a TMR0
	BTFSS       TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
	GOTO        L_interrupt151
;MyProject.c,477 :: 		TMR0ON_bit = 0;                    // Apagamos el timer de TMR0
	BCF         TMR0ON_bit+0, BitPos(TMR0ON_bit+0) 
;MyProject.c,478 :: 		TMR0IF_bit = 0;                    // Apagamos la bandera de interrupcion por Overflow de TMR0
	BCF         TMR0IF_bit+0, BitPos(TMR0IF_bit+0) 
;MyProject.c,479 :: 		externa = 1;
	MOVLW       1
	MOVWF       _externa+0 
	MOVLW       0
	MOVWF       _externa+1 
;MyProject.c,480 :: 		TMR0L = 0xFF;                      // Reiniciamos el valor de TMR0
	MOVLW       255
	MOVWF       TMR0L+0 
;MyProject.c,482 :: 		ApagarLeds();
	CALL        _ApagarLeds+0, 0
;MyProject.c,483 :: 		proceso++;                         // Cambiamos de proceso
	INFSNZ      _proceso+0, 1 
	INCF        _proceso+1, 1 
;MyProject.c,485 :: 		TMR0ON_bit = 1;                    // Volvemos a encender el TMR0
	BSF         TMR0ON_bit+0, BitPos(TMR0ON_bit+0) 
;MyProject.c,486 :: 		}
	GOTO        L_interrupt152
L_interrupt151:
;MyProject.c,487 :: 		else if (TMR1IF_bit == 1)              // Si fue una interrupcion debida a TMR1
	BTFSS       TMR1IF_bit+0, BitPos(TMR1IF_bit+0) 
	GOTO        L_interrupt153
;MyProject.c,489 :: 		TMR1ON_bit = 0;                     // Apagamos el timer de TMR1
	BCF         TMR1ON_bit+0, BitPos(TMR1ON_bit+0) 
;MyProject.c,490 :: 		TMR1IF_bit = 0;                     // Apagamos la bandera de interrupcion por Overflow de TMR1
	BCF         TMR1IF_bit+0, BitPos(TMR1IF_bit+0) 
;MyProject.c,492 :: 		TMR1L = 0x00;
	CLRF        TMR1L+0 
;MyProject.c,493 :: 		TMR1H = 0x00;                       // Reiniciamos el valor de TMR1
	CLRF        TMR1H+0 
;MyProject.c,495 :: 		continuar = 1;                      // Permitimos que el programa se continue ejecutando
	MOVLW       1
	MOVWF       _continuar+0 
	MOVLW       0
	MOVWF       _continuar+1 
;MyProject.c,496 :: 		}
L_interrupt153:
L_interrupt152:
;MyProject.c,498 :: 		}
L_end_interrupt:
L__interrupt248:
	RETFIE      1
; end of _interrupt

_main:

;MyProject.c,500 :: 		void main() {
;MyProject.c,501 :: 		configurar();
	CALL        _configurar+0, 0
;MyProject.c,502 :: 		while(1)
L_main154:
;MyProject.c,504 :: 		ElegirProceso();
	CALL        _ElegirProceso+0, 0
;MyProject.c,505 :: 		}
	GOTO        L_main154
;MyProject.c,506 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
