##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CC		=		gcc

SRC		=		src/main.c

OBJ		=		$(SRC:.c=.o)

all: compil_bin

compil_bin: $(OBJ)
	$(CC)

clean:
	rm

fclean: clean


re: fclean all