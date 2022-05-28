/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** manage_info_cmd
*/

#include "my_teams.h"

int info_user(struct client_s *c, data_server_t *data)
{
    char *line = NULL;
    char *uuid = c->user->info->id;
    char *name = c->user->info->name;
    int status = 1;

    (void) data;
    asprintf(&line, "341\a%s\a%s\a%d\n", uuid, name, status);
    c->data_send = add_send(c->data_send, line);
    free(line);
    return 0;
}

int info_team(struct client_s *c, data_server_t *data)
{
    char *line = NULL;
    char *name = c->user->team->name;
    char *uuid = c->user->team->id;
    char *description = c->user->team->description;

    (void) data;
    asprintf(&line, "342\a%s\a%s\a%s\n", name, uuid, description);
    c->data_send = add_send(c->data_send, line);
    free(line);
    return 0;
}

int info_channel(struct client_s *c, data_server_t *data)
{
    char *line = NULL;
    char *name = c->user->channel->name;
    char *uuid = c->user->channel->id;
    char *description = c->user->channel->description;

    (void) data;
    asprintf(&line, "343\a%s\a%s\a%s\n", name, uuid, description);
    c->data_send = add_send(c->data_send, line);
    free(line);
    return 0;
}

int info_thread(struct client_s *c, data_server_t *data)
{
    char *line = NULL;
    char *uuid = c->user->thread->id;
    char *auth = c->user->thread->creator_id;
    char *title = c->user->thread->title;
    char *body = c->user->thread->body;
    time_t ts = c->user->thread->timestamp;

    (void) data;
    asprintf(&line, "344\a%s\a%s\a%d\a%s\a%s\n", auth, uuid, ts, title, body);
    c->data_send = add_send(c->data_send, line);
    free(line);
    return 0;
}
