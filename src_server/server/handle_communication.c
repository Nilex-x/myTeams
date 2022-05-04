/*
** EPITECH PROJECT, 2022
** handle_communication.c
** File description:
** handle_comunication
*/

#include "teams_serv.h"

void read_client(server_t *info, client_t *client)
{
    char *read_buffer = NULL;
    int read_value = -1;

    read_buffer = malloc(sizeof(char) * LENGTH_COMMAND);
    if (!read_buffer)
        return;
    read_value = read(client->socket, read_buffer, LENGTH_COMMAND);
    if (read_value == -1) {
        free(read_buffer);
        return;
    }
    if (read_value == 0) {
        remove_client(info, client->socket);
        clear_list(info);
        free(read_buffer);
        return;
    }
    read_buffer[read_value] = '\0';
    add_to_write(client->buff, read_buffer);
    free(read_buffer);
}

char *read_to_buffer(buffer_t *buff)
{
    int len = count_until_char(buff->rdonly, '\n');
    char *value = NULL;

    if (len == -1)
        return NULL;
    value = malloc(sizeof(char) * (len + 1));
    if (!value)
        return (NULL);
    for (int i = 0; buff->rdonly[0] != '\n'; buff->rdonly++, i++) {
        if ((buff->rdonly - buff->buffer) == LENGTH_COMMAND)
            buff->rdonly = buff->buffer;
        value[i] = buff->rdonly[0];
    }
    return (value);
}

void add_to_write(buffer_t *buff, char *value)
{
    int len = strlen(value);
    printf("len: %d\n", len);

    for (int i = 0; value[i]; i++, buff->wronly++) {
        if ((buff->wronly - buff->buffer) == LENGTH_COMMAND)
            buff->wronly = buff->buffer;
        buff->wronly[0] = value[i];
    }
}

void write_client(server_t *info, int s_client)
{
    // int w_value = 1;
    // client_t *client = find_client(info, s_client);
    // char *value = read_to_buffer(client);
    // int len = strlen(client->data_send);
    // int value_send = 1024;

    // while (w_value < len && w_value > 0) {
    //     if (len < 1024)
    //         value_send = len;
    //     w_value += write(s_client, client->data_send, value_send);
    //     len -= w_value;
    // }
    // if (w_value == 0) {
    //     remove_client(info, s_client);
    // }
    // if (w_value != -1){
    //     client->status = READ;
    //     free(client->data_send);
    // }
}