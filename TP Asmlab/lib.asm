
global strClone
global strPrint
global strCmp
global strLen
global strDelete

global arrayNew
global arrayDelete
global arrayPrint
global arrayGetSize
global arrayAddLast
global arrayGet
global arrayRemove
global arraySwap

global cardCmp
global cardClone
global cardAddStacked
global cardDelete
global cardGetSuit
global cardGetNumber
global cardGetStacked
global cardPrint
global cardNew

extern calloc
extern free
extern fputs
extern intClone
extern intDelete
extern intPrint
extern fprintf
extern cloneDataByType
extern deleteDataByType
extern printDataByType

extern listNew
extern listAddFirst
extern listAddLast
extern listPrint
extern listDelete

%define SIZEOF_ARRAY 16
%define OFFSET_ARRAY_TYPE 0
%define OFFSET_ARRAY_SIZE 4
%define OFFSET_ARRAY_CAPACITY 5
%define OFFSET_ARRAY_DATA 8

%define SIZEOF_CARD 24
%define OFFSET_CARD_SUIT 0
%define OFFSET_CARD_NUMBER 8
%define OFFSET_CARD_STACKED 16

%define SIZEOF_LIST 24
%define OFFSET_LIST_TYPE 0
%define OFFSET_LIST_SIZE 4
%define OFFSET_LIST_FIRST 8
%define OFFSET_LIST_LAST 16

%define OFFSET_LISTELEM_DATA 0
%define OFFSET_LISTELEM_NEXT 8
%define OFFSET_LISTELEM_PREV 16

section .data
	null_str db "NULL", 0
	apertura_corchetes db "[", 0
	coma db ",", 0
	cierre_corchetes db "]", 0
	abro_card db "{", 0
	guion db "-", 0
	cierro_card db "}", 0

section .text
; ---------------- String ----------------

;char* strClone(char* a);
strClone:
	push rbp
	mov rbp, rsp
	sub rsp, 8

	push r12
	push r13
	push r14

	mov r12, rdi ; r12 = a
        call strLen
        inc rax ; strlen(a) + 1 ('\0')

        mov rdi, rax ; rdi = strlen(a) + 1
	mov rsi, 1
        call calloc

        mov r13, rax ; r13 = strCopy
        mov r14, rax ; r14 = strCopy

        .bucle_strcpy:
                mov al, BYTE [r12]
                mov BYTE [r13], al

                inc r12
                inc r13

                cmp al, 0 ; al == '\0'
                jne .bucle_strcpy

	.fin:
		mov rax, r14 ; return strCopy

		pop r14
		pop r13
		pop r12

		add rsp, 8
		pop rbp
		ret

; void strPrint(char* a, FILE* pFile);
strPrint:
	push rbp
	mov rbp, rsp

	cmp BYTE [rdi], 0 ; dil == '\0'
	je .imprimir_null
	jmp .imprimir_string

	.imprimir_null:
		mov rdi, null_str

	.imprimir_string:
		call fputs

	.fin:
		pop rbp
		ret

;uint32_t strLen(char* a);
strLen:
	push rbp
	mov rbp, rsp

	xor rax, rax

        .bucle_strlen:
                cmp BYTE [rdi], 0 ; dil == '\0'
                je .return

                inc rdi
                inc eax
                jmp .bucle_strlen

	.return:
		pop rbp
		ret

;int32_t strCmp(char* a, char* b);
strCmp:
	push rbp
	mov rbp, rsp

	xor rax, rax
	xor rdx, rdx

	.bucle_strcmp:
		mov al, BYTE [rdi]
		mov dl, BYTE [rsi]

		cmp al, dl
		jne .diferentes

		cmp al, 0 ; al == '\0'
		je .iguales

		inc rdi
		inc rsi
		jmp .bucle_strcmp

	.diferentes:
		cmp eax, edx
		ja .mayor
		jb .menor

	.mayor:
		mov eax, -1 ; return -1
		jmp .fin

	.menor:
		mov eax, 1 ; return 1
		jmp .fin

	.iguales:
		mov eax, 0 ; return 0

	.fin:
		pop rbp
		ret
        
