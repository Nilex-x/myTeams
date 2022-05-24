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

// str to array

void replace_char(char *str);
char **str_to_array(char *str, char c);
void free_array(char **array);

// server_response

int server_response(char *response);

// code
void code_101();
void code_102();
void code_103();
void code_104();

void code_301();
void code_302();
void code_303();
void code_304();

void code_313();
void code_315();
void code_319();

void code_311(char *response);
void code_312(char *response);
void code_314(char *response);
void code_316(char *response);
void code_317(char *response);

void code_321();
void code_322();
void code_323();
void code_324();

void code_331(char *response);
void code_332(char *response);
void code_333(char *response);
void code_334(char *response);

void code_341(char *response);
void code_342(char *response);
void code_343(char *response);
void code_344(char *response);

void code_500();
void code_501();
void code_502();
void code_503();
void code_504();
void code_511();
void code_512();
void code_513();
void code_521();
void code_522();
void code_523();
void code_524();

#endif /* !TEAMS_CLIENT_H_ */
