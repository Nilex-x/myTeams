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

    #define NB_LISTEN 32

typedef struct server_s
{
    int port;
    int fd_server;
    int max_fd;
    fd_set wfds;
    fd_set rfds;
}server_t;

int create_socket(server_t *info);


#endif /* !MY_TEAMS_H_ */
