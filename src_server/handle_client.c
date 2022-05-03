/*
** EPITECH PROJECT, 2022
** handle_client.c
** File description:
** handler_client
*/

#include "teams_serv.h"

void init_client(server_t *info, char *ip)
{
    client_t *list_client = malloc(sizeof(client_t));
    if (!list_client)
        return;
    list_client->data_send = NULL;
    list_client->isConnected = false;
    list_client->next = NULL;
    list_client->prev = NULL;
    list_client->status = READ;
    list_client->user = NULL;
    list_client->socket = info->fd_server;
    info->list_client = list_client;
}

void get_client_command(server_t *info, int client_socket)
{
    char **tab = NULL;
    char *value = read_client(info, client_socket);

    if (client_socket == 0 && value) {
        sort_command(info, client_socket, value);
        return;
    }
    tab = malloc(sizeof(char *) * 5);
    if (!value || !tab)
        return;
    for (int i = 0; value; i++) {
        tab[i] = strdup(value);
        tab[i + 1] = NULL;
        if (find_char_in_str('\r', tab[i]) && find_char_in_str('\n', tab[i]))
            break;
        free(value);
        value = read_client(info, client_socket);
    }
    free(value);
    return (arr)
    sort_command(info, client_socket, array_to_str(tab));
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
    node->user = NULL;
    node->status = READ;
    temp->isConnected = false;
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
            free_client(temp);
            return;
        }
        temp = temp->next;
    }
}
