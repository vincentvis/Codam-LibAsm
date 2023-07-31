; **************************************************************************** ;
;                                                                              ;
;                                                         ::::::::             ;
;    ft_list_size_bonus.s                               :+:    :+:             ;
;                                                      +:+                     ;
;    By: vincent <vincent@student.codam.nl>           +#+                      ;
;                                                    +#+                       ;
;    Created: 2021/02/27 17:38:36 by vincent       #+#    #+#                  ;
;    Updated: 2021/03/12 15:23:18 by vincent       ########   odam.nl          ;
;                                                                              ;
; **************************************************************************** ;

;	int		ft_list_size(t_list *begin_list);
;	rdi = *begin_list
;	[rdi + 8] = *next

section .text

global _ft_list_size
extern _malloc
_ft_list_size:
	xor							rax, rax
	jmp							.size_loop

.size_counter:
	inc							rax
.size_loop:
	cmp							rdi, 0
	je							.ft_list_size_done
	mov							rdi, [rdi + 8]
	jmp							.size_counter

.ft_list_size_done:
	ret
