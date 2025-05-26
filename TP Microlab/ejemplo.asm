main:	
	SET R7, 0xF0

	; SIG
	SET R0, 0x01
	CALL ins_sig

	; NEG
	SET R1, 0x05
	CALL ins_neg

	; MIX
	SET R2, 0x55
	SET R3, 0xAA
	CALL ins_mix

	; Pruebo los JMPs
	SET R0, 0xFF
	SET R1, 0x01
	ADD R0, R1 ; genera carry
	SET R2, destino_jc
	JC R2

	SET R1, halt
	JMP R1

ins_sig:
	SIG R0
	RET R7 ; R7 se usa como RSP

ins_neg:
	NEG R1
	RET R7

ins_mix:
	MIX R2, R3
	RET R7

destino_jc:
	SET R0, 0x01
	SET R1, 0x01
	SUB R0, R1 ; Z = 1
	SET R2, destino_jz
	JZ R2
	SET R1, halt
	JMP R1

destino_jz:
	SET R0, 0x00
	SET R1, 0x01
	SUB R0, R1 ; N = 1
	SET R2, destino_jn
	JN R2
	SET R1, halt
	JMP R1

destino_jn:
	SET R2, destino_jmp
	JMP R2
	SET R1, halt
	JMP R1

destino_jmp:
	SET R1, halt
	JMP R1

halt:
	SET R1, halt
	JMP R1