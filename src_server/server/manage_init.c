/*
** EPITECH PROJECT, 2022
** manage_init.c
** File description:
** manage_init
*/

#include "teams_serv.h"

void init_buff_client(client_t *node)
{
    node->buff_read = malloc(sizeof(buffer_t));
    if (!node->buff_read)
        return;
    init_buffer(node->buff_read, LENGTH_COMMAND);
}

void handle_command(server_t *info, client_t *client)
{
    char *value = NULL;
    value = read_to_buffer(client->buff_read, '\n', LENGTH_COMMAND);
    if (!value || value[0] == '\n') {
        free(value);
        return;
    }
    if (client->socket == 0 && strcmp(value, "quit\n") == 0) {
        free(value);
        close_server(info);
    }
    if (strcmp(value, "QUIT\n") == 0) {
        free(value);
        client->isQuit = true;
        client->data_send = strdup("304 Goodbye see you soon\n");
        client->status = WRITE;
        return;
    }
    printf("value client [%s]\n", value);
    sort_command(client, info->data, value);
    free(value);
}