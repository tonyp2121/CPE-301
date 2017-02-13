;
; Created: 2/10/2017 11:42:41 AM
; Author : Anthony Pallone
; Sarah Harris
; CPE 301L
; Design Assignment 2_1
;


start:
	LDI		R16, 0x61		; I set PinC 0, 4, and 5
	OUT		DDRC, R16
	LDI		R16, 0xFF		; I set ever Pin on PinB
	OUT		DDRB, R16
	LDI		R16, 0x20		; this is a constant of PC.4 toggle
	LDI		R17, 0x40		; this is a constant of PC.5 toggle
	LDI		R22, 0x01		; this is a constand of PC.0 toggle
	LDI		R18, 0x00		; this is a constant 0
	MOV		R8, R18			; keeps track of what needs to be toggled
	MOV		R9, R18			; counter of rising edges
	OUT		PORTB, R18		; make sure there are nothing being outputted currently on PortB
	OUT		PORTC, R18		; make sure there is nothing being outputted on PortC
	LDI		R19, 0x05		; counter to see when it gets to every 5 pulses
	LDI		R20, 0x0A		; counter to see when it gets to ever 10 pulses
	LDI		R23, 0x1E		; 30 our main counter
Begin:
	OUT		TCNT0, R18		; load Timer0 = 0
	OUT		TCCR0A,R18		; Timer0: normal mode, internal clock
	LDI		R24, (1<<CS02)	; Clock/256
	OUT		TCCR0B, R24
Loop:
	IN		R9, TIFR0		; read Timer0 flags register
	SBRS	R9, 0			; if overflow (TOV0) is set skip next instruction
	RJMP	Loop
	OUT		TCCR0B, R18		; stop/disable Timer0
	LDI		R25, (1<<TOV0)	;clear Timer0 overflow flag (TOV0)
	OUT		TIFR0,R25
	DEC		R23				; counter --
	BRNE	Begin			; if counter =! 0 start over again
Toggle:
	EOR		R8, R22			; toggle PC.0
	SBRS	R8, 0			; if R8.0 == 1 skip next line
	JMP		Skip2			; else were done and dont need to do the rest
	INC		R9				; increment counter of rising edges
	DEC		R19				; decriment 5 counter
	BRNE	Skip1			; if =! 0 skip
	EOR		R8, R17			; toggle PC.5
	LDI		R19, 0x05		; restart counter
Skip1:
	DEC		R20				; decriment 10 counter
	BRNE	Skip2			; if =! 0 skip
	EOR		R8, R16			; toggle PC.4
	LDI		R20, 0X0A		; restart counter
Skip2:
	OUT		PORTB, R9		; Output counter to portB
	OUT		PORTC, R8		; Output R8 to PortC
	LDI		R23, 0x1E		; Restart counter
	Jmp		Begin			; Begin again