;void strDelete(char* a);
strDelete:
	push rbp
	mov rbp, rsp

        call free

	pop rbp
        ret

; ---------------- Array ----------------

; uint8_t arrayGetSize(array_t* a);
arrayGetSize:
	push rbp
	mov rbp, rsp

	xor rax, rax
	mov al, BYTE [rdi + OFFSET_ARRAY_SIZE] ; al = a->type

	pop rbp
	ret

; void arrayAddLast(array_t* a, void* data);
arrayAddLast:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15
	
	mov r14, rdi ; r14 = array_t*
	mov r15, rsi ; r15 = void*

	mov r12b, BYTE [r14 + OFFSET_ARRAY_SIZE] ; r12 = size
	mov r13b, BYTE [r14 + OFFSET_ARRAY_CAPACITY] ; r13 = capacity
	cmp r12b, r13b
	jae .fin ; size >= capacity

	mov rdi, r15 ; rdi = data
	mov esi, DWORD [r14 + OFFSET_ARRAY_TYPE] ; rsi = type
	call cloneDataByType

	mov rdx, QWORD [r14 + OFFSET_ARRAY_DATA] ; rdx = data
	mov QWORD [rdx + r12 * 8], rax ; data[size] = copia
	inc r12b
	mov BYTE [r14 + OFFSET_ARRAY_SIZE], r12b ; size++

	.fin:
		pop r15
		pop r14
		pop r13
		pop r12
		
		pop rbp
		ret

; void* arrayGet(array_t* a, uint8_t i);
arrayGet:
	push rbp
	mov rbp, rsp

	xor rax, rax
	cmp sil, BYTE [rdi + OFFSET_ARRAY_SIZE]
	jae .fin ; i >= size

	mov r8, QWORD [rdi + OFFSET_ARRAY_DATA] ; r8 = a->data
	mov rax, QWORD [r8 + rsi * 8] ; rax = data[i]

	.fin:
		pop rbp
		ret

; array_t* arrayNew(type_t t, uint8_t capacity);
arrayNew:
	push rbp
	mov rbp, rsp
	sub rsp, 8

	push r12
	push r13
	push r14

	mov r12d, edi ; r120d = t
	mov r13b, sil ; r13b = capacity

	mov rdi, 1
	mov rsi, SIZEOF_ARRAY
	call calloc ; rax = puntero al struct 'array_t'

	mov r14, rax ; r14 = puntero al struct

	xor rax, rax
   	mov al, r13b ; al = capacity
    	shl rax, 3 ; rax = capacity * 8 (cada puntero ocupa 8 bytes)

	mov rdi, 1
    	mov rsi, rax
    	call calloc ; rax = puntero al arreglo 'data'

	mov DWORD [r14 + OFFSET_ARRAY_TYPE], r12d ; asigno 'type' al struct
    	mov BYTE [r14 + OFFSET_ARRAY_CAPACITY], r13b ; asigno 'capacity' al struct
	mov QWORD [r14 + OFFSET_ARRAY_DATA], rax ; asigno puntero al arreglo 'data' en el struct

	mov rax, r14 ; rax = puntero al struct

	pop r14
	pop r13
    	pop r12

	add rsp, 8
	pop rbp
	ret

