/*
** EPITECH PROJECT, 2022
** manage_teams.c
** File description:
** manage_teams
*/

#include "my_teams.h"

team_t *get_teams_by_id(char *uuid, data_server_t *data)
{
    team_t *temp = data->teams;

    while (temp) {
        if (strcmp(temp->id, uuid) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

team_t *get_teams_by_name(char *name, data_server_t *data)
{
    team_t *temp = data->teams;

    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

team_t *create_add_teams(char *name, char *desc, data_server_t *data)
{
    team_t *new_team = malloc(sizeof(team_t));
    team_t *temp = data->teams;

    if (!new_team)
        return (NULL);
    new_team->name = strdup(name);
    new_team->description = strdup(desc);
    new_team->channels = NULL;
    new_team->subcribed = NULL;
    new_team->next = NULL;
    new_team->id = generate_uuid();
    if (!temp) {
        data->teams = new_team;
        return (new_team);
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new_team;
    return new_team;
}

void free_subscribed(subscribed_t *subs)
{
    subscribed_t *next = NULL;

    while (subs) {
        next = subs->next;
        free(subs);
        subs = next;
    }
}

void free_teams(team_t *teams)
{
    team_t *next = NULL;

    while (teams) {
        next = teams->next;
        free(teams->name);
        free(teams->description);
        free(teams->id);
        free_subscribed(teams->subcribed);
        free_channels(teams->channels);
        free(teams);
        teams = next;
    }
    return;
}
