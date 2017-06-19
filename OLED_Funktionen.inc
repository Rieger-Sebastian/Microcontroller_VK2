
;------------------------------------------------------------------------------
;
;	Funktionen zur Verwendung des OLED Display
;
;	Filename:		OLED_Funktionen.inc
;	Date:			01/2010
;	Version:		1.0
;	Target:			hD2 / ATxmega 128A1
;	Author:			mj, ACMC
;	Support-Email:	acmc@hs-mittweida.de
;	
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Konstantendefinition
;------------------------------------------------------------------------------
.equ oled_spi_portdir = PORTE_DIR
.equ oled_spi_portout = PORTE_OUT
.equ oled_spi_ctrlreg = SPIE_CTRL
.equ oled_spi_datareg = SPIE_DATA
.equ oled_spi_statusreg = SPIE_STATUS

.equ BLACK = 0x0000
.equ WHITE = 0xFFFF
.equ RED = 0xF800
.equ GREEN = 0x07E0
.equ BLUE = 0x001F
.equ YELLOW = 0xFFE0


;------------------------------------------------------------------------------
;			Variablen
;------------------------------------------------------------------------------
.dseg

oled_x_koord:		.byte 2		; X-Koordinate (16bit)
oled_y_koord:		.byte 1		; Y-Koordinate (8bit)

oled_window_width:	.byte 2		; Fensterbreite (16bit)
oled_window_high:	.byte 1		; Fensterhöhe (8bit)

oled_char:			.byte 1		; ASCII-Code für Zeichen (8bit)

oled_color:			.byte 2		; Farbcode (16bit)



.cseg
;------------------------------------------------------------------------------
;			Init SPI fuer OLED
;
;			/param: no param
;------------------------------------------------------------------------------
OLED_SPI_INIT:
	push r16							; Hilfsregister sichern

	lds r16, oled_spi_portdir	
	ori r16, (0x80 | 0x20 | 0x10)		; SCK-, MOSI-, SS-Pin output
	sts oled_spi_portdir, r16

	ldi r16, 0b01011100					; enable SPI, mode 3, master, 
	sts oled_spi_ctrlreg, r16			; 					prescaler 4

	pop r16								; Hilfsregister wiederherstellen

	ret									; zurück 
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Init OLED Display
;
;			/param: no param			
;------------------------------------------------------------------------------
OLED_INIT:
	push r16
	push r20
	push r21
	push r22

	lds r16, PORTE_DIR
	ori r16, 0x03				; output: OLED_RESET, OLED_POWER
	sts PORTE_DIR, r16		

	lds r16, PORTE_OUT
	andi r16, ~0x01				; OLED POWER disable
	ori r16, (0x10)|(0x02)		; CS- und Reset-Leitung high
	sts PORTE_OUT, r16

	; RESET Sequenz
	rcall _wait_100ms

	lds r16, PORTE_OUT
	andi r16, ~0x02				; Reset-Leitung low
	sts PORTE_OUT, r16
	
	rcall _wait_1ms

	lds r16, PORTE_OUT
	ori r16, 0x02				; Reset-Leitung high
	sts PORTE_OUT, r16
	
	rcall _wait_10ms	

	; Init Sequenz
	ldi r22, 0x03				; Index Entry mode
	ldi r21, 0					; 65k-color mode, ID[1:0]=0, AM=1
	ldi r20, 0x01	
	rcall OLED_SEND_DATA

	ldi r22, 0x10				; Index Standby
	ldi r21, 0					; Standby off
	ldi r20, 0
	rcall OLED_SEND_DATA

	ldi r22, 0x05				; Index display Control
	ldi r21, 0					; Display off
	ldi r20, 0
	rcall OLED_SEND_DATA

	; Gamma settings
	ldi r22, 0x70				; Gamma Top/Bottom R
	ldi r21, 0x2B					
	ldi r20, 0x80
	rcall OLED_SEND_DATA
	ldi r22, 0x71				; Gamma Top/Bottom G
	ldi r21, 0x36					
	ldi r20, 0x00
	rcall OLED_SEND_DATA
	ldi r22, 0x72				; Gamma Top/Bottom B
	ldi r21, 0x3E					
	ldi r20, 0x00
	rcall OLED_SEND_DATA
	ldi r22, 0x73				; Gamma Top/Bottom R1,2
	ldi r21, 0x1F
	ldi r20, 0x19
	rcall OLED_SEND_DATA
	ldi r22, 0x74				; Gamma Top/Bottom R4,4
	ldi r21, 0x22
	ldi r20, 0x14
	rcall OLED_SEND_DATA
	ldi r22, 0x75				; Gamma Top/Bottom G1,2
	ldi r21, 0x22
	ldi r20, 0x1B
	rcall OLED_SEND_DATA
	ldi r22, 0x76				; Gamma Top/Bottom G3,4
	ldi r21, 0x1E					
	ldi r20, 0x16
	rcall OLED_SEND_DATA
	ldi r22, 0x77				; Gamma Top/Bottom B1,2
	ldi r21, 0x24					
	ldi r20, 0xE1
	rcall OLED_SEND_DATA
	ldi r22, 0x78				; Gamma Top/Bottom B3,4
	ldi r21, 0x26					
	ldi r20, 0x17
	rcall OLED_SEND_DATA


	rcall _wait_100ms

	rcall OLED_CLEAR			; clear Display

	lds r16, PORTE_OUT
	ori r16, 0x01				; OLED POWER on
	sts PORTE_OUT, r16

	rcall _wait_10ms
	rcall _wait_10ms
	rcall _wait_10ms
	rcall _wait_10ms

	ldi r22, 0x05				; Index display Control
	ldi r21, 0				
	ldi r20, 0x01				; Display on
	rcall OLED_SEND_DATA

	ldi r16, low(WHITE)			; Farbe vordefinieren
	sts oled_color, r16
	ldi r16, high(WHITE)
	sts oled_color+1, r16
	
	pop r22
	pop r21
	pop r20
	pop r16
	
	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Clear Display
