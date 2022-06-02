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
    c->data_send = add_send(c->data_send, "319\n");
    return;
}

static void use_team(client_t *c, char **arg, data_server_t *data)
{
    team_t *team = get_teams_by_id(arg[1], data);
    char *line = NULL;

    c->user->channel = NULL;
    c->user->thread = NULL;
    if (!team) {
        asprintf(&line, "522\a%s\n", arg[1]);
    } else {
        c->user->team = team;
        asprintf(&line, "319\n");
    }
    c->data_send = add_send(c->data_send, line);
    free(line);
    return;
}

static void use_channel(client_t *c, char **arg, data_server_t *data)
{
    team_t *team = get_teams_by_id(arg[1], data);
    channel_t *channel = get_channel_by_uuid(arg[2], team);
    char *line = NULL;

    c->user->thread = NULL;
    if (!team)
        asprintf(&line, "522\a%s\n", arg[1]);
    if (!channel)
        asprintf(&line, "523\a%s\n", arg[2]);
    if (team && channel) {
        c->user->team = team;
        c->user->channel = channel;
        asprintf(&line, "319\n");
    }
    c->data_send = add_send(c->data_send, line);
    free(line);
    return;
}

static void use_thread(client_t *c, char **arg, data_server_t *data)
{
    team_t *team = get_teams_by_id(arg[1], data);
    channel_t *channel = get_channel_by_uuid(arg[2], team);
    thread_t *thread = get_thread_by_uuid(arg[3], channel);
    char *line = NULL;

    if (!team)
        asprintf(&line, "522\a%s\n", arg[1]);
    if (!channel)
        asprintf(&line, "523\a%s\n", arg[2]);
    if (!thread)
        asprintf(&line, "524\a%s\n", arg[3]);
    if (team && channel && thread) {
        c->user->team = team;
        c->user->channel = channel;
        c->user->thread = thread;
        asprintf(&line, "319\n");
    }
    c->data_send = add_send(c->data_send, line);
    free(line);
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
