
;------------------------------------------------------------------------------
;
;	Tabelle f�r Schriftzeichen 8x14pxl
;
;	Filename:		8x14font.inc
;	Date:			01/2010
;	Version:		1.0
;	Target:			hD2 / ATxmega 128A1
;	Author:			mj, ACMC
;	Support-Email:	acmc@hs-mittweida.de
;	
;------------------------------------------------------------------------------


.cseg

Font8x14:
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00      // space (32)
	.db  0x00 , 0x00 , 0x00 , 0x18 , 0x3C , 0x3C , 0x3C , 0x18 , 0x18 , 0x00 , 0x18 , 0x18 , 0x00 , 0x00      // !
	.db  0x00 , 0x66 , 0x66 , 0x66 , 0x24 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00      // Anf�hrungszeichen
	.db  0x00 , 0x00 , 0x00 , 0x6C , 0x6C , 0xFE , 0x6C , 0x6C , 0x6C , 0xFE , 0x6C , 0x6C , 0x00 , 0x00      // #
	.db  0x00 , 0x18 , 0x18 , 0x7C , 0xC6 , 0xC2 , 0xC0 , 0x7C , 0x06 , 0x86 , 0xC6 , 0x7C , 0x18 , 0x18      // &
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xC2 , 0xC6 , 0x0C , 0x18 , 0x30 , 0x66 , 0xC6 , 0x00 , 0x00      // %
	.db  0x00 , 0x00 , 0x00 , 0x38 , 0x6C , 0x6C , 0x38 , 0x76 , 0xDC , 0xCC , 0xCC , 0x76 , 0x00 , 0x00      // &
	.db  0x00 , 0x18 , 0x18 , 0x18 , 0x30 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00      // //
	.db  0x00 , 0x00 , 0x00 , 0x0C , 0x18 , 0x30 , 0x30 , 0x30 , 0x30 , 0x30 , 0x18 , 0x0C , 0x00 , 0x00      // (
	.db  0x00 , 0x00 , 0x00 , 0x30 , 0x18 , 0x0C , 0x0C , 0x0C , 0x0C , 0x0C , 0x18 , 0x30 , 0x00 , 0x00      // )
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x66 , 0x3C , 0xFF , 0x3C , 0x66 , 0x00 , 0x00 , 0x00 , 0x00      // *
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x7E , 0x18 , 0x18 , 0x00 , 0x00 , 0x00 , 0x00      // +
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x18 , 0x30 , 0x00      // �
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xFE , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00      // -
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x00 , 0x00      // .
	.db  0x00 , 0x00 , 0x00 , 0x02 , 0x06 , 0x0C , 0x18 , 0x30 , 0x60 , 0xC0 , 0x80 , 0x00 , 0x00 , 0x00      // /
	.db  0x00 , 0x00 , 0x00 , 0x38 , 0x6C , 0xC6 , 0xC6 , 0xD6 , 0xC6 , 0xC6 , 0x6C , 0x38 , 0x00 , 0x00      // 0 (48-32)
	.db  0x00 , 0x00 , 0x00 , 0x18 , 0x38 , 0x78 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x7E , 0x00 , 0x00      //1
	.db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0x06 , 0x0C , 0x18 , 0x30 , 0x60 , 0xC6 , 0xFE , 0x00 , 0x00      //2
	.db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0x06 , 0x06 , 0x3C , 0x06 , 0x06 , 0xC6 , 0x7C , 0x00 , 0x00      //3
	.db  0x00 , 0x00 , 0x00 , 0x0C , 0x1C , 0x3C , 0x6C , 0xCC , 0xFE , 0x0C , 0x0C , 0x1E , 0x00 , 0x00      //4
	.db  0x00 , 0x00 , 0x00 , 0xFE , 0xC0 , 0xC0 , 0xC0 , 0xFC , 0x06 , 0x06 , 0xC6 , 0x7C , 0x00 , 0x00      //5
	.db  0x00 , 0x00 , 0x00 , 0x38 , 0x60 , 0xC0 , 0xC0 , 0xFC , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //6
	.db  0x00 , 0x00 , 0x00 , 0xFE , 0xC6 , 0x06 , 0x0C , 0x18 , 0x30 , 0x30 , 0x30 , 0x30 , 0x00 , 0x00      //7
	.db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //8
	.db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0x7E , 0x06 , 0x06 , 0x0C , 0x78 , 0x00 , 0x00      //9
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x00 , 0x00 , 0x00      //:
	.db  0x00 , 0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x30 , 0x00 , 0x00      //;
	.db  0x00 , 0x00 , 0x00 , 0x0C , 0x18 , 0x30 , 0x60 , 0xC0 , 0x60 , 0x30 , 0x18 , 0x0C , 0x00 , 0x00      //>
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x7E , 0x00 , 0x00 , 0x7E , 0x00 , 0x00 , 0x00 , 0x00      //=
    .db  0x00 , 0x00 , 0x00 , 0x60 , 0x30 , 0x18 , 0x0C , 0x06 , 0x0C , 0x18 , 0x30 , 0x60 , 0x00 , 0x00      //<
    .db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0x0C , 0x18 , 0x18 , 0x00 , 0x18 , 0x18 , 0x00 , 0x00      //?
    .db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0xDE , 0xDE , 0xDE , 0xDC , 0xC0 , 0x7C , 0x00 , 0x00      //@
    .db  0x00 , 0x00 , 0x00 , 0x10 , 0x38 , 0x6C , 0xC6 , 0xC6 , 0xFE , 0xC6 , 0xC6 , 0xC6 , 0x00 , 0x00      //A
    .db  0x00 , 0x00 , 0x00 , 0xFC , 0x66 , 0x66 , 0x66 , 0x7C , 0x66 , 0x66 , 0x66 , 0xFC , 0x00 , 0x00      //B
    .db  0x00 , 0x00 , 0x00 , 0x3C , 0x66 , 0xC2 , 0xC0 , 0xC0 , 0xC0 , 0xC2 , 0x66 , 0x3C , 0x00 , 0x00      //C
    .db  0x00 , 0x00 , 0x00 , 0xF8 , 0x6C , 0x66 , 0x66 , 0x66 , 0x66 , 0x66 , 0x6C , 0xF8 , 0x00 , 0x00      //D
    .db  0x00 , 0x00 , 0x00 , 0xFE , 0x66 , 0x62 , 0x68 , 0x78 , 0x68 , 0x62 , 0x66 , 0xFE , 0x00 , 0x00      //E
    .db  0x00 , 0x00 , 0x00 , 0xFE , 0x66 , 0x62 , 0x68 , 0x78 , 0x68 , 0x60 , 0x60 , 0xF0 , 0x00 , 0x00      //F
    .db  0x00 , 0x00 , 0x00 , 0x3C , 0x66 , 0xC2 , 0xC0 , 0xC0 , 0xDE , 0xC6 , 0x66 , 0x3A , 0x00 , 0x00      //G
    .db  0x00 , 0x00 , 0x00 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xFE , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x00 , 0x00      //H
    .db  0x00 , 0x00 , 0x00 , 0x3C , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x3C , 0x00 , 0x00      //I
    .db  0x00 , 0x00 , 0x00 , 0x1E , 0x0C , 0x0C , 0x0C , 0x0C , 0x0C , 0xCC , 0xCC , 0x78 , 0x00 , 0x00      //J
    .db  0x00 , 0x00 , 0x00 , 0xE6 , 0x66 , 0x6C , 0x6C , 0x78 , 0x6C , 0x6C , 0x66 , 0xE6 , 0x00 , 0x00      //K
    .db  0x00 , 0x00 , 0x00 , 0xF0 , 0x60 , 0x60 , 0x60 , 0x60 , 0x60 , 0x62 , 0x66 , 0xFE , 0x00 , 0x00      //L
    .db  0x00 , 0x00 , 0x00 , 0xC6 , 0xEE , 0xFE , 0xD6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x00 , 0x00      //M
    .db  0x00 , 0x00 , 0x00 , 0xC6 , 0xE6 , 0xF6 , 0xFE , 0xDE , 0xCE , 0xC6 , 0xC6 , 0xC6 , 0x00 , 0x00      //N
    .db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //O
    .db  0x00 , 0x00 , 0x00 , 0xFC , 0x66 , 0x66 , 0x66 , 0x7C , 0x60 , 0x60 , 0x60 , 0xF0 , 0x00 , 0x00      //P
    .db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xD6 , 0xDE , 0x7C , 0x0E , 0x00      //Q
    .db  0x00 , 0x00 , 0x00 , 0xFC , 0x66 , 0x66 , 0x66 , 0x7C , 0x6C , 0x66 , 0x66 , 0xE6 , 0x00 , 0x00      //R
    .db  0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0x60 , 0x38 , 0x0C , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //S
    .db  0x00 , 0x00 , 0x00 , 0x7E , 0x7E , 0x5A , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x3C , 0x00 , 0x00      //T
    .db  0x00 , 0x00 , 0x00 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //U
    .db  0x00 , 0x00 , 0x00 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x6C , 0x38 , 0x10 , 0x00 , 0x00      //V
    .db  0x00 , 0x00 , 0x00 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xD6 , 0xD6 , 0xFE , 0x6C , 0x6C , 0x00 , 0x00      //W
    .db  0x00 , 0x00 , 0x00 , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x38 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0x00 , 0x00      //X
    .db  0x00 , 0x00 , 0x00 , 0x66 , 0x66 , 0x66 , 0x66 , 0x3C , 0x18 , 0x18 , 0x18 , 0x3C , 0x00 , 0x00      //Y
    .db  0x00 , 0x00 , 0x00 , 0xFE , 0xC6 , 0x8C , 0x18 , 0x30 , 0x60 , 0xC2 , 0xC6 , 0xFE , 0x00 , 0x00      //Z
    .db  0x00 , 0x00 , 0x00 , 0x3C , 0x30 , 0x30 , 0x30 , 0x30 , 0x30 , 0x30 , 0x30 , 0x3C , 0x00 , 0x00      //[
    .db  0x00 , 0x00 , 0x00 , 0x80 , 0xC0 , 0xE0 , 0x70 , 0x38 , 0x1C , 0x0E , 0x06 , 0x02 , 0x00 , 0x00      // "\"
    .db  0x00 , 0x00 , 0x00 , 0x3C , 0x0C , 0x0C , 0x0C , 0x0C , 0x0C , 0x0C , 0x0C , 0x3C , 0x00 , 0x00      //]
    .db  0x10 , 0x38 , 0x6C , 0xC6 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00      //^
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xFF      //_
    .db  0x00 , 0x30 , 0x18 , 0x0C , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00      //�
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x78 , 0x0C , 0x7C , 0xCC , 0xCC , 0x76 , 0x00 , 0x00      //a
    .db  0x00 , 0x00 , 0x00 , 0xE0 , 0x60 , 0x60 , 0x78 , 0x6C , 0x66 , 0x66 , 0x66 , 0x7C , 0x00 , 0x00      //b
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC0 , 0xC0 , 0xC6 , 0x7C , 0x00 , 0x00      //c
    .db  0x00 , 0x00 , 0x00 , 0x1C , 0x0C , 0x0C , 0x3C , 0x6C , 0xCC , 0xCC , 0xCC , 0x76 , 0x00 , 0x00      //d
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xFE , 0xC0 , 0xC6 , 0x7C , 0x00 , 0x00      //e
    .db  0x00 , 0x00 , 0x00 , 0x1C , 0x36 , 0x32 , 0x30 , 0x7C , 0x30 , 0x30 , 0x30 , 0x78 , 0x00 , 0x00      //f
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x76 , 0xCC , 0xCC , 0xCC , 0x7C , 0x0C , 0xCC , 0x78      //g
    .db  0x00 , 0x00 , 0x00 , 0xE0 , 0x60 , 0x60 , 0x6C , 0x76 , 0x66 , 0x66 , 0x66 , 0xE6 , 0x00 , 0x00      //h
    .db  0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x00 , 0x38 , 0x18 , 0x18 , 0x18 , 0x18 , 0x3C , 0x00 , 0x00      //i
    .db  0x00 , 0x00 , 0x00 , 0x06 , 0x06 , 0x00 , 0x0E , 0x06 , 0x06 , 0x06 , 0x06 , 0x66 , 0x66 , 0x3C      //j
    .db  0x00 , 0x00 , 0x00 , 0xE0 , 0x60 , 0x60 , 0x66 , 0x6C , 0x78 , 0x6C , 0x66 , 0xE6 , 0x00 , 0x00      //k
    .db  0x00 , 0x00 , 0x00 , 0x38 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x3C , 0x00 , 0x00      //l
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xEC , 0xFE , 0xD6 , 0xD6 , 0xD6 , 0xD6 , 0x00 , 0x00      //m
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xDC , 0x66 , 0x66 , 0x66 , 0x66 , 0x66 , 0x00 , 0x00      //n
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //o
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xDC , 0x66 , 0x66 , 0x66 , 0x7C , 0x60 , 0x60 , 0xF0      //P
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x76 , 0xCC , 0xCC , 0xCC , 0x7C , 0x0C , 0x0C , 0x1E      //q
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xDC , 0x76 , 0x66 , 0x60 , 0x60 , 0xF0 , 0x00 , 0x00      //r
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x7C , 0xC6 , 0x70 , 0x1C , 0xC6 , 0x7C , 0x00 , 0x00      //s
    .db  0x00 , 0x00 , 0x00 , 0x10 , 0x30 , 0x30 , 0xFC , 0x30 , 0x30 , 0x30 , 0x36 , 0x1C , 0x00 , 0x00      //t
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0x76 , 0x00 , 0x00      //u
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xC6 , 0xC6 , 0xC6 , 0x6C , 0x38 , 0x10 , 0x00 , 0x00      //v
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xC6 , 0xC6 , 0xD6 , 0xD6 , 0xFE , 0x6C , 0x00 , 0x00      //w
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xC6 , 0x6C , 0x38 , 0x38 , 0x6C , 0xC6 , 0x00 , 0x00      //x
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x7E , 0x06 , 0x0C , 0x78      //y
    .db  0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xFE , 0xCC , 0x18 , 0x30 , 0x66 , 0xFE , 0x00 , 0x00      //z 122
    .db  0x00 , 0x00 , 0x00 , 0x0E , 0x18 , 0x18 , 0x18 , 0x70 , 0x18 , 0x18 , 0x18 , 0x0E , 0x00 , 0x00      //{
    .db  0x00 , 0x00 , 0x00 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x18 , 0x00 , 0x00      //|
    .db  0x00 , 0x00 , 0x00 , 0x70 , 0x18 , 0x18 , 0x18 , 0x0E , 0x18 , 0x18 , 0x18 , 0x70 , 0x00 , 0x00      //}
    .db  0xFF , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0xFF      //unused
    .db  0x00 , 0x00 , 0x00 , 0x48 , 0x00 , 0x00 , 0x78 , 0x0C , 0x7C , 0xCC , 0xCC , 0x76 , 0x00 , 0x00      //�
    .db  0x00 , 0x00 , 0x00 , 0x48 , 0x00 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //�
    .db  0x00 , 0x00 , 0x00 , 0x48 , 0x00 , 0x00 , 0xCC , 0xCC , 0xCC , 0xCC , 0xCC , 0x76 , 0x00 , 0x00      //�
    .db  0x00 , 0x44 , 0x00 , 0x10 , 0x38 , 0x6C , 0xC6 , 0xC6 , 0xFE , 0xC6 , 0xC6 , 0xC6 , 0x00 , 0x00      //�
    .db  0x00 , 0x44 , 0x00 , 0x7C , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //�
    .db  0x00 , 0x44 , 0x00 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0xC6 , 0x7C , 0x00 , 0x00      //�
    .db  0x00 , 0x00 , 0x00 , 0x78 , 0xCC , 0xCC , 0xF8 , 0xCC , 0xCC , 0xCC , 0xF8 , 0xC0 , 0xC0 , 0xC0      //�
    .db  0x00 , 0x00 , 0x00 , 0x18 , 0x24 , 0x24 , 0x18 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 	  // �

;------------------------------------------------------------------------------