;
;			/param: no param
;------------------------------------------------------------------------------
OLED_CLEAR:
	push r16
	push r17
	push r18
	push r20
	push r21
	push r22
	
	rcall OLED_RESET_WINDOW

	ldi r22, 0x22			; Index write GRAM
	ldi r21, high(BLACK)	; High-Byte RGB-Code (schwarz)
	ldi r20, low(BLACK)		; Low-Byte RGB-Code (schwarz)

	ldi r18, 4				; 240*320 Pixel = 76800 Pixel Farbe setzen (schwarz)
_m01:	
	ldi r17, 100
_m02:	
	ldi r16, 192
_m03:
	rcall OLED_SEND_DATA
	dec r16
	cpi r16, 0
	brne _m03
	dec r17
	cpi r17, 0
	brne _m02
	dec r18
	cpi r18, 0
	brne _m01		

	ldi r16, 0				; reset Cursor
	sts oled_x_koord, r16
	sts oled_x_koord+1, r16
	sts oled_y_koord, r16
	rcall OLED_SET_XY

	pop r22
	pop r21
	pop r20
	pop r18
	pop r17
	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Setzen eines farbigen Pixel
;
;			/param:	oled_x_koord -> X-Koordinate (16bit) (0...319)
;					oled_y_koord -> Y-Koordinate (8bit) (0...239)
;					oled_color -> Farbcode (16bit)		
;------------------------------------------------------------------------------
OLED_SET_PIXEL:
	push r20
	push r21
	push r22

	rcall OLED_SET_XY		; setze Cursor

	ldi r22, 0x22			; Index Write GRAM
	lds r20, oled_color		; Low-Byte RGB-Code
	lds r21, oled_color+1	; High-Byte RGB-Code	
	rcall OLED_SEND_DATA	; sende RGB-Code für Pixel

	pop r22
	pop r21
	pop r20

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Ausgabe eines einzelnen ASCII-Zeichen
;
;			/param:	oled_x_koord -> X-Koordinate obere linke Ecke (16bit) (0...319)
;					oled_y_koord -> Y-Koordinate obere linke Ecke (8bit) (0...239)
;					oled_char -> ASCII-Code für Zeichen (8bit)
;					oled_color -> Farbcode für Zeichen (16bit) 
;------------------------------------------------------------------------------
OLED_PUTC:
	push r0
	push r1
	push r16
	push r17
	push r18
	push r19
	push r20
	push r21
	push r22
	push ZL
	push ZH	

	;......................................................

	; Fenster für Zeichen setzen	
	ldi r16, 8				; Breite = 8
	sts oled_window_width, r16
	ldi r16, 0
	sts oled_window_width+1, r16
	ldi r16, 14				; Höhe = 14
	sts oled_window_high, r16
	rcall OLED_SET_WINDOW	; Fenster setzen
	
	;......................................................

	; prüfen auf nichtdruckbare Zeichen
	lds r18, oled_char	; Zeichen lesen
	cpi r18, 0x20		; Zeichencode < 32?
	brlo _noprint		;	nicht druckbar	
	rjmp _special		; bei druckbaren Zeichen, prüfe auf Sonderzeichen
