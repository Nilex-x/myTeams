/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** manage_list_cmd
*/

#include "my_teams.h"

static int list_teams(struct client_s *c, data_server_t *data)
{
    char *line = NULL;

    for (team_t *curr = data->teams; curr; curr = curr->next) {
        asprintf(&line, "331\a%s\a%s\a%s\n", curr->id, curr->name
        , curr->description);
        c->data_send = add_send(c->data_send, line);
        free(line);
    }
    return 0;
}

static int list_channels(struct client_s *c, data_server_t *data)
{
    char *line = NULL;

    for (channel_t *curr = c->user->team->channels; curr; curr = curr->next) {
        asprintf(&line, "332\a%s\a%s\a%s\n", curr->id, curr->name
        , curr->description);
        c->data_send = add_send(c->data_send, line);
        free(line);
    }
    return 0;
}

static int list_threads(struct client_s *c, data_server_t *data)
{
    char *line = NULL;

    for (thread_t *curr = c->user->channel->threads; curr; curr = curr->next) {
        asprintf(&line, "333\a%s\a%s\a%ld\a%s\a%s\n", curr->id
        , curr->creator_id, curr->timestamp, curr->title, curr->body);
        c->data_send = add_send(c->data_send, line);
        free(line);
    }
    return 0;
}

static int list_comments(struct client_s *c, data_server_t *data)
{
    char *line = NULL;

    // for (char *curr = c->user->channel->threads->comment; curr; curr = curr->next) {
    //     asprintf(&line, "333\a%s\a%s\a%ld\a%s\a%s\n", c->user->info->id
    //     , c->user->info->id, 1111111111, c->user->info->id, c->user->info->id);
    //     c->data_send = add_send(c->data_send, line);
    //     free(line);
    // }
    return 0;
}

int list(struct client_s *c, char **arg, data_server_t *data)
{
    int context = (c->user->team != NULL) + (c->user->channel != NULL) +
    (c->user->thread != NULL);
    int (*f[4])(struct client_s *, data_server_t *) = {
        &list_teams, &list_channels, &list_threads, &list_comments
    };

    (void) arg;
    if (!c->user) {
        c->data_send = add_send(c->data_send, "502 - Not logged-in.\n");
        c->status = WRITE;
        return (0);
    }
    return f[context](c, data);
}
