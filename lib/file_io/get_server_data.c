/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** get_server_data
*/

#include "file_io.h"

data_server_t *get_server_data(char *file_name)
{
    data_server_t *data = malloc(sizeof(data_server_t));
    file_io_t *file_io = file_io_create(file_name);
    char *line = NULL;

    if (!data)
        return NULL;
    data->list = file_io;
    data->teams = get_teams(file_io);
    data->users = NULL;
    data->userinfos = get_all_user_infos(file_io);
    return data;
}
