##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CC			=		gcc

SRC_SERV	=		src_server/server/teams_serv.c \
					src_server/server/handle_client.c \
					src_server/server/handle_communication.c \
					src_server/server/manage_server.c \
					src_server/server/utils.c

OBJ_SERV	=		$(SRC_SERV:.c=.o)

SRC_CLIENT	=		src_client/teams_client.c

OBJ_CLIENT	=		$(SRC_CLIENT:.c=.o)

HEADER_DIR	=		include

LIB_PATH	=		lib

NAME_LIB	=		my_teams

SERV_NAME	=		myteams_server

CLIENT_NAME	=		myteams_cli

CFLAGS		=		-W -Wall -Wextra -I$(HEADER_DIR) -L$(LIB_PATH) -l$(NAME_LIB) -g3

all: compil_lib compil_server compil_client

compil_lib:
	@make -C $(LIB_PATH)

compil_server: $(OBJ_SERV)
	$(CC) -o $(SERV_NAME) $(OBJ_SERV) -I$(HEADER_DIR) -L$(LIB_PATH) -l$(NAME_LIB)

compil_client: $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) -I$(HEADER_DIR) -L$(LIB_PATH) -l$(NAME_LIB)

debug:compil_lib debug_server debug_client

debug_server: $(OBJ_SERV)
	$(CC) -o $(SERV_NAME) $(OBJ_SERV) -I$(HEADER_DIR) -L$(LIB_PATH) -l$(NAME_LIB) -g3

debug_client: $(OBJ_SERV)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) -I$(HEADER_DIR) -L$(LIB_PATH) -l$(NAME_LIB) -g3

clean:
	@make clean -C $(LIB_PATH)
	rm -f $(OBJ_SERV)

fclean:
	@make fclean -C $(LIB_PATH)
	rm -f $(OBJ_SERV)
	rm -f $(SERV_NAME)

re: fclean all

.PHONY: compil_server debug fclean clean re all
