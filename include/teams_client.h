/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** teams_client
*/

#ifndef TEAMS_CLIENT_H_
	#define TEAMS_CLIENT_H_

	#include <arpa/inet.h>
	#include <stdio.h>
	#include <string.h>
	#include <sys/socket.h>
	#include <unistd.h>
	#include <sys/select.h>

	#include "lib.h"

    #define WRITE 0
    #define READ 1
    #define LENGTH_COMMAND 512


typedef struct info_s {
	int socket;
	int read_write;
	buffer_t read_buffer;
	char *write_buffer;
	fd_set readfds;
	fd_set writefds;
} info_t;


// client_command: manage user and server input

void get_server_command(info_t *info);
void get_user_command(info_t *info);
void write_command(info_t *info);
void manage_client(info_t *info);
void clear_list(info_t *info);


// manage user command

int user_command(info_t *info);

#endif /* !TEAMS_CLIENT_H_ */
