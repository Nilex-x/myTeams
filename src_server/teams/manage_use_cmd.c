/*
** EPITECH PROJECT, 2022
** manage_use_cmd.c
** File description:
** manage_use_cmd
*/

#include "my_teams.h"

static void use_root(client_t *c, char **arg, data_server_t *data)
{
    return;
}

static void use_team(client_t *c, char **arg, data_server_t *data)
{
    return;
}

static void use_channel(client_t *c, char **arg, data_server_t *data)
{
    return;
}

static void use_thread(client_t *c, char **arg, data_server_t *data)
{
    return;
}

int cmd_use(client_t *c, char **arg, data_server_t *data)
{
    int len = len_array(arg);
    void (*context[4])(client_t *, char **, data_server_t *) = { use_root,
    use_team, use_channel, use_thread};

    if (!c->user)
        c->data_send = add_send(c->data_send , "502\n");
    if (len > 4)
        c->data_send = add_send(c->data_send, "501\n");
    if (!c->user || len > 4)
        return;
    context[len - 1](c, arg, data);
    return (0);
}