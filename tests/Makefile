
HEADERS = libasm.h libasmtest.h
TEST_HELPERS = generate_things.c
INC = -I.
LIB = -L.. -lasm
CFLAGS = -Wall -Werror -Wextra -g

all: test_mandatory test_bonus

fclean: clean

clean:
	$(RM) -rf *.dSYM
	$(RM) *.out

lib:
	make -C ..

lib_bonus:
	make -C .. BONUS=1

test_mandatory: strlen strcpy strcmp strdup read write

test_bonus: atoi_base push_front list_size remove_if list_sort

list_sort: lib_bonus $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) list_sort_main.c -o ft_list_sort.out
ifdef RUN
	@./ft_list_sort.out
	@./ft_list_sort.out 16 "evenodd"
	@./ft_list_sort.out 27 "alpharev"
	@./ft_list_sort.out 8 "alpharev" "donull"
endif

remove_if: lib_bonus $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) list_remove_if_main.c -o ft_remove_if.out
ifdef RUN
	@./ft_remove_if.out 10
	@./ft_remove_if.out 15 0 static
	@./ft_remove_if.out 15 0 first2chars_gt150
	@./ft_remove_if.out 15 "Odd element" make_NULL
	@./ft_remove_if.out 15 "Odd element"
	@./ft_remove_if.out 15 "Even element"
endif

list_size: lib_bonus $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) list_size_main.c -o ft_list_size.out
ifdef RUN
	@./ft_list_size.out
	@./ft_list_size.out
	@./ft_list_size.out 50
	@./ft_list_size.out
endif

push_front: lib_bonus $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) list_push_front_main.c -o ft_push_front.out
ifdef RUN
	@./ft_push_front.out
endif

atoi_base: lib_bonus $(HEADERS)
	@$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) atoi_base_main.c -o ft_atoi_base.out
ifdef RUN
	@echo "Comparing with strtoll() only works with non-weird base strings"
	@./ft_atoi_base.out "-123"
	@./ft_atoi_base.out "123"
	@./ft_atoi_base.out "9846513"
	@./ft_atoi_base.out "10000" "01"
	@./ft_atoi_base.out "01111" "10"
	@./ft_atoi_base.out "deadbeef" "0123456789abcdef"
	@./ft_atoi_base.out "DEADBEEF" "0123456789ABCDEF"
	@./ft_atoi_base.out "SomeLongAss base str or base 63" "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz "
	@./ft_atoi_base.out "+-20" "0123456789"
	@./ft_atoi_base.out "      -20" "0123456789"
	@./ft_atoi_base.out "      +20-spaces and positive" "0123456789"
	@./ft_atoi_base.out "20- base contains char twice" "01234567890"
	@./ft_atoi_base.out random random random
	@./ft_atoi_base.out random random random
endif

write: lib $(HEADERS)
	@$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) write_main.c -o ft_write.out
ifdef RUN
	@./ft_write.out
	@./ft_write.out
	@./ft_write.out
	@./ft_write.out badfildes 25
endif

read: lib $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) read_main.c -o ft_read.out
ifdef RUN
	@./ft_read.out 80 25 #bad filedes
	@./ft_read.out 80 n y
endif

strdup: lib $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) strdup_main.c -o ft_strdup.out
ifdef RUN
	@./ft_strdup.out
	@./ft_strdup.out
	@./ft_strdup.out
	@./ft_strdup.out
endif

strcmp: lib $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) strcmp_main.c -o ft_strcmp.out
ifdef RUN
	@./ft_strcmp.out "a" "A"
	@./ft_strcmp.out "test" "test" 0 200
	@./ft_strcmp.out "test" "test" 200 0
	@./ft_strcmp.out "test" "test" 200 199
	@./ft_strcmp.out "test" "test" 201 201
	@./ft_strcmp.out random
	@./ft_strcmp.out random
	@./ft_strcmp.out random_up
	@./ft_strcmp.out random_up
	@./ft_strcmp.out random_down
	@./ft_strcmp.out random_down
endif

strcmp_sanitize: lib $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) -fsanitize=address strcmp_sanitize.c -o ft_sanitize_strcmp.out
ifdef RUN
	./ft_sanitize_strcmp.out
endif

strcpy: lib $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) strcpy_main.c -o ft_strcpy.out
ifdef RUN
	@./ft_strcpy.out
	@./ft_strcpy.out 1
	@./ft_strcpy.out 2
	@./ft_strcpy.out 4
	@./ft_strcpy.out 8
	@./ft_strcpy.out 50
	@./ft_strcpy.out 120
	@./ft_strcpy.out
endif

strlen_sanitize: lib $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) -fsanitize=address strlen_sanitize.c -o ft_sanitize_strlen.out
ifdef RUN
	./ft_sanitize_strlen.out
endif

strlen: lib $(HEADERS)
	$(CC) $(CFLAGS) $(LIB) $(INC) $(TEST_HELPERS) strlen_main.c -o ft_strlen.out
ifdef RUN
	@./ft_strlen.out
	@./ft_strlen.out 1
	@./ft_strlen.out 2
	@./ft_strlen.out 3
	@./ft_strlen.out 4
	@./ft_strlen.out 8
	@./ft_strlen.out 16
	@./ft_strlen.out 32
	@./ft_strlen.out
	@./ft_strlen.out
endif
