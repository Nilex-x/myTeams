/*
** EPITECH PROJECT, 2022
** handle_communication.c
** File description:
** handle_comunication
*/

#include "teams_serv.h"

char *read_client(server_t *info, int client_socket)
{
    char *read_buffer = NULL;
    int read_value = -1;

    read_buffer = malloc(sizeof(char) * 1024);
    if (!read_buffer)
        return (NULL);
    read_value = read(client_socket, read_buffer, 1024);
    if (read_value == -1) {
        perror("read client");
        free(read_buffer);
        return (NULL);
    } else if (read_value == 0) {
        remove_client(info, client_socket);
        clear_list(info);
        free(read_buffer);
        return (NULL);
    } else {
        read_buffer[read_value] = '\0';
        return (read_buffer);
    }
}