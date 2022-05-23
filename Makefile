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
					src_server/server/manage_init.c \
					src_server/teams/sort_command.c \
					src_server/teams/manage_init_data.c \
					src_server/teams/manage_user_infos.c \
					src_server/teams/manage_users.c \
					src_server/teams/manage_messages.c \
					src_server/teams/send_message.c \
					src_server/teams/manage_data_send.c \
					src_server/teams/read_unread_messages.c \

OBJ_SERV	=		$(SRC_SERV:.c=.o)

SRC_CLIENT	=		src_client/teams_client.c

OBJ_CLIENT	=		$(SRC_CLIENT:.c=.o)

HEADER_DIR	=		include

LIB_PATH	=		libs

LIB_SO_PATH	=		myteams

NAME_LIB	=		my_teams

FILE_LIB	=		file_io

SERV_NAME	=		myteams_server

LIB_SO_NAME	=		myteams

CLIENT_NAME	=		myteams_cli

CFLAGS		=		-W -Wall -Wextra -I$(HEADER_DIR) -L$(LIB_PATH) -l$(NAME_LIB) -l$(LIB_SO_NAME) -g3

all: compil_lib compil_server compil_client

compil_lib:
	@make -C $(LIB_PATH)

compil_server: $(OBJ_SERV)
	$(CC) -o $(SERV_NAME) $(OBJ_SERV) -I$(HEADER_DIR) -L$(LIB_PATH) -L$(LIB_PATH)/$(LIB_SO_PATH)  -l$(NAME_LIB) -l$(FILE_LIB) -l$(LIB_SO_NAME) -luuid

compil_client: $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) -I$(HEADER_DIR) -L$(LIB_PATH) -L$(LIB_PATH)/$(LIB_SO_PATH) -l$(NAME_LIB) -l$(LIB_SO_NAME)

debug:compil_lib debug_server debug_client

debug_server: $(OBJ_SERV)
	$(CC) -o $(SERV_NAME) $(OBJ_SERV) -I$(HEADER_DIR) -L$(LIB_PATH) -L$(LIB_PATH)/$(LIB_SO_PATH) -l$(NAME_LIB) -l$(FILE_LIB) -l$(LIB_SO_NAME) -luuid -g3

debug_client: $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) -I$(HEADER_DIR) -L$(LIB_PATH) -L$(LIB_PATH)/$(LIB_SO_PATH) -l$(NAME_LIB) -l$(FILE_LIB) -l$(LIB_SO_NAME) -g3

clean:
	@make clean -C $(LIB_PATH)
	rm -f $(OBJ_SERV)
	rm -f $(OBJ_CLIENT)

fclean:
	@make fclean -C $(LIB_PATH)
	rm -f $(OBJ_SERV)
	rm -f $(OBJ_CLIENT)
	rm -f $(SERV_NAME)
	rm -f $(CLIENT_NAME)

re: fclean all

.PHONY: compil_server debug fclean clean re all
