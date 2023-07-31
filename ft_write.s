; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_write.s                                         :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/03/08 18:00:12 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:23:08 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;	ssize_t write(int fildes, const void *buf, size_t nbyte);
;	write() attempts to write nbyte of data to the object
;	referenced by the descriptor fildes from the buffer pointed
;	to by buf.
;	rdi = filedes
;	rsi = buf
;	rcx/rdx = nbyte

section .text

global _ft_write
extern ___error
_ft_write:
	mov							rax, 0x2000004					; syscalls are done with 0x2000000 offset for some reason
	syscall
	jc							.ft_write_error
	ret

.ft_write_error:
	push						r15								; r15 is callee save
	push						rbp
	mov							rbp, rsp						; create new stack frame
	and							rsp, 0xfffffffffffffff0			; align stack on 16 bit boundary
	mov							r15, rax						; copy error number in r15
	call						___error						; call external function
	mov							[rax], r15						; move our error number to the pointer returned by error
	mov							rax, -1							; set return value to -1
	mov							rsp, rbp						; resets rsp when needed
	pop							rbp								; gets back the original stack base pointer
	pop							r15								; restore r15
	ret															; return
