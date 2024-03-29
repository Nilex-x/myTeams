/*
** EPITECH PROJECT, 2022
** teams_client.c
** File description:
** teams_client
*/

#include "teams_client.h"
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

static info_t *init_info(int socket)
{
    info_t *info = malloc(sizeof(info_t));

    if (!info)
        return NULL;
    info->socket = socket;
    info->read_write = READ;
    info->write_buffer = NULL;
    init_buffer(&info->read_buffer, LENGTH_COMMAND);
    FD_SET(info->socket, &info->readfds);
    FD_SET(info->socket, &info->exceptfds);
    FD_ZERO(&info->writefds);
    info->quit = 0;
    return info;
}

int connect_client(char *ip, int port)
{
    int client_socket;
    int serv_lenght;
    struct sockaddr_in serv_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
        return -1;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) < 0)
        return -1;
    serv_lenght = sizeof(serv_addr);
    if (connect(client_socket, (struct sockaddr*)&serv_addr, serv_lenght) < 0)
        return -1;
    return client_socket;
}

void client_loop(info_t *info)
{
    int max = info->socket + 1;

    clear_list(info);
    if (select(max, &info->readfds, &info->writefds, &info->exceptfds, NULL))
        manage_client(info);
}

int main(int argc, char **argv)
{
    int client_socket;
    info_t *info = NULL;

    if (argc != 3)
        return 84;
    client_socket = connect_client(argv[1], atoi(argv[2]));
    if (client_socket < 0)
        return 84;
    info = init_info(client_socket);
    if (!info)
        return 84;
    while (!info->quit)
        client_loop(info);
    free(info);
    return (0);
}
