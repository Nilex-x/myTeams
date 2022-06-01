/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** teams_client
*/

#ifndef TEAMS_CLIENT_H_
    #define TEAMS_CLIENT_H_
    #define _GNU_SOURCE

    #include <sys/select.h>

    #include "lib.h"
    #include "logging_client.h"

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
    fd_set exceptfds;
    int quit;
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

int remove_dquotes(char *str);
void replace_char(char *str);
char **str_to_array(char *str, char c);
void free_array(char **array);

// server_response

void server_response(char *response, info_t *info);

// code
void code_101(char *response);
void code_102(char *response);
void code_103(char *response);

void code_104(char *response);

void code_301(char *response);
void code_302(char *response);
void code_303(char *response);

void code_313(char *response);
void code_315(char *response);
void code_318(char *response);
void code_319(char *response);

void code_311(char *response);
void code_312(char *response);
void code_314(char *response);
void code_316(char *response);
void code_317(char *response);

void code_321(char *response);
void code_322(char *response);
void code_323(char *response);
void code_324(char *response);

void code_331(char *response);
void code_332(char *response);
void code_333(char *response);
void code_334(char *response);

void code_341(char *response);
void code_342(char *response);
void code_343(char *response);
void code_344(char *response);

void code_201(char *response);
void code_202(char *response);
void code_211(char *response);
void code_212(char *response);
void code_221(char *response);
void code_222(char *response);
void code_223(char *response);

void code_500(char *response);
void code_501(char *response);
void code_502(char *response);
void code_503(char *response);
void code_511(char *response);
void code_512(char *response);
void code_513(char *response);
void code_521(char *response);
void code_522(char *response);
void code_523(char *response);
void code_524(char *response);

#endif /* !TEAMS_CLIENT_H_ */
