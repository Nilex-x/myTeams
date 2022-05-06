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
    node->buff_write = malloc(sizeof(buffer_t));
    if (!node->buff_read || !node->buff_write)
        return;
    init_buffer(node->buff_read, LENGTH_COMMAND);
    init_buffer(node->buff_write, LENGTH_COMMAND);
}