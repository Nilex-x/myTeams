/*
** EPITECH PROJECT, 2022
** manage_create_cmd.c
** File description:
** manage_create_cmd
*/

#include "my_teams.h"

static int add_teams(client_t *c, char **args, data_server_t *data)
{
    team_t *new_team = get_teams_by_name(args[1], data);
    char *line = NULL;

    if (new_team) {
        c->data_send = add_send(c->data_send, "512 teams already exists\n");
        return (0);
    }
    new_team = create_add_teams(args[1], args[2], data);
    asprintf(&line, "CREATE\aTEAM\a%s\a%s\a%s", new_team->id,
                        new_team->name, new_team->description);
    append_to_list(&data->list->lines, line);
    asprintf(&line, "321\a%s\a%s\a%s\n", new_team->id, new_team->name,
                                new_team->description);
    c->data_send = add_send(c->data_send, line);
    free(line);
    server_event_team_created(new_team->id, new_team->name, c->user->info->id);
    send_notif_team(data, c->user, new_team);
    return (0);
}

static int add_channel(client_t *c, char **args, data_server_t *data)
{
    userinfo_t *info = get_subscribe_by_id(c->user->team, c->user->info->id);
    channel_t *channel = get_channel_by_name(args[1], c->user->team);
    char *line = NULL;

    if (channel || !info) {
        c->data_send = add_send(c->data_send, info ? "512\n" : "513\n");
        return (0);
    }
    channel = create_add_channel(args[1], args[2], c->user->team);
    asprintf(&line, "CREATE\aCHANNEL\a%s\a%s\a%s\a%s\n", c->user->team->id,
        channel->id, channel->name, channel->description);
    append_to_list(&data->list->lines, line);
    asprintf(&line, "322\a%s\a%s\a%s\n", channel->id, channel->name,
                                channel->description);
    c->data_send = add_send(c->data_send, line);
    free(line);
    server_event_channel_created(c->user->team->id, channel->id,
                                                channel->name);
    send_notif_channel(data, c->user, channel);
    return (0);
}

static int add_thread(client_t *c, char **arg, data_server_t *data)
{
    userinfo_t *info = get_subscribe_by_id(c->user->team, c->user->info->id);
    thread_t *trd = get_thread_by_title(arg[1], c->user->channel);
    char *line = NULL;

    if (trd || !info) {
        c->data_send = add_send(c->data_send, info ? "512\n" : "513\n");
        return (0);
    }
    trd = create_add_thread(arg[1], arg[2], c->user->channel, c->user->info);
    asprintf(&line, "CREATE\aTHREAD\a%s\a%s\a%s\a%s\a%ld\a%s\a%s\n", trd->id,
    c->user->channel->id, trd->id, trd->creator_id, trd->timestamp,
    trd->title, trd->body);
    append_to_list(&data->list->lines, line);
    asprintf(&line, "323\a%s\a%s\a%ld\a%s\a%s\n", trd->id,
        c->user->info->id, trd->timestamp, trd->title, trd->body);
    c->data_send = add_send(c->data_send, line);
    free(line);
    send_notif_thread(data, c->user, trd);
    return (0);
}

static int send_comment(client_t *c, char **args, data_server_t *data)
{
    reply_t *reply = NULL;
    char *line = NULL;

    if (get_subscribe_by_id(c->user->team, c->user->info->id)) {
        c->data_send = add_send(c->data_send, "513\n");
        return (0);
    }
    reply = create_add_reply(args[1], c->user->info, c->user->thread);
    asprintf(&line, "324\a%s\a%s\a%ld\a%s\n", c->user->thread->id,
    c->user->info->id, reply->timestamp, reply->body);
    c->data_send = add_send(c->data_send, line);
    free(line);
    server_event_reply_created(c->user->thread->id, c->user->info->id,
    reply->body);
    send_notif_reply(data, c->user, reply);
    return (0);
}

int sort_create(client_t *c, char **args, data_server_t *data)
{
    int len = len_array(args);

    if (!c->user)
        c->data_send = add_send(c->data_send, "503 Not logged-in\n");
    if (c->user && !c->user->team && len == 3)
        return (add_teams(c, args, data));
    if (c->user && !c->user->channel && len == 3)
        return (add_channel(c, args, data));
    if (c->user && !c->user->thread && len == 3)
        return (add_thread(c, args, data));
    if (c->user && c->user->thread && len == 2)
        return (send_comment(c, args, data));
    c->data_send = add_send(c->data_send, "502 Command missing arguments.\n");
    return (0);
}
