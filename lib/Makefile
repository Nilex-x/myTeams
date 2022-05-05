##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

SRC			=		src/my_str_to_word_array.c \
					src/find_char_in_str.c \
					src/array_to_str.c \
					src/clear_str.c \
					src/remove_to_last_char.c \
					src/str_to_word_array_separator.c \
					src/strlen_array.c \
					src/intlen.c \
					src/free_array.c \
					src/remove_part_of_array.c \
					src/strcatdup.c \
					src/manage_buffer.c


OBJ 		=		$(SRC:.c=.o)

NAME_LIB	=		libmy_teams.a

INCLUDE_PATH	=	../include

CFLAGS		=		-W -Wall -Wextra -I$(INCLUDE_PATH)

all: compil_files create_lib

compil_files: $(OBJ)
	@gcc -c $(SRC) -Wall -Wextra -I$(INCLUDE_PATH)
	@echo "Compil finish"

create_lib:
	@ar cr $(NAME_LIB) $(OBJ)
	@echo "Lib create"

clean:
	@rm -f $(OBJ)
	@echo "all .o is remove"

fclean: clean
	@rm -f $(NAME_LIB)
	@echo "Lib is remove"
