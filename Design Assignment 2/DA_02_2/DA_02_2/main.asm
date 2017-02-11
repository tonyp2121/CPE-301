;
; Created: 2/10/2017 11:42:41 AM
; Author : Anthony Pallone
; Sarah Harris
; CPE 301L
; Design Assignment 2_2
;
.org 0
	jmp  Start
.org 0x20
	jmp  TIM0_OVF


Start:
	LDI		R16, 0x61
	OUT		DDRC, R16
	LDI		R16, 0xFF
	OUT		DDRB, R16
	LDI		R16, 0x20		; toggle for Port C.4
	LDI		R17, 0x40		; toggle for Port C.5
	LDI		R22, 0x01		; toggle for Port C.0
	LDI		R18, 0x00
	MOV		R8, R18			; keeps track of what needs to be toggled
	MOV		R9, R18			; counter of rising edges
	OUT		PORTB, R18
	OUT		PORTC, R18
	LDI		R19, 0x05		; 5 counter
	LDI		R20, 0x0A		;10 counter
	LDI		R23, 0x1E		;30 our counter
Begin:
	OUT		TCNT0, R18
	OUT		TCCR0A,R18
	LDI		R24, (1<<CS02)	; put clock /256
	OUT		TCCR0B, R24
	STS		TIMSK0, R22
	SEI

Loop:
	RJMP	LOOP

TIM0_OVF:
	OUT		TCCR0B, R18
	LDI		R26, (1<<TOV0)
	OUT		TIFR0, R26
	DEC		R23
	BRNE	Finish

	LDI		R23, 30
	EOR		R8, R22
	DEC		R19
	BRNE	Skip1
	LDI		R19, 0x05
	EOR		R8, R16
Skip1:
	DEC		R20
	BRNE	Skip2
	LDI		R20, 0x0A
	EOR		R8, R17
Skip2:
	INC		R9
	OUT		PORTB, R9
	OUT		PORTC, R8

Finish:
	OUT		TCNT0, R18
	OUT		TCCR0A,R18
	LDI		R24, (1<<CS02)	; put clock /256
	OUT		TCCR0B, R24
	RETI