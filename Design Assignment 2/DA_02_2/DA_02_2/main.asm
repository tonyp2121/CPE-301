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
	LDI		R16, 0x31		; I set PinC 0, 4, and 5
	OUT		DDRC, R16
	LDI		R16, 0xFF		; I set ever Pin on PinB
	OUT		DDRB, R16
	LDI		R16, 0x10		; toggle for Port C.4
	LDI		R17, 0x20		; toggle for Port C.5
	LDI		R22, 0x01		; toggle for Port C.0
	LDI		R18, 0x00		; this is a constant 0
	MOV		R8, R18			; keeps track of what needs to be toggled
	MOV		R9, R18			; counter of rising edges
	OUT		PORTB, R18		; make sure there are nothing being outputted currently on PortB
	OUT		PORTC, R18		; make sure there is nothing being outputted on PortC
	LDI		R19, 0x05		; 5 counter
	LDI		R20, 0x0A		;10 counter
	LDI		R23, 0x1E		;30 our counter
Begin:
	OUT		TCNT0, R18
	OUT		TCCR0A,R18		; Timer0: normal mode, internal clock
	LDI		R24, (1<<CS02)	; put clock /256
	OUT		TCCR0B, R24		;enable overflow interrupt
	STS		TIMSK0, R22
	SEI						; set global interrupts

Loop:
	RJMP	LOOP			; infinite loop

TIM0_OVF:
	OUT		TCCR0B, R18		; stop/disable Timer0
	LDI		R26, (1<<TOV0)	; clear Timer0 overflow flag (TOV0)
	OUT		TIFR0, R26
	DEC		R23				; counter --
	BRNE	Skip2			; if counter =! 0 jump to finish

	LDI		R23, 30			; restart counter
	EOR		R8, R22			; toggle PortC.0
	SBRS	R8, 0			; if R8.0 == 1 skip next line
	JMP		Skip2
	INC		R9				; increment counter
	DEC		R19				; decriment the 5 counter
	BRNE	Skip1			; if its =! 0 skip
	LDI		R19, 0x05		; restart 5 counter
	EOR		R8, R17			; toggle PC.5
Skip1:
	DEC		R20				; decriment 10 counter
	BRNE	Skip2			; if =! 0 skip
	LDI		R20, 0x0A		; restart the 10 counter
	EOR		R8, R16			; toggle PC.4
Skip2:
	OUT		PORTB, R9		; output counter
	OUT		PORTC, R8		; output changes

Finish:
	OUT		TCNT0, R18		;load Timer0 = 0
	OUT		TCCR0A,R18		;Timer0: enabled
	LDI		R24, (1<<CS02)	; put clock /256
	OUT		TCCR0B, R24
	RETI					;return from interrupt