_noprint:				; wenn nicht druckbar,
	ldi r18, '#'			; Zeichen = #
	rjmp _adress_set	; setze weiter unten fort

	; prüfen auf Sonderzeichen
_special:
	cpi r18, 127	; Zeichencode < 127?
	brlo _adress_set	; wenn ja, normales Zeichen

	cpi r18, 'ä'	; Zeichen = ä?
	brne _oe_small		; wenn nein, prüfe auf nächstes Sonderzeichen
	ldi r18, 127		; wenn ja, Zeichencode = 127
	rjmp _adress_set	; setze weiter unten fort
_oe_small:
	cpi r18, 'ö'	; ö
	brne _ue_small
	ldi r18, 128
	rjmp _adress_set
_ue_small:
	cpi r18, 'ü'	; ü
	brne _ae_big
	ldi r18, 129
	rjmp _adress_set
_ae_big:
	cpi r18, 'Ä'	; Ä
	brne _oe_big
	ldi r18, 130
	rjmp _adress_set
_oe_big:
	cpi r18, 'Ö'	; Ö
	brne _ue_big
	ldi r18, 131
	rjmp _adress_set
_ue_big:
	cpi r18, 'Ü'	; Ü
	brne _sz
	ldi r18, 132
	rjmp _adress_set
_sz:
	cpi r18, 'ß'	; ß
	brne _grad
	ldi r18, 133
	rjmp _adress_set
_grad:
	cpi r18, '°'	; °
	brne _not_in_table
	ldi r18, 134
	rjmp _adress_set	
_not_in_table:
	ldi r18, '#'	; wenn Zeichen nicht in Tabelle, Zeichen = #

	;......................................................
_adress_set:
	; Pointer auf Zeichen in Tabelle
	ldi ZL, low(Font8x14 * 2)	; Pointer Beginn Zeichentabelle
	ldi ZH, high(Font8x14 * 2)

		; Offset berechnen
	subi r18, 0x20	; Zeichen - 32
	ldi r19, 14	
	mul r18, r19	; Offset = (Zeichen - 32) * 14
					;  (Ergebnis in r1:r0)

		; Pointer auf Zeichen	
	add ZL, r0		; addiere Offset zu Pointer
	adc ZH, r1
	;......................................................

	; Zeichen ausgeben
	ldi r22, 0x22	; Index Write GRAM	
	ldi r16, 0		; Liniencounter
		
		; Zeichenlinie lesen
_linie:
	lpm	r19, Z+		; Byte aus Tabelle lesen, Pointer erhöhen

		; einzelne Pixel von Linie setzen
	ldi r17, 0		; Bitcounter
_bit:
	mov r18, r19
	andi r18, 0x80	; Bitweise testen ob 1 oder 0
	cpi r18, 0
	breq _bg_color	; wenn Bit=0: Pixel=Hintergrundfarbe
					; wenn Bit=1: Pixel=Vordergrundfarbe
	lds r20, oled_color		; Vordergrundfarbe
	lds r21, oled_color+1
	rjmp _send
_bg_color:
	ldi r20, low(BLACK)		; Hintergrundfarbe
	ldi r21, high(BLACK)