; void* arrayRemove(array_t* a, uint8_t i);
arrayRemove:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = a
	mov r13b, BYTE [r12 + OFFSET_ARRAY_SIZE] ; r13b = size
	mov r14, QWORD [r12 + OFFSET_ARRAY_DATA] ; r14 = a->data
	xor r15, r15
	mov r15b, sil ; r15 = i

	cmp r15b, r13b
	jae .fueraDeRango ; i >= size

	mov rax, QWORD [r14 + r15 * 8] ; rax = data[i] (valor a devolver)
    	push rax

	xor rsi, rsi
    	mov rsi, r15 ; rsi = j = i
	
	.moverLoop:
		xor rdx, rdx
		mov dl, r13b ; dl = size
		dec rdx
		cmp rsi, rdx
		jae .reducirSize ; j >= size - 1

		mov rax, QWORD [r14 + rsi * 8 + 8] ; rax = data[j + 1]
       		mov QWORD [r14 + rsi * 8], rax ; data[j] = data[j + 1]

		inc rsi ; j++
		jmp .moverLoop

	.reducirSize:
		dec BYTE [r12 + OFFSET_ARRAY_SIZE] ; a->size--

		xor rax, rax
        	mov al, BYTE [r12 + OFFSET_ARRAY_SIZE] ; al = new size
        	mov QWORD [r14 + rax * 8], 0 ; data[new_size] = NULL

		pop rax
		jmp .fin

	.fueraDeRango:
		xor rax, rax

	.fin:
		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret

; void arraySwap(array_t* a, uint8_t i, uint8_t j);
arraySwap:
	push rbp
	mov rbp, rsp

	cmp sil, BYTE [rdi + OFFSET_ARRAY_SIZE]
	jae .fin ; i >= size
	cmp dl, BYTE [rdi + OFFSET_ARRAY_SIZE]
	jae .fin ; j >= size

	mov rax, QWORD [rdi + OFFSET_ARRAY_DATA] ; rax = data
	mov r8, QWORD [rax + rsi * 8] ; r8 = data[i]
	mov r9, QWORD [rax + rdx * 8] ; r9 = data[j]
	mov QWORD [rax + rsi * 8], r9 ; data[i] = data[j]
	mov QWORD [rax + rdx * 8], r8 ; data[j] = data[i]

	.fin:
		pop rbp
		ret

; void arrayDelete(array_t* a);
arrayDelete:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = a
	mov r13b, BYTE [r12 + OFFSET_ARRAY_SIZE] ; r13b = size
	mov r14, QWORD [r12 + OFFSET_ARRAY_DATA] ; r14 = a->data
	mov r15d, DWORD [r12 + OFFSET_ARRAY_TYPE] ; r15d = type

	xor rbx, rbx ; rbx = i = 0

	.liberarElementos:
		cmp bl, r13b
		jae .liberarArreglo ; i >= size

		mov rdi, QWORD [r14 + rbx * 8] ; rdi = data[i]
		cmp rdi, 0 ; verifico que no sea NULL
        	jz .siguienteElemento

		mov rsi, r15 ; rsi = type
		call deleteDataByType

	.siguienteElemento:
		inc rbx
		jmp .liberarElementos

	.liberarArreglo:
		mov rdi, r14
		call free ; free(a->data)

		mov rdi, r12
		call free ; free(a)

	.fin:
		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret

;void arrayPrint(array_t* a, FILE* pFile);
arrayPrint:
	push rbp
	mov rbp, rsp
	sub rsp, 8

	push rbx
	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = a
	mov r13, rsi ; r13 = pFile
	xor r14, r14
	mov r14b, BYTE [r12 + OFFSET_ARRAY_SIZE] ; r14b = size
	mov r15, QWORD [r12 + OFFSET_ARRAY_DATA] ; r15 = a->data

	mov rdi, r13
	mov rsi, apertura_corchetes
	call fprintf

	xor rbx, rbx ; rbx = i = 0

	.imprimirElementos:
		cmp bl, r14b
		jae .fin ; i >= size

		cmp bl, 0 ; si es el primer elemento => sin coma
		jz .sinComma

		mov rdi, r13
		mov rsi, coma
		call fprintf

	.sinComma:
		xor rax, rax
		mov al, bl ; rax = i

		mov rdi, QWORD [r15 + rax * 8] ; rdi = data[i]
		mov esi, DWORD [r12 + OFFSET_ARRAY_TYPE] ; rsi = type
		mov rdx, r13 ; rdx = pFile
		call printDataByType

	.siguienteElemento:
		inc bl
		jmp .imprimirElementos

	.fin:
		mov rdi, r13
		mov rsi, cierre_corchetes
		call fprintf

		pop r15
		pop r14
		pop r13
		pop r12
		pop rbx

		add rsp, 8
		pop rbp
		ret

