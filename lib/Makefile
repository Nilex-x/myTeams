##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

SRC			=


OBJ 		=		$(SRC:.c=.o)

NAME_LIB	=		libmy_teams.a

CFLAGS		=		-W -Wall -Wextra

all: compil_files create_lib

compil_files: $(OBJ)
	@gcc -c $(SRC) -Wall -Wextra -I../include -lmy -g3
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