_send:
	rcall OLED_SEND_DATA	; Pixelfarbe senden
		; nächstes Pixel
	lsl r19			; Zeichen-Byte links schieben
	inc r17			; Bitcounter erhöhen
	cpi r17, 8		; alle Bits fertig?
	brne _bit		; wenn nicht, nächstes Bit

		; nächste Linie	
	inc r16			; Liniencounter erhöhen	
	cpi r16, 14		; alle Linien fertig?
	brne _linie		; wenn nicht, nächste linie
	;......................................................
	
	; Fenster rücksetzen
	lds r17, oled_x_koord	; Koordinaten sichern (wegen Verwendung in PUT_STRING)
	lds r18, oled_x_koord+1
	lds r19, oled_y_koord

	rcall OLED_RESET_WINDOW	; Fenster rücksetzen

	sts oled_x_koord, r17	; Koordinaten wiederherstellen
	sts oled_x_koord+1, r18
	sts oled_y_koord, r19		

	pop ZH
	pop ZL
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18	
	pop r17
	pop r16
	pop r1
	pop r0

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Ausgabe einer konstanten Zeichenkette aus dem Programmspeicher (Flash) 
;
;			/param:	Z -> Zeiger auf auszugebende Zeichenkette im Flash
;					oled_x_koord -> X-Koordinate obere linke Ecke erstes Zeichen (16bit) (0...319)
;					oled_y_koord -> Y-Koordinate (8bit) (0...239)
;					oled_color -> Farbcode (16bit)
;
;			!!! String muss nullterminiert sein !!!
;
;------------------------------------------------------------------------------
OLED_PUT_STRING_const:
	push r16
	push r17
	push r18
	push r19
	push r20
	push r21
	push r22
	push ZL
	push ZH	

	lds r21, oled_x_koord	; X-Koordinate sichern
	lds r22, oled_x_koord+1	

	ldi r16, 8			; Offset X-Koordinate
	ldi r17, 0

_read_char_c:
	lpm r18, Z+			; Zeichen lesen aus Flashspeicher
	
	cpi r18, 0			; Sringende erreicht?
	breq _ret_putstr_c		; wenn ja, Ende

	sts oled_char, r18	; Zeichenübergabe
	rcall OLED_PUTC		; Zeichen ausgeben

	lds r19, oled_x_koord	; X-Koordinate lesen
	lds r20, oled_x_koord+1 
	add r19, r16		; X-Koordinate erhöhen
	adc r20, r17
	sts oled_x_koord, r19	; X-Koordinate überschreiben
	sts oled_x_koord+1, r20

	rjmp _read_char_c	; nächstes Zeichen

_ret_putstr_c:
	sts oled_x_koord, r21	; X-Koordinate wiederherstellen
	sts oled_x_koord+1, r22
	
	pop ZH
	pop ZL
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Ausgabe einer variablen Zeichenkette aus dem Datenspeicher (SRAM) 
;
;			/param:	Z -> Zeiger auf auszugebende Zeichenkette im SRAM
;					oled_x_koord -> X-Koordinate obere linke Ecke erstes Zeichen (16bit) (0...319)
;					oled_y_koord -> Y-Koordinate (8bit) (0...239)
;					oled_color -> Farbcode (16bit)
;
;			!!! String muss nullterminiert sein !!!
;	
;------------------------------------------------------------------------------
OLED_PUT_STRING_var:
	push r16
	push r17
	push r18
	push r19
	push r20
	push r21
	push r22
	push ZL
	push ZH	

	lds r21, oled_x_koord	; X-Koordinate sichern
	lds r22, oled_x_koord+1

	ldi r16, 8			; Offset X-Koordinate
	ldi r17, 0

_read_char_v:
	ld r18, Z+			; Zeichen lesen aus SRAM
	
	cpi r18, 0			; Sringende erreicht?
	breq _ret_putstr_v		; wenn ja, Ende

	sts oled_char, r18	; Zeichenübergabe
	rcall OLED_PUTC		; Zeichen ausgeben

	lds r19, oled_x_koord	; X-Koordinate lesen
	lds r20, oled_x_koord+1 
	add r19, r16		; X-Koordinate erhöhen
	adc r20, r17
	sts oled_x_koord, r19	; X-Koordinate überschreiben
	sts oled_x_koord+1, r20

	rjmp _read_char_v	; nächstes Zeichen

