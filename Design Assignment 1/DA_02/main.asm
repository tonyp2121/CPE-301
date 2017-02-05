;;
; Design Assignment 2
; CPE 301
; Sarrah Harris
; 
; Created: 2/4/2017 4:11:07 PM
; Author : Anthony Pallone
;


	LDI R19, 25				;counter of numbers we entered
	LDI R18, 0				;constant 0
	LDI R16, 3				;constant 3
	LDI R17, 7				;constant 7
	LDI R20, 0				;running sum for 7
	LDI R21, 0
	LDI R23, 0				;running sum for 3
	LDI R24, 0
	ldi R25, 0
	LDI R31,0
	LDI ZL, LOW(RAMEND/2)
	LDI ZH, HIGH(RAMEND/2)	;Have to set Z to point to RAMEND/2

loopOne:
	MOV  R9, ZL
	ST  Z+, R9
	DEC R19
	CP R19, R18
	BRNE loopOne

	LDI ZL, LOW(RAMEND/2)
	LDI ZH, HIGH(RAMEND/2)	;Have to set Z to point to RAMEND/2
	LDI R19, 25				;counter of numbers we entered

loopTwo:
	LD R9, Z+
	MOV R8, R9
	CP R8, R18
	BREQ threeSkip	;if its R8 == 0 we dont have to do any of the next calculations its just a tiny time skip
	CP R8, R17
	BRLO sevenDone

sevenLoop:
	SUB R8, R17
	CP R8, R17
	BRSH sevenLoop

sevenDone:
	CP R8, R18
	BRNE sevenSkip
	ADD R20, R9
	brlo overflowSeven
	jmp sevenSkip

overflowSeven:
	inc R21
	ldi r31, 0b00010000
	or	r31, r25
	mov r7, r31
	out DDRB, r31
	out PORTB, r31
			
sevenSkip:
	MOV R8, R9
	CP R8, R17
	BRLO threeDone

threeLoop:
	SUB R8, R16
	CP R8, R16
	BRSH threeLoop

threeDone:
	CP R8, R18
	BRNE threeSkip
	ADD R23, R9'
	brlo overflowThree
	jmp threeSkip

overflowThree:
	inc r24
	ldi r25, 0b00001000
	or	r25, r31
	mov r7, r25
	out DDRB, r25
	out PORTB, r25 

threeSkip:
	DEC R19
	CP  R19, R18
	BRNE loopTwo

done:
	jmp loopOne