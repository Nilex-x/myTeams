/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** my_teams
*/

#ifndef TEAMS_SERV
    #define TEAMS_SERV
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/socket.h>
    #include <netinet/ip.h>
    #include <stdbool.h>
    #include "lib.h"

    #define NB_LISTEN 32
    #define WRITE 0
    #define READ 1
    #define LENGTH_COMMAND 512

typedef struct buffer_s {
    char buffer[LENGTH_COMMAND];
    char *wronly;
    char *rdonly;
} buffer_t;

typedef struct client_s {
    int socket;
    int status;
    buffer_t *buff;
    struct client_s *next;
    struct client_s *prev;
} client_t;

typedef struct server_s
{
    int port;
    int fd_server;
    int max_fd;
    fd_set wfds;
    fd_set rfds;
    client_t *list_client;
}server_t;

int create_socket(server_t *info);
void read_client(server_t *info, client_t *client);
char *get_client_command(server_t *info, client_t *client);
void remove_client(server_t *info, int client);
int handler_connection(server_t *info);
void init_client(server_t *info);
void clear_list(server_t *info);
client_t *add_client(server_t *info, int client);
client_t *find_client(server_t *info, int client);
void free_client(client_t *client);
void accept_connect(server_t *info);
void add_to_write(buffer_t *buff, char *value);
char *read_to_buffer(buffer_t *buff);

#endif /* !TEAMS_SERV */