_ret_putstr_v:
	sts oled_x_koord, r21	; X-Koordinate wiederherstellen
	sts oled_x_koord+1, r22
	
	pop ZH
	pop ZL
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r17
	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Set Window
;
;			/param:	oled_x_koord -> X-Koordinate obere linke Ecke (16bit) (0...319)
;					oled_y_koord -> Y-Koordinate obere linke Ecke (8bit) (0...239)
;					oled_window_high -> Fensterhöhe (8bit)
;					oled_window_width -> Fensterbreite (16bit)
;------------------------------------------------------------------------------
OLED_SET_WINDOW:
	push r16
	push r17
	push r20
	push r21
	push r22


	; VEA = 319 - X
	ldi	r21, high(319)		; VEA = 319
	ldi r20, low(319)
	lds r16, oled_x_koord	; X
	lds r17, oled_x_koord+1
	sub r20, r16			; 319 - X
	sbc r21, r17

	ldi r22, 0x36			; Index RAM Position
	rcall OLED_SEND_DATA	; sende VEA

	; VSA = 319 - X - (Breite - 1)
	lds r16, oled_window_width		; Breite
	lds r17, oled_window_width+1	
	subi r16, 1				; Breite - 1
	sbci r17, 0
	sub r20, r16			; (319 - X) - (Breite - 1)
	sbc r21, r17
	
	ldi r22, 0x35			; Index RAM Position
	rcall OLED_SEND_DATA	; sende VSA

	; HEA = 239 - Y
	ldi	r20, 239	; HEA = 239
	lds r16, oled_y_koord
	sub r20, r16	; 239 - Y

	; HSA = 239 - Y - (Höhe - 1)
	lds r16, oled_window_high	; Höhe
	dec r16					; Höhe - 1
	mov r21, r20			; 239 - Y
	sub r21, r16			; (239 - Y) - (Höhe - 1)

	ldi r22, 0x37		; Index RAM Position
	rcall OLED_SEND_DATA	; sende HEA und HSA

	; Cursor auf Startpixel
	rcall OLED_SET_XY
	
	pop r22
	pop r21
	pop r20
	pop r17	
	pop r16

	ret

// +-----------------------.
// | ^ HEA                 |
// |                 VSA ->|
// |                       |
// |        WINDOW         |
// |<- VEA                 |
// |              HSA \/   |
// '-----------------------'


;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Reset Window
;
;			/param: no param
;------------------------------------------------------------------------------
OLED_RESET_WINDOW:
	push r16
	push r20
	push r21
	push r22

	ldi r22, 0x35			; vertical RAM adress position register
	ldi r21, 0
	ldi r20, 0
	rcall OLED_SEND_DATA

	ldi r22, 0x36			; vertical RAM adress position register
	ldi r21, high(319)
	ldi r20, low(319)
	rcall OLED_SEND_DATA

	ldi r22, 0x37			; horizontal RAM adress position register
	ldi r21, 0
	ldi r20, 239
	rcall OLED_SEND_DATA

	ldi r16, 0				; reset Cursor
	sts oled_x_koord, r16
	sts oled_x_koord+1, r16
	sts oled_y_koord, r16
	rcall OLED_SET_XY

	pop r22
	pop r21
	pop r20
	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Set cursor (GRAM pointer)
