;
; Created: 2/10/2017 11:42:41 AM
; Author : Anthony Pallone
; Sarah Harris
; CPE 301L
;


; Replace with your application code
start:
	LDI		R16, 0x61
	OUT		DDRC, R16
	LDI		R16, 0xFF
	OUT		DDRB, R16
	LDI		R16, 0x20
	LDI		R17, 0x40
	LDI		R22, 0x01
	LDI		R18, 0x00
	MOV		R8, R18			; keeps track of what needs to be toggled
	MOV		R9, R18			; counter of rising edges
	OUT		PORTB, R18
	OUT		PORTC, R18
	LDI		R19, 0x05
	LDI		R20, 0x0A
	LDI		R23, 0x1E		;30 our counter
Begin:
	OUT		TCNT0, R18
	OUT		TCCR0A,R18
	LDI		R24, (1<<CS02)
	OUT		TCCR0B, R24
Loop:
	IN		R9, TIFR0
	SBRS	R9, 0
	JMP		Loop
	OUT		TCCR0B, R18
	LDI		R25, (1<<TOV0)
	OUT		TIFR0,R25
	DEC		R23
	BRNE	Loop
Toggle:
	EOR		R8, R22
	SBRS	R8, 0
	JMP		Skip2
	INC		R9
	DEC		R19
	BRNE	Skip1
	EOR		R8, R16
	LDI		R19, 0x05
Skip1:
	DEC		R20
	BRNE	Skip2
	EOR		R8, R17
	LDI		R20, 0X0A
Skip2:
	OUT		PORTB, R9
	OUT		PORTC, R8
	LDI		R23, 0x1E
	Jmp		Begin