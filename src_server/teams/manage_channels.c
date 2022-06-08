/*
** EPITECH PROJECT, 2022
** manage_channels.c
** File description:
** manage_channels
*/

#include "my_teams.h"

channel_t *get_channel_by_uuid(char *uuid, team_t *team)
{
    channel_t *channel = team->channels;

    while (channel) {
        if (strcmp(channel->id, uuid) == 0)
            return (channel);
        channel = channel->next;
    }
    return NULL;
}

channel_t *get_channel_by_name(char *name, team_t *team)
{
    channel_t *channel = team->channels;

    while (channel) {
        if (strcmp(channel->name, name) == 0)
            return (channel);
        channel = channel->next;
    }
    return NULL;
}

channel_t *create_add_channel(char *name, char *desc, team_t *team)
{
    channel_t *new_channel = malloc(sizeof(channel_t));
    channel_t *temp = team->channels;

    if (!new_channel)
        return (NULL);
    new_channel->id = generate_uuid();
    new_channel->name = strdup(name);
    new_channel->description = strdup(desc);
    new_channel->threads = NULL;
    new_channel->next = NULL;
    if (!temp) {
        team->channels = new_channel;
        return (new_channel);
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new_channel;
    return new_channel;
}

void free_channels(channel_t *channel)
{
    channel_t *next = NULL;

    while (channel) {
        next = channel->next;
        free(channel->name);
        free(channel->description);
        free(channel->id);
        free_thread(channel->threads);
        free(channel);
        channel = next;
    }
    return;
}
