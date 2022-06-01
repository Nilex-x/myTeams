/*
** EPITECH PROJECT, 2022
** manage_use_cmd.c
** File description:
** manage_use_cmd
*/

#include "my_teams.h"

static void use_root(client_t *c, char **arg, data_server_t *data)
{
    users_t *user = c->user;

    (void) arg;
    (void) data;
    if (user->team)
        user->team = NULL;
    if (user->channel)
        user->channel = NULL;
    if (user->thread)
        user->thread = NULL;
    return;
}

static void use_team(client_t *c, char **arg, data_server_t *data)
{
    team_t *team = get_teams_by_id(arg[1], data);

    if (!team) {
        c->data_send = add_send(c->data_send, "522\n");
        return;
    }
    c->user->team = team;
    c->data_send = add_send(c->data_send, "319\n");
    return;
}

static void use_channel(client_t *c, char **arg, data_server_t *data)
{
    team_t *team = get_teams_by_id(arg[1], data);
    channel_t *channel = get_channel_by_uuid(arg[2], team);

    if (!team || !channel) {
        c->data_send = add_send(c->data_send, team ? "523\n" : "522\n");
        return;
    }
    c->user->team = team;
    c->user->channel = channel;
    c->data_send = add_send(c->data_send, "319\n");
    return;
}

static void use_thread(client_t *c, char **arg, data_server_t *data)
{
    team_t *team = get_teams_by_id(arg[1], data);
    channel_t *channel = get_channel_by_uuid(arg[2], team);
    thread_t *thread = get_thread_by_uuid(arg[3], channel);

    if (!team)
        c->data_send = add_send(c->data_send, "522\n");
    if (!channel)
        c->data_send = add_send(c->data_send, "523\n");
    if (!thread)
        c->data_send = add_send(c->data_send, "524\n");
    if (!team || !channel || !thread)
        return;
    c->user->team = team;
    c->user->channel = channel;
    c->user->thread = thread;
    c->data_send = add_send(c->data_send, "319\n");
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
        return (0);
    context[len - 1](c, arg, data);
    return (0);
}