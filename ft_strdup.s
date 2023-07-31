; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_strdup.s                                        :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/03/08 18:02:25 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:23:00 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;	char *strdup(const char *s1);
;	Strdup() allocates sufficient memory for a copy of the string s1,
;	does the copy, and returns a pointer to it.
;	The pointer may subsequently be used as an argument to the function free(3).
;
;	rdi register contains pointer to s1

section .text

global _ft_strdup
extern _malloc
extern _ft_strlen
extern _ft_strcpy

_ft_strdup:
	push						rbp
	mov							rbp, rsp
	and							rsp, 0xfffffffffffffff0			; align on 16 bits
	; stack needs to be aligned before call!
	call						_ft_strlen						; rdi already contains s1, so that can go into strlen
																; now rax should contain length of string
	inc							rax								; increment rax to make space for terminating char
	push						rdi								; push rdi to stack since we need it later for strcpy
	push						r8								; push something else that is 8 bits to align stack
	mov							rdi, rax						; set strlen as rdi for input into malloc
	call						_malloc							; call malloc
	pop							r8								; pop both and have stack alignment again
	pop							rsi								; pop rdi from stack into rsi
	cmp							rax, 0							; check return of malloc
	je							.strdup_alloc_error				; if malloced returned NULL we dont copy and just return NULL
	mov							rdi, rax						; set the pointer returned from malloc into rdi as input for strcpy
	call						_ft_strcpy						; call strcpy
.strdup_alloc_error:
	mov							rsp, rbp
	pop							rbp
	ret															; return
