/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** my_teams
*/

#ifndef TEAMS_SERV_H_
    #define TEAMS_SERV_H_
    #include "lib.h"
    #include "my_teams.h"
    #include "logging_server.h"
    #include <stdbool.h>
    #include <sys/select.h>
    #include <stddef.h>

    #define NB_LISTEN 32
    #define WRITE 0
    #define READ 1
    #define LENGTH_COMMAND 512

typedef struct data_send_s {
    char *data;
    struct data_send_s *next;
} data_send_t;

typedef struct client_s {
    int socket;
    int status;
    bool isQuit;
    data_send_t *data_send;
    buffer_t *buff_read;
    struct users_s *user;
    struct client_s *next;
    struct client_s *prev;
} client_t;

typedef struct server_s
{
    int port;
    int fd_server;
    int max_fd;
    fd_set wfds;
    fd_set efds;
    fd_set rfds;
    client_t *list_client;
    struct data_server_s *data;
}server_t;

int create_socket(server_t *info);
int read_client(server_t *info, client_t *client);
char *get_client_command(server_t *info, client_t *client);
void remove_client(server_t *info, int client);
int handler_connection(server_t *info);
void init_client(server_t *info);
// void clear_list(server_t *info);
client_t *add_client(server_t *info, int client);
client_t *find_client(server_t *info, int client);
void free_client(client_t *client);
void accept_connect(server_t *info);
void write_client(server_t *info, int s_client);
void close_server(server_t *info);
void init_buff_client(client_t *node);
void handle_command(server_t *info, client_t *client);

data_send_t *add_send(data_send_t *data_send, char *data);
char *get_next_data_to_send(data_send_t **data_send);
size_t get_size_data_to_send(data_send_t *data_send);
void free_data_send(data_send_t *send);

#endif /* !TEAMS_SERV_H_ */
