/*
** EPITECH PROJECT, 2022
** manager_server.c
** File description:
** manage_server
*/

#include "teams_serv.h"

// void clear_list(ftp_t *info)
// {
//     client_t *temp = info->list_client->head;

//     FD_ZERO(&info->wfds);
//     FD_ZERO(&info->rfds);
//     while (temp) {
//         if (temp->status == READ)
//             FD_SET(temp->socket, &info->rfds);
//         if (temp->status == WRITE)
//             FD_SET(temp->socket, &info->wfds);
//         temp = temp->next;
//     }
// }

int create_socket(server_t *info)
{
    struct sockaddr_in my_addr;
    size_t len = sizeof(struct sockaddr_in);

    info->fd_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (info->fd_server == -1)
        return -1;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons((uint16_t) info->port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(info->fd_server, (struct sockaddr *) &my_addr, len) == -1)
        return -1;
    if (listen(info->fd_server, NB_LISTEN) == -1)
        return -1;
    info->max_fd = info->fd_server;
    FD_ZERO(&info->rfds);
    FD_ZERO(&info->wfds);
    FD_SET(info->fd_server, &info->rfds);
    return (0);
}

int handler_connection(server_t *info)
{
    while (1) {
        clear_list(info);
        if (select(info->max_fd + 1, &info->rfds, &info->wfds, NULL, NULL) < 0)
            perror("Select()");
        else
            find_socket(info);
    }
}