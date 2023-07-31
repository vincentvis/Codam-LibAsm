# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vincent <vincent@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/05 15:22:46 by vincent       #+#    #+#                  #
#    Updated: 2021/03/28 11:57:50 by vincent       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

all: $(NAME)

SRC = ft_strlen.s \
		ft_strcpy.s \
		ft_strcmp.s \
		ft_strdup.s \
		ft_write.s \
		ft_read.s

BONUSFILES = ft_atoi_base_bonus.s \
		ft_list_push_front_bonus.s \
		ft_list_size_bonus.s \
		ft_list_remove_if_bonus.s \
		ft_list_sort_bonus.s

ifdef BONUS
FILES = $(SRC) $(BONUSFILES)
else
FILES = $(SRC)
endif

OBJ = $(addprefix objs/, $(FILES:.s=.o))

objs/%.o: %.s
	$(shell mkdir -p $(dir $@))
	nasm -g -O0 -f macho64 $< -o $@

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

BONUSOBJ = $(addprefix objs/, $(BONUSFILES:.s=.o))

bonus:
	@make BONUS=1

build_tests:
	@make -C tests test_mandatory

build_bonus_tests: bonus
	@make -C tests test_bonus

run_tests:
	@make -C tests test_mandatory RUN=1

run_bonus_tests: bonus
	@make -C tests test_bonus RUN=1

clean:
	$(RM) $(OBJ)
ifndef BONUS
	$(RM) $(BONUSOBJ)
endif
	$(RM) -r objs/

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)
