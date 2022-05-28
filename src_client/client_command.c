/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** client_command
*/

#include "teams_client.h"

void clear_list(info_t *info)
{
    FD_ZERO(&info->readfds);
    FD_ZERO(&info->writefds);
    FD_ZERO(&info->exceptfds);
    FD_SET(info->socket, &info->exceptfds);
    FD_SET(0, &info->readfds);
    if (info->read_write == READ)
        FD_SET(info->socket, &info->readfds);
    else
        FD_SET(info->socket, &info->writefds);
}

void get_server_command(info_t *info)
{
    int valread;
    char *buffer = malloc(LENGTH_COMMAND);
    char *response = NULL;

    if (!buffer)
        return;
    valread = read(info->socket, buffer, LENGTH_COMMAND);
    if (valread == -1 || valread == 0) {
        info->quit = 1;
        return;
    }
    buffer[valread] = '\0';
    add_to_write(&info->read_buffer, buffer, LENGTH_COMMAND);
    free(buffer);
    response = read_to_buffer(&info->read_buffer, '\n', LENGTH_COMMAND);
    // printf("[%s]\n", response);
    if (response && response[0] != '\n')
        server_response(response, info);
    else
        free(response);
}

void get_user_command(info_t *info)
{
    int valread;
    size_t buffsize = 0;

    info->write_buffer = malloc(1);
    valread = getline(&info->write_buffer, &buffsize, stdin);
    if (valread == -1 || valread == 0) {
        info->quit = 1;
        return;
    }
    info->read_write = WRITE;
    if (user_command(info) == -2) {
        free(info->write_buffer);
        info->write_buffer = NULL;
    }
}

void write_command(info_t *info)
{
    if (info->write_buffer) {
        write(info->socket, info->write_buffer, strlen(info->write_buffer));
        free(info->write_buffer);
    } else
        printf("missing double_quotes\n");
    info->read_write = READ;
}

void manage_client(info_t *info)
{
    if (FD_ISSET(info->socket, &info->exceptfds)) {
        info->quit = 1;
        return;
    }
    if (FD_ISSET(info->socket, &info->readfds)) {
        get_server_command(info);
        if (info->quit)
            return;
    }
    if (FD_ISSET(0, &info->readfds)) {
        get_user_command(info);
        if (info->quit)
            return;
    }
    if (FD_ISSET(info->socket, &info->writefds))
        write_command(info);
}
