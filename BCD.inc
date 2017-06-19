
;------------------------------------------------------------------------------
;
;	Funktionen zur Umwandlung von BCD-Zahlen
;
;	Filename:		BCD.inc
;	Date:			02/2010
;	Version:		1.0
;	Target:			hD2 / ATxmega 128A1
;	Author:			mj, ACMC
;	Support-Email:	acmc@hs-mittweida.de
;	
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Variablen
;------------------------------------------------------------------------------
.dseg

val_signed16:	.byte 2
val_bin8:		.byte 1
bcd2:			.byte 1
bcd1:			.byte 1
bcd0:			.byte 1
bcd:			.byte 1
ascii1:			.byte 1
ascii0:			.byte 1


.cseg

;------------------------------------------------------------------------------
;
;			Umwandlung eines vorzeichenbehafteten (signed) 16-bit-Wert
;			in gepacktes BCD-Format	(3 Byte)
;
;			/param:		val_signed16 -> vorzeichenbehafteter Wert (16bit)
;										(-32768 ... +32767)
;
;			/return:	bcd2:bcd1:bcd0 -> BCD-Zahl (3 Byte)				
;						
;					Format:	bcd2:	Vorzeichen:Zehntausender 
;							bcd1:	Tausender:Hunderter
;							bcd0:	Zehner:Einer
;								
;							Vorzeichen=1: negativ
;							Vorzeichen=0: positiv
;					
;			(Wandlungs-Algorithmus von 
;					http://www.mikrocontroller.net/topic/14305#98412)
;
;------------------------------------------------------------------------------				

SIGNED16_TO_BCD:
	push r24
	push r25
	push r18
	push r19

	clr r19
	
	; 16-bit-Wert laden
	lds r24, val_signed16		; Low-Byte laden
	lds r25, val_signed16+1		; High-Byte laden

	
	; Prüfen auf Vorzeichen
	sbrs r25, 7
	rjmp _BCD0		; wenn positiv, springe

	; Wert ist negativ
	com r24			; Zweierkomplement bilden
	com r25
	adiw r24, 1
	; BCD-Vorzeichen
	ldi r19, 0x10	; Vorzeichen=1


	; Wert ist positiv bzw. wurde durch Zweierkomplement positiv
	; in BCD-Format wandeln
_BCD0:					; Zehntausenderstelle
	ldi	r18, -1 				; Zählvariable (Zehntausenderstelle) vorladen
_BCD1:	
	inc	r18						; Zehntausenderstelle erhöhen
	subi r24, low(10000)		; subtrahiere 10000
	sbci r25, high(10000)		; bis Wert negativ wird
	brcc _BCD1					
	
	or r18, r19			; Vorzeichen und Zehntausenderstelle verknüpfen
	sts bcd2, r18		; speichern nach bcd2

						; Tausenderstelle
	ldi	r18, 10					; Zählvariable (Tausenderstelle) vorladen
_BCD2:	
	dec	r18						; verringere Tausenderstelle
	subi r24, low(-1000)		; addiere 1000
	sbci r25, high(-1000)		; bis Wert positiv wird
	brcs _BCD2	
						
						; Hunderterstelle
	ldi	r19, -1					; Zählvariable vorladen
_BCD3:	
	inc	r19						; erhöhe Hunderterstelle
	subi r24, low(100)			; subtrahiere 100
	sbci r25, high(100)			; bis Wert negativ wird
	brcc _BCD3			

	lsl r18				; Tausenderstelle 4 Bit nach links schieben
	lsl r18
	lsl r18
	lsl r18
	or r18, r19			; Tausender- und Hunderterstelle verknüpfen
	sts bcd1, r18		; speichern nach bcd1

						; Zehnerstelle
	ldi	r18, 10					; Zählvariable vorladen
_BCD4:	
	dec	r18						; verringere Zehnerstelle
	subi r24, -10				; addiere 10
	brcs _BCD4					; bis Wert positiv wird

	lsl r18				; Zehnerstelle  4 Bit nach links
	lsl r18
	lsl r18
	lsl r18
	or r18, r24			; Zehner- und Einerstelle verknüpfen
	sts bcd0, r18		; speichen nach bcd0
	; Wandlung abgeschlossen

	pop r19
	pop r18
	pop r25
	pop r24
	
	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;
;			Umwandlung 8-Bit Binärzahl (unsigned) in gepacktes BCD-Format
;
;			/param:		val_bin8 -> Binärzahl (8bit)
;
;			/return:	bcd1:bcd0 -> BCD-Zahl (2 Byte)				
;						
;					Format:	bcd1:	0000:Hunderter
;							bcd0:	Zehner:Einer
;
;------------------------------------------------------------------------------							

BIN8_TO_BCD:
	push r16
	push r17

	lds r17, val_bin8		; Binärzahl laden	

						; Hunderterstelle
	ldi	r16, -1					; Zählvariable vorladen
_BCD5:	
	inc	r16						; erhöhe Hunderterstelle
	subi r17, low(100)			; subtrahiere 100
	brcc _BCD5					; bis Wert negativ wird
	
	sts bcd1, r16				; speichern nach bcd1
				
						; Zehnerstelle
	ldi	r16, 10					; Zählvariable vorladen
_BCD6:	
	dec	r16						; verringere Zehnerstelle
	subi r17, -10				; addiere 10
	brcs _BCD6					; bis Wert positiv wird

	lsl r16				; Zehnerstelle  4 Bit nach links
	lsl r16
	lsl r16
	lsl r16
	or r16, r17			; Zehner- und Einerstelle verknüpfen
	sts bcd0, r16		; speichen nach bcd0
	; Wandlung abgeschlossen	

	pop r17
	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;
;			Umwandlung gepackte BCD-Zahl in 8-Bit Binärzahl
;
;			/param:		bcd1:bcd0 -> BCD-Zahl (max. 255) (2 Byte)
;
;						Format:	bcd1:	0000:Hunderter
;								bcd0:	Zehner:Einer
;
;			/return:	val_bin8 -> Binärzahl (8bit)
;
;------------------------------------------------------------------------------

BCD_TO_BIN8:
	push r0
	push r1
	push r16
	push r17

	ldi r16, 10			; 10 für Multiplikation Zehnerstelle
	mov r0, r16
	
	lds r16, bcd0		; BCD-Zahl (Zehner:Einer) laden
	ldi r17, 0x0F		
	and r17, r16		; Einerstelle selektieren

	lsr r16				; Zehnerstelle 4 mal nach rechts schieben
	lsr r16
	lsr r16
	lsr r16

	mul r16, r0			; Zehnerstelle * 10
	add r17, r0			; Zehner + Einer 


	ldi r16, 100		; 100 für Multiplikation Hunderterstelle
	mov r0, r16

	lds r16, bcd1		; BCD-Zahl (Hunderter) laden
	andi r16, 0x0F

	mul r16, r0			; Hunderterstelle * 100
	add r17, r0			; Hunderter + (Zehner + Einer) = Binärzahl

	sts val_bin8, r17	; speichern nach val_bin8

	pop r17
	pop r16
	pop r1
	pop r0

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;
;			Umwandlung gepackte BCD-Zahl in ASCII-Code
;			
;			/param:		bcd -> BCD-Zahl, gepackt (8bit)
;		
;			/return:	ascii1 -> ASCII-Code High-Nibble der BCD-Zahl (8bit)
;						ascii0 -> ASCII-Code Low-Nibble der BCD-Zahl (8bit)
;
;------------------------------------------------------------------------------

BCD_TO_ASCII:
	push r16
	push r17
	
	ldi r17, '0'		; ASCII-Code für '0'
	
				; High-Nibble
	lds r16, bcd		; BCD-Zahl laden
	lsr r16				; 4 mal nach rechts schieben (nur High-Nibble nutzen)
	lsr r16
	lsr r16
	lsr r16	
	add r16, r17		; '0' + BCD-High-Nibble = ASCII-Code High-Nibble
	sts ascii1, r16		; speichern nach ascii1

				; Low-Nibble
	lds r16, bcd		; BCD-Zahl erneut laden
	andi r16, 0x0F		; nur Low-Nibble nutzen
	add r16, r17		; '0' + BCD-LOW-Nibble = ASCII-Code Low-Nibble
	sts ascii0, r16		; speichern nach ascii0


	pop r17
	pop r16

	ret
;------------------------------------------------------------------------------



