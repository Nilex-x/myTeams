##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

LIB_PATH	=	lib/

LIB_NAME	=	libmy_teams.a

FILE_IO_PATH	=	file_io/

FILE_IO_NAME	=	libfile_io.a

all: compil_lib compil_file_io

compil_lib:
	@make -C $(LIB_PATH)
	mv $(LIB_PATH)$(LIB_NAME) .

compil_file_io:
	@make -C $(FILE_IO_PATH)
	mv $(FILE_IO_PATH)$(FILE_IO_NAME) .

clean:
	@make clean -C $(LIB_PATH)
	@make clean -C $(FILE_IO_PATH)

fclean:
	@make fclean -C $(LIB_PATH)
	@make fclean -C $(FILE_IO_PATH)
	@rm -f $(LIB_NAME) $(FILE_IO_NAME)


re: fclean all
