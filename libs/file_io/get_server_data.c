/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** get_server_data
*/

#include "file_io.h"

struct data_server_s *get_server_data(char *file_name)
{
    data_server_t *data = malloc(sizeof(data_server_t));
    file_io_t *file_io = file_io_create(file_name);

    if (!data) {
        file_io_destroy(file_io);
        return NULL;
    }
    data->list = file_io;
    data->userinfos = get_all_user_infos(file_io);
    data->teams = get_teams(file_io, data);
    data->users = NULL;
    return data;
}

void remove_subscribed(file_io_t *f_io, char *id, char *uid)
{
    line_t *curr = f_io->lines->next;
    line_t *last = f_io->lines;
    char *p = NULL;

    asprintf(&p, "SUBSCRIBED\a%s\a%s", id, uid);
    if (last->type == SUBSCRIBED && strcmp(last->line, p) == 0) {
        f_io->lines = curr;
        return;
    }
    for (; curr; curr = curr->next) {
        if (curr->type == SUBSCRIBED && strcmp(curr->line, p) == 0) {
            last->next = curr->next;
            free(curr);
            break;
        }
        last = curr;
    }
    free(p);
}
