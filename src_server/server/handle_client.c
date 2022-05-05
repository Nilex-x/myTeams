/*
** EPITECH PROJECT, 2022
** handle_client.c
** File description:
** handler_client
*/

#include "teams_serv.h"

void init_client(server_t *info)
{
    client_t *list_client = malloc(sizeof(client_t));
    if (!list_client)
        return;
    list_client->next = NULL;
    list_client->prev = NULL;
    list_client->status = READ;
    list_client->socket = info->fd_server;
    list_client->buff_read = malloc(sizeof(buffer_t));
    list_client->buff_write = malloc(sizeof(buffer_t));
    if (!list_client->buff_read || !list_client->buff_write)
        return;
    init_buffer(list_client->buff_read, LENGTH_COMMAND);
    init_buffer(list_client->buff_write, LENGTH_COMMAND);
    info->list_client = list_client;
}

client_t *add_client(server_t *info, int client)
{
    client_t *temp = info->list_client;
    client_t *node = NULL;

    node = malloc(sizeof(client_t));
    if (!node)
        return NULL;
    while (temp->next)
        temp = temp->next;
    temp->next = node;
    node->socket = client;
    node->prev = temp;
    node->next = NULL;
    node->status = READ;
    node->buff_read = malloc(sizeof(buffer_t));
    node->buff_write = malloc(sizeof(buffer_t));
    if (!node->buff_read || !node->buff_write)
        return (NULL);
    init_buffer(node->buff_read, LENGTH_COMMAND);
    init_buffer(node->buff_write, LENGTH_COMMAND);
    return (node);
}

client_t *find_client(server_t *info, int client)
{
    client_t *temp = info->list_client;

    while (temp) {
        if (temp->socket == client)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

void remove_client(server_t *info, int client)
{
    client_t *temp = info->list_client;

    while (temp) {
        if (temp->socket == client) {
            temp->prev->next = temp->next;
            free(temp->buff_read);
            free(temp->buff_write);
            free(temp);
            return;
        }
        temp = temp->next;
    }
}

void accept_connect(server_t *info)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(struct sockaddr_in);
    client_t *new_client = NULL;
    int incomming_fd = accept(info->fd_server, (struct sockaddr *) &client, \
                                &len);

    FD_SET(incomming_fd, &info->wfds);
    new_client = add_client(info, incomming_fd);
    add_to_write(new_client->buff_write, "220\n", LENGTH_COMMAND);
    new_client->status = WRITE;
    if (incomming_fd > info->max_fd)
        info->max_fd = incomming_fd;
}
