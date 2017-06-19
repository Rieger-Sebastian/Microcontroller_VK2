;------------------------------------------------------------------------------
;
;	Funktionen zur Umwandlung von 8-Bit Zahlen in einen String
;
;	Filename:		bin8tostring.inc
;	benötigt:		bcd.inc
;	Date:			03/2010
;	Version:		1.0
;	Target:			hD2 / ATxmega 128A1
;	Author:			hpo, ACMC
;	Support-Email:	acmc@hs-mittweida.de
;	
;------------------------------------------------------------------------------
.dseg
string_var: .byte 4 			; 5 Byte (max. 3 Zeichen + NULL)
bin8in:		.byte 1				; 1 Byte für Funktion bin8tostring

.cseg

bin8tostring:
	push r16					; verwendete Register auf dem Stack sichern
	push r17
	push r18

	lds r16,bin8in
	sts val_bin8,r16			; speichern in Übergabevariable für BIN8_TO_BCD

	rcall BIN8_TO_BCD			; BIN8_TO_BCD Wandlung ausführen

	ldi XL, low(string_var)		; setze X-Zeiger Low-Byte von Speicheradresse des String
	ldi XH, high(string_var)	; setze X-Zeiger High-Byte von Speicheradresse des String
	
	lds r17,bcd1				; lade Ergebnis High-Byte der BIN8_TO_BCD Wandlung nach temp2
	sts bcd,r17					; speichern in Übergabevariable für BCD_TO_ASCII
	rcall BCD_TO_ASCII			; BCD_TO_ASCII ausführen

	lds r18,ascii0				; lade Ergebnis Low-Byte der BCD_TO_ASCII nach temp3

	st X+,r18					; schreibe temp3 nach string_var und incrementiere X

	lds r17,bcd0				; lade Ergebnis Low-Byte der BIN8_TO_BCD Wandlung nach temp2
	sts bcd,r17					; speichern in Übergabevariable für BCD_TO_ASCII
	rcall BCD_TO_ASCII			; BCD_TO_ASCII ausführen

	lds r17,ascii1				; lade Ergebnis High-Byte der BCD_TO_ASCII nach temp2
	lds r18,ascii0				; lade Ergebnis Low-Byte der BCD_TO_ASCII nach temp3

	st X+,r17					; schreibe temp2 nach string_var und incrementiere X
	st X+,r18					; schreibe temp3 nach string_var und incrementiere X

	ldi r16,0					; lade temp1 mit NULL-Kennung für string_var
	st X,r16					; schreibe temp1 nach string_var

	pop r18
	pop r17
	pop r16						; verwendete Register vom Stack holen
	ret
