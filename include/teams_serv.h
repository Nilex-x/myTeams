/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** my_teams
*/

#ifndef MY_TEAMS_H_
    #define MY_TEAMS_H_
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/socket.h>
    #include <netinet/ip.h>
    #include <stdbool.h>

    #define NB_LISTEN 32
    #define WRITE 0
    #define READ 1

typedef struct client_s {
    int socket;
    int status;
    bool isConnected;
    char *user;
    char *data_send;
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
char *read_client(server_t *info, int client_socket);
void get_client_command(server_t *info, int client_socket);


#endif /* !MY_TEAMS_H_ */
