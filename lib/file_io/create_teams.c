/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** create_teams
*/

#include "file_io.h"

char **get_comments(file_io_t *file_io, char *thread_id)
{
    int size = 1;
    char **comms = malloc(sizeof(char *));
    int len = strlen(thread_id) + 16;
    char *p = malloc(len);

    sprintf(p, "CREATE COMMENT %s", thread_id);
    for (line_t *curr = file_io->lines; curr; curr = curr->next)
        if (curr->type == CREATE && !strncmp(curr->line, p, len)) {
            comms = realloc(comms, (size + 1) * sizeof(char *));
            comms[size - 1] = strdup(curr->line + len + 1);
            size++;
        }
    comms[size - 1] = 0;
    free(p);
    return comms;
}

thread_t *get_threads(file_io_t *file_io, char *team_id, char *chan_id)
{
    thread_t *threads = NULL;
    thread_t *last = NULL;
    thread_t *tmp = NULL;
    int len = strlen(team_id) + strlen(chan_id) + 16;
    char *p = malloc(len);

    sprintf(p, "CREATE THREAD %s %s", team_id, chan_id);
    for (line_t *curr = file_io->lines; curr; curr = curr->next)
        if (curr->type == CREATE && !strncmp(curr->line, p, len)) {
            tmp = malloc(sizeof(thread_t));
            tmp->id = strdup(strtok(curr->line + len, " "));
            tmp->name = strdup(get_quotes_content(strtok(NULL, " ")));
            tmp->description = strdup(get_quotes_content(strtok(NULL, " ")));
            tmp->comment = get_comments(file_io, tmp->id);
            (threads) ? (last->next = tmp) : (threads = tmp);
            last = tmp;
        }
    free(p);
    return threads;
}

channel_t *get_channels(file_io_t *file_io, char *team_id)
{
    channel_t *channels = NULL;
    channel_t *last = NULL;
    channel_t *tmp = NULL;
    int len = (strlen(team_id) + 16);
    char *p = malloc(sizeof(char) * len);

    sprintf(p, "CREATE CHANNEL %s", team_id);
    for (line_t *curr = file_io->lines; curr; curr = curr->next)
        if (curr->type == CREATE && strncmp(curr->line, p, len - 1) == 0) {
            tmp = malloc(sizeof(channel_t));
            tmp->id = strdup(strtok(curr->line + len, " "));
            tmp->name = strdup(get_quotes_content(strtok(NULL, " ")));
            tmp->description = strdup(get_quotes_content(strtok(NULL, " ")));
            tmp->threads = get_threads(file_io, team_id, tmp->id);
            tmp->next = NULL;
            (channels) ? (last->next = tmp) : (channels = tmp);
            last = tmp;
        }
    free(p);
    return channels;
}

subscribed_t *get_subscribed(file_io_t *file_io, char *team_id, data_server_t *d)
{
    subscribed_t *sub = NULL;
    subscribed_t *last = NULL;
    subscribed_t *tmp = NULL;
    int len = (strlen(team_id) + 12);
    char *p = malloc(sizeof(char) * len);

    sprintf(p, "SUBSCRIBE %s", team_id);
    for (line_t *curr = file_io->lines; curr; curr = curr->next)
        if (curr->type == SUBSCRIBED && strncmp(curr->line, p, len - 1) == 0) {
            tmp = malloc(sizeof(subscribed_t));
            tmp->user = get_user_by_id(d, strtok(curr->line + len, " "));
            tmp->next = NULL;
            (sub) ? (last->next = tmp) : (sub = tmp);
            last = tmp;
        }
    free(p);
    return sub;
}

team_t *get_teams(file_io_t *file_io, data_server_t *data)
{
    team_t *teams = NULL;
    team_t *last = NULL;
    team_t *tmp = NULL;
    line_t *curr = file_io->lines;

    while (curr) {
        if (curr->type == CREATE && strncmp(curr->line + 7, "TEAM", 4) == 0) {
            tmp = malloc(sizeof(team_t));
            tmp->id = strdup(strtok(curr->line + 12, " "));
            tmp->name = strdup(strtok(NULL, " "));
            tmp->description = strdup(strtok(NULL, " "));
            tmp->channels = get_channels(file_io, tmp->id);
            tmp->subcribed = get_subscribed(file_io, tmp->id, data);
            (teams) ? (last->next = tmp) : (teams = tmp);
            last = tmp;
        }
        curr = curr->next;
    }
    return teams;
}
