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
    channel_t *channel = get_channel_by_name(args[1], c->user->team);
    char *line = NULL;

    if (channel) {
        c->data_send = add_send(c->data_send, "512 teams already exists\n");
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
    send_notif_channel(data, c->user, c->user->team, channel);
    return (0);
}

static int add_thread(client_t *c, char **args, data_server_t *data)
{
    thread_t *thread = get_thread_by_title(args[1], c->user->channel);
    char *line = NULL;

    if (thread) {
        c->data_send = add_send(c->data_send, "512 teams already exists\n");
        return (0);
    }
    thread = create_add_thread(args[1], args[2], c->user->channel,
                                                    c->user->info);
    asprintf(&line, "CREATE\aTHREAD\a%s\a%s\a%s\a%s\a%ld\a%s\a%s\n",
        thread->id, c->user->channel->id, thread->id,
        thread->creator_id, thread->timestamp, thread->title, thread->body);
    append_to_list(&data->list->lines, line);
    asprintf(&line, "323\a%s\a%s\a%ld\a%s\a%s\n", thread->id,
        c->user->info->id, thread->timestamp, thread->title, thread->body);
    c->data_send = add_send(c->data_send, line);
    free(line);
    server_event_thread_created(c->user->channel->id, thread->id,
        c->user->info->id, thread->title, thread->body);
    return (0);
}

static int send_comment(client_t *client, char **args, data_server_t *data)
{
    (void) client;
    (void) args;
    (void) data;


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
