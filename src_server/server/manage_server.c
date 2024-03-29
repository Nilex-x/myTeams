/*
** EPITECH PROJECT, 2022
** manager_server.c
** File description:
** manage_server
*/

#include "teams_serv.h"
#include <sys/socket.h>
#include <netinet/ip.h>
#include <sys/select.h>

static void clear_list(server_t *info)
{
    client_t *temp = info->list_client;

    FD_ZERO(&info->wfds);
    FD_ZERO(&info->rfds);
    FD_ZERO(&info->efds);
    while (temp) {
        FD_SET(temp->socket, &info->efds);
        if (!temp->data_send)
            FD_SET(temp->socket, &info->rfds);
        if (temp->data_send)
            FD_SET(temp->socket, &info->wfds);
        temp = temp->next;
    }
}

static void sort_client(client_t *client, server_t *info)
{
    if (client->socket == info->fd_server) {
        accept_connect(info);
        return;
    }
    if (read_client(info, client) != -1)
        handle_command(info, client);
}

static void find_socket(server_t *info)
{
    client_t *temp = info->list_client;
    client_t *next = NULL;
    bool broken = false;

    while (temp) {
        broken = false;
        next = temp->next;
        if (FD_ISSET(temp->socket, &info->efds)) {
            remove_client(info, temp->socket);
            broken = true;
        }
        if (!broken && FD_ISSET(temp->socket, &info->rfds))
            sort_client(temp, info);
        else if (!broken && FD_ISSET(temp->socket, &info->wfds))
            write_client(info, temp->socket);
        temp = next;
    }
    return;
}

int handler_connection(server_t *info)
{
    FD_ZERO(&info->rfds);
    FD_ZERO(&info->wfds);
    FD_ZERO(&info->efds);
    FD_SET(info->fd_server, &info->rfds);
    info->data = get_server_data(FILEPATH_SAVE);
    init_client(info);
    while (1) {
        clear_list(info);
        if (select(info->max_fd + 1, &info->rfds, &info->wfds,
                                    &info->efds, NULL) < 0) {
            perror("Select()");
        } else {
            find_socket(info);
        }
    }
}

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
    if (bind(info->fd_server, (struct sockaddr *) &my_addr, len) == -1) {
        perror("Bind()");
        return -1;
    }
    if (listen(info->fd_server, NB_LISTEN) == -1)
        return -1;
    info->max_fd = info->fd_server;
    return (0);
}
