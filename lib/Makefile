##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

LIB_PATH	=	lib/

LIB_NAME	=	libmy_teams.a

all: compil_lib

compil_lib:
	@make -C $(LIB_PATH)
	mv $(LIB_PATH)$(LIB_NAME) .

clean:
	@make clean -C $(LIB_PATH)

fclean: clean
	@rm -f $(LIB_NAME)

