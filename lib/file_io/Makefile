##
## EPITECH PROJECT, 2022
## myTeams_collaborate
## File description:
## Makefile
##

NAME = file_io.a

SRC = $(shell find -name '*.c')

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I../../include

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ..
	cp file_io.h ../../include/
	make fclean

all:	$(NAME) fclean

clean:
	rm -f *~

fclean:		clean
	rm -f $(OBJ)

re:		fclean all