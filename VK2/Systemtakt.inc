
;------------------------------------------------------------------------------
;
;	Funktionen zur Konfiguration des Systemtaktes
;
;	Filename:		Sytemtakt.inc
;	Date:			01/2010
;	Version:		1.0
;	Target:			hD2 / ATxmega 128A1
;	Author:			mj, ACMC
;	Support-Email:	acmc@hs-mittweida.de
;	
;------------------------------------------------------------------------------

.equ F_CPU = 16000000 		; Systemtakt 16 MHz


.cseg

;------------------------------------------------------------------------------
;	Unterprogramm zur Umschaltung der Taktquelle auf den externen 16MHz Quarz
;------------------------------------------------------------------------------

CLOCK_INIT_16MHZ:
	push r16

	ldi r16, 0b11000111		; Bereich 12-16MHz, Startup-Time 1k Clk
	sts OSC_XOSCCTRL, r16

	lds r16, OSC_CTRL
	ori	r16, (1<<3)			; external Oscillator enable
	sts OSC_CTRL, r16
clock_wait:
	lds r16, OSC_STATUS		; warte bis external Oscillator ready
	sbrs r16, 3
	rjmp clock_wait

	ldi r16, 0xD8			; Configuration Protection Register beschreiben
	out CPU_CCP, r16
	ldi r16, 0b00000011		; Umschalten auf externen Quarz als Taktquelle
	sts CLK_CTRL, r16

	ldi	r16, 0b00001000		; andere Oscillatoren abschalten
	sts OSC_CTRL, r16

	pop r16
	ret

;------------------------------------------------------------------------------
