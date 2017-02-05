;
; Design Assignment 1
; CPE 301
; Sarrah Harris
; 
; Created: 2/4/2017 4:11:07 PM
; Author : Anthony Pallone
;

start:
	LDI R19, 25				;counter of numbers we entered
	LDI R18, 0				;constant 0
	LDI R16, 3				;constant 3
	LDI R17, 7				;constant 7
	LDI R20, 0				;running sum for 7
	LDI R21, 0				;upper part of running sum
	LDI R23, 0				;running sum for 3
	LDI R24, 0				;upper part of running sum
	ldi R25, 0				; just set it to 0 so when it was Or-d later it would be 0
	LDI R31,0				; same as above
	OUT PORTB, R18			; would set port B to 0 which turns it off
	LDI ZL, LOW(RAMEND/2)
	LDI ZH, HIGH(RAMEND/2)	;Have to set Z to point to RAMEND/2

loopOne:
	MOV  R9, ZL				;Since we want to store the lower part of RAMEND/2 into Z we move it into R9
	ST  Z+, R9				;then go right on ahead and store it
	DEC R19					;decriment counter
	CP R19, R18				;compare to 0
	BRNE loopOne			;if not 0 we havent done 25 loops and wrote to 25 memory locations

	LDI ZL, LOW(RAMEND/2)
	LDI ZH, HIGH(RAMEND/2)	;Have to set Z to point to RAMEND/2 again
	LDI R19, 25				;counter of numbers we entered

loopTwo:
	LD R9, Z+				; we load from Z and then we increment Z
	MOV R8, R9				; we copy r9 to keep r9 from being changed
	CP R8, R18			
	BREQ threeSkip		;if R8 = 0 we dont have to do any of the next calculations its just a tiny time skip
	CP R8, R17			;we also see if r8 < r17 at the start in which case the next loop wouldnt work so we check beforehand
	BRLO sevenDone

sevenLoop:
	SUB R8, R17			;since we cant divide we subtract 7 until its less than 7
	CP R8, R17			;we check if its < 7
	BRSH sevenLoop		;if so go to seven loop

sevenDone:
	CP R8, R18			;we see if r8 = 0 if its not we skip the next couple of lines
	BRNE sevenSkip
	ADD R20, R9			;add r9 into our running some
	brlo overflowSeven	;we check if theres an overflow if there is we jump
	jmp sevenSkip		;if not we skip the next line of code

overflowSeven:
	inc R21				;we increment the top part of the running some
	ldi r28, 0b00010000	; load up 0x10 so we can open portb.4 and ddrb.4
	or	r28, r25		;in case theres the other one
	mov r7, r28			; set r7.4
	out DDRB, r28		;out ddrb.4
	out PORTB, r28		;out portb.4

			
sevenSkip:
	MOV R8, R9			;copy r8 so r9 is untouched 
	CP R8, R17			;see if r8 is less than 3 if so were done
	BRLO threeDone

threeLoop:
	SUB R8, R16			;subtract 3
	CP R8, R16			;see if its less than 3 and untiol it is we repeatedly subtract
	BRSH threeLoop

threeDone:
	CP R8, R18			;we see if its = 0 if not we skip the next lines of code
	BRNE threeSkip
	ADD R23, R9			;add it to our running sum
	brlo overflowThree	;if theres overflow do the next couple lines of code
	jmp threeSkip		;otherwise skip em

overflowThree:
	inc r24				;increment top register
	ldi r25, 0b00001000	;set 0x08 so it portb.3 and ddrb.3
	or	r25, r28		;see if we got the other one to overflow
	mov r7, r25         ;set 7.3
	out DDRB, r25		;out ddrb.3
	out PORTB, r25		;out portb.3


threeSkip:
	DEC R19				;decriment counter
	CP  R19, R18		;see if its = 0
	BRNE loopTwo		;if not loop again

	jmp start			;then its done so jump to start