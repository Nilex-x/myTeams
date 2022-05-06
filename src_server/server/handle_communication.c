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
    int w_value = 0;
    client_t *client = find_client(info, s_client);
    char *value = read_to_buffer(client->buff_write, '\n', LENGTH_COMMAND);
    printf("value to write: [%s]\n", value);

    if (!value) {
        client->status = READ;
        return;
    }
    w_value += write(s_client, value, strlen(value));
    if (w_value == 0)
        remove_client(info, s_client);
    if (w_value != -1)
        client->status = READ;
    free(value);
}

void free_data(struct data_server_s *data)
{
    free(data);
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
        free(temp->buff_write);
        free(temp);
        temp = next;
    }
    free_data(info->data);
    close(info->fd_server);
    exit(0);
}