; ---------------- Card ----------------

; card_t* cardNew(char* suit, int32_t* number);
cardNew:
	push rbp
	mov rbp, rsp
	sub rsp, 8

	push rbx
	push r12
	push r13

	mov r12, rdi ; r12 = suit (char*)
	mov r13, rsi ; r13 = number (int32_t*)

	mov rdi, 1
	mov rsi, SIZEOF_CARD
	call calloc
	mov rbx, rax ; rbx = card
	
	mov rdi, r12 ; rdi = suit
	call strClone
	mov QWORD [rbx + OFFSET_CARD_SUIT], rax

	mov rdi, r13 ; rdi = number
	call intClone
	mov QWORD [rbx + OFFSET_CARD_NUMBER], rax

	mov rdi, 3 ; card_t = type_t 3
	call listNew
	mov QWORD [rbx + OFFSET_CARD_STACKED], rax

	mov rax, rbx ; return card

	pop r13
	pop r12
	pop rbx

	add rsp, 8
	pop rbp
	ret

;char* cardGetSuit(card_t* c);
cardGetSuit:
	push rbp
	mov rbp, rsp

	mov rax, QWORD [rdi + OFFSET_CARD_SUIT] ; rax = c->suit

	pop rbp
	ret

;int32_t* cardGetNumber(card_t* c);
cardGetNumber:
	push rbp
	mov rbp, rsp

	mov rax, QWORD [rdi + OFFSET_CARD_NUMBER] ; rax = c->number

	pop rbp
	ret

;list_t* cardGetStacked(card_t* c);
cardGetStacked:
	push rbp
	mov rbp, rsp

	mov rax, QWORD [rdi + OFFSET_CARD_STACKED] ; rax = c->stacked

	pop rbp
	ret

;void cardPrint(card_t* c, FILE* pFile);
cardPrint:
	push rbp
	mov rbp, rsp

	push r12
	push r13

	mov r13, rdi ; r13 = c
	mov r12, rsi ; r12 = pFile

	mov rdi, abro_card ; rdi = "{"
	mov rsi, r12 ; rsi = pFile
	call fputs

	mov rdi, r13 ; rdi = c
	call cardGetSuit
	mov rdi, rax ; rdi = card->suit
	mov rsi, r12 ; rsi = pFile
	call strPrint

	mov rdi, guion ; rdi = "-"
	mov rsi, r12 ; rsi = pFile
	call fputs

	mov rdi, r13 ; rdi = c
	call cardGetNumber
	mov rdi, rax ; rdi = card->number
	mov rsi, r12 ; rsi = pFile
	call intPrint

	mov rdi, guion ; rdi = "-"
	mov rsi, r12 ; rsi = pFile
	call fputs

	mov rdi, r13 ; rdi = c
	call cardGetStacked
	mov rdi, rax ; rdi = card->stacked
	mov rsi, r12 ; rsi = pFile
	call listPrint

	mov rdi, cierro_card ; rdi = "}"
	mov rsi, r12 ; rsi = pFile
	call fputs

	pop r13
	pop r12

	pop rbp
	ret

