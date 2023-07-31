; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_list_push_front_bonus.s                         :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/02/27 17:21:04 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:22:55 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;	void    ft_list_push_front(t_list **begin_list, void *data);
;	So i'm guessing we basically also have to do create_elem?
;	rdi = **begin_list
;	rsi = data

section .text

global _ft_list_push_front
extern _malloc
_ft_list_push_front:
	push						rbp
	mov							rbp, rsp
	and							rsp, 0xfffffffffffffff0			; align stack frame
	cmp							rdi, 0
	je							.null_error
	push						rdi								; pushes 2 time 8 bytes,
	push						rsi								; so still 16 bit aligned for malloc
	mov							rdi, 16							; t_list = 2 pointers = 16 bits
	call						_malloc							; allocated pointer should be in rax after this
	pop							rsi								;
	pop							rdi								;
	cmp							rax, 0							; check if malloc returned 0
	je							.null_error
	mov							r8, [rdi]						; temp store *list_item in r8
	mov							[rax], rsi						; set data
	mov							[rax + 8], r8					; set next to [rdi] (can be 0)
	mov							[rdi], rax

.null_error:
	mov							rsp, rbp
	pop							rbp
	ret
