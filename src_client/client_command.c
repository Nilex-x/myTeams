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
    if (valread == -1)
        info->quit = 1;
    if (valread == 0 || valread == -1)
        return;
    buffer[valread] = '\0';
    add_to_write(&info->read_buffer, buffer, LENGTH_COMMAND);
    free(buffer);
    response = read_to_buffer(&info->read_buffer, '\n', LENGTH_COMMAND);
    if (response && response[0] != '\n')
        server_response(response, info);
    else
        free(response);
}

void get_user_command(info_t *info)
{
    int valread;

    info->write_buffer = malloc(LENGTH_COMMAND);
    valread = read(0, info->write_buffer, LENGTH_COMMAND);
    if (valread == -1 || valread == 0)
        return;
    info->write_buffer[valread] = '\0';
    info->read_write = WRITE;
    user_command(info);
}

void write_command(info_t *info)
{
    write(info->socket, info->write_buffer, strlen(info->write_buffer));
    free(info->write_buffer);
    info->read_write = READ;
}

void manage_client(info_t *info)
{
    if (FD_ISSET(info->socket, &info->readfds))
        get_server_command(info);
    if (FD_ISSET(0, &info->readfds))
        get_user_command(info);
    if (FD_ISSET(info->socket, &info->writefds))
        write_command(info);
}