/*
** EPITECH PROJECT, 2022
** manage_subscribe.c
** File description:
** manage_subcribe
*/

#include "my_teams.h"

static int subscribe_user(team_t *team, users_t *toadd)
{
    subscribed_t *new = NULL;
    subscribed_t *temp = team->subcribed;

    new = malloc(sizeof(subscribed_t));
    if (!new)
        return (0);
    new->user = toadd->info;
    new->next = NULL;
    server_event_user_subscribed(team->id, toadd->info->id);
    if (!temp) {
        team->subcribed = new;
        return (0);
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new;
    return (0);
}

static int add_to_list(team_t *team, userinfo_t *info, data_server_t *data)
{
    char *line = NULL;

    asprintf(&line, "SUBSCRIBED\a%s\a%s", team->id, info->id);
    append_to_list(&data->list->lines, line);
    free(line);
    return (0);
}

int subscribe(client_t *c, char **args, data_server_t *data)
{
    team_t *team = NULL;
    char *response = NULL;

    if (len_array(args) != 2) {
        c->data_send = add_send(c->data_send, "502 missing argument.\n");
        return (0);
    }
    team = get_teams_by_id(args[1], data);
    if (!team)
        asprintf(&response, "522\a%s\n", args[1]);
    if (team && get_subscribe_by_id(team, c->user->info->id))
        asprintf(&response, "103\a%s\a%s\n", team->id ,c->user->info->id);
    if (team && !get_subscribe_by_id(team, c->user->info->id)) {
        subscribe_user(team, c->user);
        asprintf(&response, "315\a%s\a%s\n", c->user->info->id, team->id);
        add_to_list(team, c->user->info, data);
    }
    c->data_send = add_send(c->data_send, response);
    free(response);
    return (0);
}
