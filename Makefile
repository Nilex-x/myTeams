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
					src_server/teams/manage_teams.c \
					src_server/teams/manage_create_cmd.c \
					src_server/teams/send_message.c \
					src_server/teams/manage_data_send.c \
					src_server/teams/read_unread_messages.c \
					src_server/teams/manage_list_cmd.c \
					src_server/teams/manage_info_cmd.c \
					src_server/teams/manage_connection.c \
					src_server/teams/manage_subscribe.c \
					src_server/teams/manage_unsubscribe.c \
					src_server/teams/send_list.c \
					src_server/teams/manage_notif.c \
					src_server/teams/manage_channels.c \
					src_server/teams/manage_thread.c

OBJ_SERV	=		$(SRC_SERV:.c=.o)

SRC_CLIENT	=		src_client/teams_client.c \
					src_client/client_command.c \
					src_client/manage_user_command.c \
					src_client/str_to_array.c \
					src_client/server_response.c \
					src_client/informative_response.c \
					src_client/connection_response.c \
					src_client/error_response_0.c \
					src_client/error_response_1.c \
					src_client/error_response_2.c \
					src_client/info_response.c \
					src_client/create_response.c \
					src_client/list_response.c \
					src_client/user_response.c \
					src_client/user_data_response.c \
					src_client/notif_response_01.c \
					src_client/notif_response_2.c \

OBJ_CLIENT	=		$(SRC_CLIENT:.c=.o)

HEADER_DIR	=		include

LIB_PATH	=		libs

LIB_SO_PATH	=		myteams

NAME_LIB	=		my_teams

FILE_LIB	=		file_io

SERV_NAME	=		myteams_server

LIB_SO_NAME	=		myteams

CLIENT_NAME	=		myteams_cli

CFLAGS		=		-W -Wall -Wextra -I$(HEADER_DIR)

LDFLAGS		=		-Llibs 	-Llibs/myteams -lmy_teams -lmyteams -lfile_io -luuid

all: compil_lib compil_server compil_client

compil_lib:
	@make -C $(LIB_PATH)

compil_server: $(OBJ_SERV)
	$(CC) -o $(SERV_NAME) $(OBJ_SERV) $(LDFLAGS)

compil_client: $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) $(LDFLAGS)


debug: CFLAGS += -g3
debug: compil_lib compil_server compil_client

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

.PHONY: debug fclean clean re all
