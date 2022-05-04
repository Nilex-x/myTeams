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
    list_client->buff = malloc(sizeof(buffer_t));
    if (!list_client->buff)
        return;
    for (int i = 0; i < LENGTH_COMMAND; i++)
        list_client->buff->buffer[i] = '\0';
    list_client->buff->rdonly = list_client->buff->buffer;
    list_client->buff->wronly = list_client->buff->buffer;
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
            free(temp);
            return;
        }
        temp = temp->next;
    }
}
