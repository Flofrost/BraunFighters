
braunFighters:     file format elf32-avr


Disassembly of section .text:

00000000 <__vectors>:
   0:	0c 94 46 00 	jmp	0x8c	; 0x8c <__ctors_end>
   4:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
   8:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
   c:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  10:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  14:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  18:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  1c:	0c 94 5f 00 	jmp	0xbe	; 0xbe <__vector_7>
  20:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  24:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  28:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  2c:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  30:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  34:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  38:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  3c:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  40:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  44:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  48:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  4c:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  50:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  54:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  58:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  5c:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  60:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  64:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  68:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  6c:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  70:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  74:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  78:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  7c:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  80:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  84:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>
  88:	0c 94 5d 00 	jmp	0xba	; 0xba <__bad_interrupt>

0000008c <__ctors_end>:
  8c:	11 24       	eor	r1, r1
  8e:	1f be       	out	0x3f, r1	; 63
  90:	cf ef       	ldi	r28, 0xFF	; 255
  92:	d0 e4       	ldi	r29, 0x40	; 64
  94:	de bf       	out	0x3e, r29	; 62
  96:	cd bf       	out	0x3d, r28	; 61

00000098 <__do_copy_data>:
  98:	12 e0       	ldi	r17, 0x02	; 2
  9a:	a0 e0       	ldi	r26, 0x00	; 0
  9c:	b1 e0       	ldi	r27, 0x01	; 1
  9e:	e8 e5       	ldi	r30, 0x58	; 88
  a0:	f1 e0       	ldi	r31, 0x01	; 1
  a2:	00 e0       	ldi	r16, 0x00	; 0
  a4:	0b bf       	out	0x3b, r16	; 59
  a6:	02 c0       	rjmp	.+4      	; 0xac <__do_copy_data+0x14>
  a8:	07 90       	elpm	r0, Z+
  aa:	0d 92       	st	X+, r0
  ac:	a2 30       	cpi	r26, 0x02	; 2
  ae:	b1 07       	cpc	r27, r17
  b0:	d9 f7       	brne	.-10     	; 0xa8 <__do_copy_data+0x10>
  b2:	0e 94 9c 00 	call	0x138	; 0x138 <main>
  b6:	0c 94 aa 00 	jmp	0x154	; 0x154 <_exit>

000000ba <__bad_interrupt>:
  ba:	0c 94 00 00 	jmp	0	; 0x0 <__vectors>

000000be <__vector_7>:
  be:	1f 92       	push	r1
  c0:	0f 92       	push	r0
  c2:	0f b6       	in	r0, 0x3f	; 63
  c4:	0f 92       	push	r0
  c6:	11 24       	eor	r1, r1
  c8:	0b b6       	in	r0, 0x3b	; 59
  ca:	0f 92       	push	r0
  cc:	8f 93       	push	r24
  ce:	ef 93       	push	r30
  d0:	ff 93       	push	r31
  d2:	f8 94       	cli
  d4:	80 91 00 01 	lds	r24, 0x0100	; 0x800100 <__DATA_REGION_ORIGIN__>
  d8:	88 23       	and	r24, r24
  da:	d9 f0       	breq	.+54     	; 0x112 <__vector_7+0x54>
  dc:	57 9a       	sbi	0x0a, 7	; 10
  de:	e0 91 00 01 	lds	r30, 0x0100	; 0x800100 <__DATA_REGION_ORIGIN__>
  e2:	e1 50       	subi	r30, 0x01	; 1
  e4:	e0 93 00 01 	sts	0x0100, r30	; 0x800100 <__DATA_REGION_ORIGIN__>
  e8:	f0 e0       	ldi	r31, 0x00	; 0
  ea:	ef 5f       	subi	r30, 0xFF	; 255
  ec:	fe 4f       	sbci	r31, 0xFE	; 254
  ee:	80 81       	ld	r24, Z
  f0:	80 95       	com	r24
  f2:	87 b9       	out	0x07, r24	; 7
	...
  fc:	00 00       	nop
  fe:	57 98       	cbi	0x0a, 7	; 10
	...
 108:	00 00       	nop
 10a:	80 91 00 01 	lds	r24, 0x0100	; 0x800100 <__DATA_REGION_ORIGIN__>
 10e:	81 11       	cpse	r24, r1
 110:	e5 cf       	rjmp	.-54     	; 0xdc <__vector_7+0x1e>
 112:	57 9a       	sbi	0x0a, 7	; 10
 114:	17 b8       	out	0x07, r1	; 7
	...
 11e:	00 00       	nop
 120:	57 98       	cbi	0x0a, 7	; 10
 122:	78 94       	sei
 124:	ff 91       	pop	r31
 126:	ef 91       	pop	r30
 128:	8f 91       	pop	r24
 12a:	0f 90       	pop	r0
 12c:	0b be       	out	0x3b, r0	; 59
 12e:	0f 90       	pop	r0
 130:	0f be       	out	0x3f, r0	; 63
 132:	0f 90       	pop	r0
 134:	1f 90       	pop	r1
 136:	18 95       	reti

00000138 <main>:
 138:	88 e0       	ldi	r24, 0x08	; 8
 13a:	80 93 68 00 	sts	0x0068, r24	; 0x800068 <__TEXT_REGION_LENGTH__+0x7e0068>
 13e:	80 e8       	ldi	r24, 0x80	; 128
 140:	80 93 73 00 	sts	0x0073, r24	; 0x800073 <__TEXT_REGION_LENGTH__+0x7e0073>
 144:	8f ef       	ldi	r24, 0xFF	; 255


 146:	57 9a       	sbi	0x0a, 7	; 10

 148:	87 b9       	out	0x07, r24	; 7
 14a:	57 98       	cbi	0x0a, 7	; 10

 14c:	4f 9b       	sbis	0x09, 7	; 9
 14e:	fe cf       	rjmp	.-4      	; 0x14c <main+0x14>


 150:	81 50       	subi	r24, 0x01	; 1
 152:	f9 cf       	rjmp	.-14     	; 0x146 <main+0xe>

00000154 <_exit>:
 154:	f8 94       	cli

00000156 <__stop_program>:
 156:	ff cf       	rjmp	.-2      	; 0x156 <__stop_program>
