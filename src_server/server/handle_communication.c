/*
** EPITECH PROJECT, 2022
** handle_communication.c
** File description:
** handle_comunication
*/

#include "teams_serv.h"



int read_client(server_t *info, client_t *client)
{
    char *read_buffer = NULL;
    int read_value = -1;

    read_buffer = malloc(sizeof(char) * LENGTH_COMMAND);
    if (!read_buffer)
        return (-1);
    read_value = read(client->socket, read_buffer, LENGTH_COMMAND);
    if (read_value == -1) {
        free(read_buffer);
        return (-1);
    }
    if (read_value == 0) {
        remove_client(info, client->socket);
        free(read_buffer);
        return (-1);
    }
    read_buffer[read_value] = '\0';
    add_to_write(client->buff_read, read_buffer, LENGTH_COMMAND);
    free(read_buffer);
    return (0);
}

void write_client(server_t *info, int s_client)
{
    int w_value = 1;
    client_t *client = find_client(info, s_client);
    int len = strlen(client->data_send);
    int value_write = LENGTH_COMMAND;

    while (w_value < len && w_value > 0) {
        if (len < LENGTH_COMMAND)
            value_write = len;
        w_value += write(s_client, client->data_send, value_write);
        len -= value_write;
    }
    free(client->data_send);
    client->status = READ;
    if (w_value < 0)
        remove_client(info, s_client);
    if (client->isQuit)
        close(s_client);
}

void close_server(server_t *info)
{
    client_t *temp = info->list_client;
    client_t *next = NULL;

    FD_ZERO(&info->rfds);
    FD_ZERO(&info->wfds);
    while (temp) {
        next = temp->next;
        free(temp->buff_read);
        free(temp);
        temp = next;
    }
    free(info->data);
    close(info->fd_server);
    exit(0);
}