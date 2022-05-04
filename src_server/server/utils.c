/*
** EPITECH PROJECT, 2022
** utils.c
** File description:
** utils
*/

#include "teams_serv.h"

void accept_connect(server_t *info)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(struct sockaddr_in);
    client_t *new_client = NULL;
    int incomming_fd = accept(info->fd_server, (struct sockaddr *) &client, \
                                &len);

    // FD_SET(incomming_fd, &info->wfds);
    new_client = add_client(info, incomming_fd);
    // new_client->data_send = strdup("220\r\n");
    // new_client->status = WRITE;
    if (incomming_fd > info->max_fd)
        info->max_fd = incomming_fd;
}