;
;			/param:	oled_x_koord -> X-Koordinate (16bit) (0...319)
;					oled_y_koord -> Y-Koordinate (8bit) (0...239)
;------------------------------------------------------------------------------
OLED_SET_XY:
	push r16
	push r17
	push r20
	push r21
	push r22

	; x = 319 - x
	ldi	r21, high(319)		; 319
	ldi r20, low(319)	
	lds r16, oled_x_koord		; X-Koordinate Low-Byte
	lds r17, oled_x_koord+1		; X-Koordinate High-Byte
	sub r20, r16			; 319 - x
	sbc r21, r17
	; X-Koordinate senden
	ldi r22, 0x21			; Index GRAM Adresse (x)
	rcall OLED_SEND_DATA	; senden X-Koordinate	
	
	; y = 239 - y
	ldi r20, 239			; 239
	lds r16, oled_y_koord		; Y-Koordinate			
	sub	r20, r16			; 239 - y
	; Y-Koordinate senden
	ldi r21, 0				; Y-Koordinate (high)
	ldi r22, 0x20			; Index GRAM Adresse (y)
	rcall OLED_SEND_DATA	; senden Y-Koordinate

	pop r22
	pop r21
	pop r20
	pop r17
	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Datenuebertragung zum OLED (16-bit)
;
;			/param:	r20 -> LOW-Byte Daten
;					r21 -> HIGH-Byte Daten
;					r22 -> Index				
;------------------------------------------------------------------------------
OLED_SEND_DATA:
	push r16
	push r25

	;..........................................................................
	; write index
	lds r16, oled_spi_portout		; CS-Leitung LOW
	andi r16, ~(0x10)
	sts oled_spi_portout, r16
	
	ldi r25, 0b01110000				; sende Startbyte:
	rcall OLED_SEND_BYTE			;		device ID + code for set index

	ldi r25, 0						; sende High-Byte Index
	rcall OLED_SEND_BYTE

	mov r25, r22					; sende Low-Byte Index
	rcall OLED_SEND_BYTE

	lds r16, oled_spi_portout		; CS-Leitung HIGH
	ori r16, 0x10
	sts oled_spi_portout, r16
	
	;..........................................................................
	;write data
	lds r16, oled_spi_portout		; CS-Leitung LOW
	andi r16, ~(0x10)
	sts oled_spi_portout, r16
	
	ldi r25, 0b01110010				; sende Startbyte:
	rcall OLED_SEND_BYTE			;		device ID + code for data

	mov r25, r21					; sende High-Byte Data
	rcall OLED_SEND_BYTE

	mov r25, r20					; sende Low-Byte Data
	rcall OLED_SEND_BYTE

	lds r16, oled_spi_portout		; CS-Leitung HIGH
	ori r16, 0x10
	sts oled_spi_portout, r16
	;..........................................................................
	
	pop r25
	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Uebertragung eines Bytes zum OLED
;
;			/param:	r25 -> zu uebertragendes Byte
;------------------------------------------------------------------------------
OLED_SEND_BYTE:
	push r16
	
	sts oled_spi_datareg, r25			; Daten senden
_spi_wait:	
	lds r16, oled_spi_statusreg			; warte bis Senden abgeschlossen
	sbrs r16, 7
	rjmp _spi_wait
	
	lds r16, oled_spi_datareg			; SPI Interrupt Flag rücksetzen

	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Zeitverzögerungen 
;
;			Basis: 16 MHz
;					(bei niedriger Frequenz verlängern sich die Verzögerungen
;					entsprechend, dies hat keine Auswirkungen auf die
;					Funktionalität an den entsprechenden Programmstellen
;					dieser Funktionsbibliothek)
;------------------------------------------------------------------------------

_wait_100ms:
	push r18

	ldi r18, 100
_w_100:
	rcall _wait_1ms
	dec r18
	cpi r18, 0
	brne _w_100

	pop r18

	ret
;..............................................................................


_wait_10ms:
	push r18

	ldi r18, 10
_w_10:
	rcall _wait_1ms
	dec r18
	cpi r18, 0
	brne _w_10

	pop r18

	ret
;..............................................................................


_wait_1ms:
	push r16
	push r17
	
	ldi r17, 16
	ldi r16, 250
	dec r16
	cpi r16, 0
	brne PC-2
	dec r17
	cpi r17,0
	brne PC-5

	pop r17
	pop r16

	ret
;------------------------------------------------------------------------------


;------------------------------------------------------------------------------
;			Zeichentabelle
;------------------------------------------------------------------------------
.include "8x14font.inc"

;------------------------------------------------------------------------------


