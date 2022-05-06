/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** create_teams
*/

#include "file_io.h"

thread_t *get_threads(file_io_t *file_io, char *team_id, char *chan_id)
{
    thread_t *threads = NULL;
    thread_t *last = NULL;
    thread_t *tmp = NULL;
    int len = strlen(team_id) + strlen(chan_id) + 16;
    char *p = malloc(len);

    sprintf(p, "CREATE THREAD %s %s", team_id, chan_id);
    for (line_t *curr = file_io->lines; curr; curr = curr->next)
        if (curr->type == CREATE && !strcmp(curr->line, p)) {
            tmp = malloc(sizeof(thread_t));
            tmp->id = strdup(strtok(curr->line + len, " "));
            tmp->name = strdup(get_quotes_content(strtok(NULL, " ")));
            tmp->description = strdup(get_quotes_content(strtok(NULL, " ")));
            tmp->comment = NULL;
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

team_t *get_teams(file_io_t *file_io)
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
            (teams) ? (last->next = tmp) : (teams = tmp);
            last = tmp;
        }
        curr = curr->next;
    }
    return teams;
}
