; Inkludierung Symboldatei
.nolist
.include "ATxmega128A1def.inc"
.list


; notwendige Definitionen

; -----------------------------------------------------------------------------
// notwendiger Sprung von Bootloaderadresse zum Flash - Anfang
.cseg
.org 0x10000					; Adresse des Bootloaders
	jmp	0x000					; Sprung zum Application Flash

; -----------------------------------------------------------------------------
;					Interruptvektortabelle
; -----------------------------------------------------------------------------
.org 0x000						; Flash Adresse 0x0000
	rjmp RESET

	; hier erfolgt der Eintrag von Interruptvektoren
.org PORTH_INT0_vect
	rjmp ISR_PORTH_INT0;
; -----------------------------------------------------------------------------
;                    Beginn des Hauptprogramms
; -----------------------------------------------------------------------------
.org 0x100						; Flash Adresse 0x0100
RESET:
	rcall CLOCK_INIT_16MHZ		; Initialisierung der Taktquelle
	;-------------INTERRUPT---------------
	rcall Interrupt
	;----------------------------
	; Eintrag weiterer Initialisierungen
	rcall Display
	rcall PORT_init
	ldi r19,001
	sts bin8in,r19
; Endlosschleife Hauptprogramm ----------------------------------------------

MAINLOOP:
	; Hier eigenen Programmablauf eintragen
					;Lade Register r16 mit decimalwert 245
				;r16 in bin8in speichern
	rcall bin8tostring		;Funktionsaufruf -> steht in string_var
	rcall DISPLAY_Ausgabe
	rcall LOOP				; Hauptschleife
;------------------------------------------------------------------------------
; 					Unterprogramme
;------------------------------------------------------------------------------
PORT_init:
	ldi		r16,0b00000000		;Maske für PORT lesen/schreiben
	sts		PORTH_DIRSET,r16	;PORTH setzen lesen

	ldi		r16, 0b11111111		;Maske für PORT F	
	sts		PORTF_DIRSET,r16	;PORTF als Ausgang definiert
	ldi		r16, 0b00000010	    ;Maske für PORT F	
	sts		PORTF_OUT,r16
	ret
DISPLAY_Ausgabe:
	;----r16
	;-----string_var
	;lds r17,string_var
	;sts bcd,r17
	;rcall BCD_TO_ASCII
	;-----ascii0,ascii1
	;-----
	ldi ZL, low(string_var)
	ldi ZH,high(string_var)
	ldi r16,low(120)
	sts oled_x_koord, r16
	ldi r16,high(120)
	sts oled_x_koord+1, r16
	ldi r16,50
	sts oled_y_koord,r16
	ldi r16,low(white)
	sts oled_color,r16
	ldi r16,high(white)
	sts oled_color+1,r16
	rcall OLED_PUT_STRING_var
	ret
Interrupt:
	ldi r16,0x01
	sts PORTH_INTCTRL,r16
	ldi r16,0x01
	sts PMIC_CTRL,r16
	ldi r16,0x01
	sts PORTH_INT0MASK,r16
	ldi r16,0x02
	sts PORTH_PIN0CTRL,r16
	sei
	ret
Display:
	rcall OLED_SPI_INIT
	rcall OLED_INIT
	rcall OLED_CLEAR
	ret
ISR_PORTH_INT0:
	lds r19,bin8in
	inc r19
	sts bin8in,r19
	rcall time3
	rcall bin8tostring		;Funktionsaufruf -> steht in string_var
	rcall DISPLAY_Ausgabe
	cpi	r19,11
	breq LED
	reti
LED:
	ldi		r19,0b00000010		    ; lade temp1 mit Bitmaske
	sts		PORTF_OUTTGL,r19		; toggle Pin an PORTF
	rcall	time3					; Zeitverzögerung
	rjmp LED
time1:
	ldi	r20,0x00				; temp1 = 0x00
t1:	dec	r20					; temp1 = temp1 - 1
	brne t1						; wenn Zero Flag nicht gesetzt gehe zu ti01
	ret							; return aus UP
#; Zeitverzögerung2 ------------------------------------------------------------
time2:
	ldi	r21,0x00				; temp2 = 0x00
t2:	rcall time1					; Unterprogrammaufruf "time1"
	dec	r21					; temp2 = temp2 - 1
	brne t2						; wenn Zero Flag nicht gesetzt gehe zu ti02
	ret							; return aus UP					; return aus UP
LOOP:
	rjmp LOOP
; Zeitverzögerung3 ------------------------------------------------------------
time3:
	ldi	r22,0x20				; temp3 = 0x32
t3:	rcall time2					; Unterprogrammaufruf "time1"
	dec	r22					; temp3 = temp3 - 1
	brne t3						; wenn Zero Flag nicht gesetzt gehe zu ti03
	ret							; return aus UP						; return aus UP


;------------------------------------------------------------------------------
; notwendige Includes ---------------------------------------------------------
.nolist
.include "Systemtakt.inc"
.include "bin8tostring.inc"
.include "bcd.inc"
.include "OLED_Funktionen.inc"
.list
