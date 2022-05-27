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
    new->user = toadd->info;
    new->next = NULL;
    server_event_user_subscribed(team->id, toadd->info->id);
    if (!temp) {
        printf("first subs\n");
        team->subcribed = new;
        return (0);
    }
    while (temp->next) {
        printf("loop subs\n");
        temp = temp->next;
    }
    temp->next = new;
    return (0);
}

static int unsubscribe_user(team_t *team, users_t *torm)
{
    subscribed_t *temp = team->subcribed;
    subscribed_t *prev = NULL;

    server_event_user_subscribed(team->id, torm->info->id);
    if (temp->user == torm->info) {
        printf("first unsubs\n");
        team->subcribed = team->subcribed->next;
        free(temp);
        return (0);
    }
    while (temp->next) {
        printf("loop unsubs\n");
        if (temp->user == torm->info) {
            prev->next = temp->next;
            free(temp);
            break;
        }
        prev = temp;
        temp = temp->next;
    }
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
    team = get_teams_by_id(get_quotes_content(args[1]), data);
    if (!team) {
        asprintf(&response, "522\a%s\n", args[1]);
        c->data_send = add_send(c->data_send, "522\n");
        free(response);
        return (0);
    }
    subscribe_user(team, c->user);
    asprintf(&response, "315\a%s\a%s\n", c->user->info->id, team->id);
    c->data_send = add_send(c->data_send, response);
    free(response);
    return (0);
}

userinfo_t *get_subscribe_by_id(team_t *team, char *uuid)
{
    subscribed_t *temp = team->subcribed;

    while (temp) {
        if (strcmp(temp->user->id, uuid) == 0)
            return temp->user;
        temp = temp->next;
    }
    return NULL;
}

int unsubscribe(client_t *c, char **args, data_server_t *data)
{
    team_t *team = NULL;
    char *response = NULL;

    if (len_array(args) != 2) {
        c->data_send = add_send(c->data_send, "502 missing argument.\n");
        return (0);
    }
    team = get_teams_by_id(get_quotes_content(args[1]), data);
    if (!team)
        asprintf(&response, "522\a%s\n", args[1]);
    if (team && !get_subscribe_by_id(team, c->user->info->id))
        asprintf(&response, "513\a%s\n", team->id);
    if (team && get_subscribe_by_id(team, c->user->info->id)) {
        unsubscribe_user(team, c->user);
        asprintf(&response, "318\a%s\a%s\n", c->user->info->id, team->id);
    }
    c->data_send = add_send(c->data_send, response);
    free(response);
    return (0);
}