;int32_t cardCmp(card_t* a, card_t* b);
cardCmp:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = a
	mov r13, rsi ; r13 = b

	mov rdi, r12 ; rdi = a
	call cardGetSuit
	mov r14, rax ; r14 = a->suit

	mov rdi, r13 ; rdi = b
	call cardGetSuit

	mov rdi, r14 ; rdi = a->suit
	mov rsi, rax ; rsi = b->suit
	call strCmp
	cmp eax, 0
	jne .fin ; si no son iguales se retorna

	; si los suits son iguales, comparar los números:
	mov rdi, r12 ; rdi = a
	call cardGetNumber
	mov r14, rax ; r14 = a->number

	mov rdi, r13 ; rdi = b
	call cardGetNumber
	mov r15, rax ; r15 = b->number

	mov r14d, DWORD [r14] ; r14d = *a->number
	mov r15d, DWORD [r15] ; r15d = *b->number

	cmp r14d, r15d
	je .numbers_equal
	jl .number_a_less
	jg .number_a_greater

	.numbers_equal:
		mov rax, 0 ; return 0
		jmp .fin

	.number_a_less:
		mov rax, 1 ; return 1
		jmp .fin

	.number_a_greater:
		mov rax, -1 ; return -1

	.fin:
		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret

;card_t* cardClone(card_t* c);
cardClone:
	push rbp
	mov rbp, rsp

	push r12
	push r13
	push r14
	push r15

	mov r12, rdi ; r12 = c

	mov rdi, 1
	mov rsi, SIZEOF_CARD
	call calloc
	mov r13, rax ; r13 = cardCopy

	mov rdi, r12 ; rdi = c
	call cardGetSuit
	mov rdi, rax ; rdi = c->suit
	call strClone
	mov QWORD [r13 + OFFSET_CARD_SUIT], rax ; cardCopy->suit = c->suit

	mov rdi, r12 ; rdi = c
	call cardGetNumber
	mov rdi, rax ; rdi = c->number
	call intClone
	mov QWORD [r13 + OFFSET_CARD_NUMBER], rax ; cardCopy->number = c->number

	mov rdi, r12 ; rdi = c
	call cardGetStacked
	cmp rax, 0

	mov edi, 3 ; card_t = type_t 3
	call listNew
	mov r14, rax ; r14 = lista nueva

	mov rdi, r12
	call cardGetStacked
	mov rdi, rax ; rdi = c->stacked
	mov r15, QWORD [rdi + OFFSET_LIST_FIRST] ; r15 = c->stacked->first

	.clone_list_loop:
		cmp r15, 0
		je .fin

		mov rdi, r14 ; rdi = lista nueva
		mov rsi, QWORD [r15 + OFFSET_LISTELEM_DATA] ; rsi = carta original
		call listAddLast

		mov r15, QWORD [r15 + OFFSET_LISTELEM_NEXT] ; r15 = c->stacked->first->next
		jmp .clone_list_loop

	.fin:
		mov QWORD [r13 + OFFSET_CARD_STACKED], r14 ; cardCopy->stacked = lista nueva
		mov rax, r13

		pop r15
		pop r14
		pop r13
		pop r12

		pop rbp
		ret

;void cardAddStacked(card_t* c, card_t* card);
cardAddStacked:
	push rbp
	mov rbp, rsp

	push r12
	push r13

	mov r12, rdi ; r12 = c
	mov r13, rsi ; r13 = card

	mov rdi, r12 ; rdi = c
	call cardGetStacked
	mov rdi, rax ; rdi = c->stacked
	mov rsi, r13 ; rsi = card
	call listAddFirst

	pop r13
	pop r12

	pop rbp
	ret

;void cardDelete(card_t* c);
cardDelete:
	push rbp
	mov rbp, rsp
	sub rsp, 8

	push r12

	mov r12, rdi ; r12 = c

	call cardGetSuit
	mov rdi, rax ; rdi = c->suit
	call strDelete ; free(c->suit)

	mov rdi, r12 ; rdi = c
	call cardGetNumber
	mov rdi, rax ; rdi = c->number
	call intDelete ; free(c->number)

	mov rdi, r12 ; rdi = c
	call cardGetStacked
	mov rdi, rax ; rdi = c->stacked
	call listDelete ; free(c->stacked)

	.fin:
		mov rdi, r12 ; rdi = c
		call free ; free(c)

		pop r12

		add rsp, 8
		pop rbp
		ret