/*
** EPITECH PROJECT, 2022
** manage_init_data.c
** File description:
** mange_init
*/

#include "teams_serv.h"
#include "my_teams.h"

void init_data(server_t *info)
{
    info->data = malloc(sizeof(data_server_t));
    if (!info->data)
        return;
    info->data->users = NULL;
    info->data->teams = NULL;
    info->data->userinfos = NULL;
    info->data->list = file_io_create("../../info.save");
}

users_t *init_user(userinfo_t *info, data_server_t *data)
{
    users_t *new_user = malloc(sizeof(users_t));

    if (!new_user)
        return NULL;
    new_user->info = info;
    new_user->channel = NULL;
    new_user->next = NULL;
    new_user->team = NULL;
    new_user->thread = NULL;
    add_userinfo(info, data);
    add_user(new_user, data);
    return new_user;
}