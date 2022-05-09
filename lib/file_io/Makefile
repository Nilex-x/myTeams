##
## EPITECH PROJECT, 2022
## myTeams_collaborate
## File description:
## Makefile
##

NAME = libfile_io.a

SRC = $(shell find -name '*.c')

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I../../include -luuid -g3

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp file_io.h ../../include/

all:	$(NAME) fclean

clean:
	rm -f *~

fclean:		clean
	rm -f $(OBJ)

re:		fclean all