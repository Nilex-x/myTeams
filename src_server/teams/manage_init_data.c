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
    info->data->list = file_io_create("../../info.save");
}

users_t *init_user(userinfo_t *info, data_server_t *data)
{
    users_t *new_user = malloc(sizeof(userinfo_t));
    users_t *list = data->users;
    users_t *prev = NULL;

    if (!new_user)
        return NULL;
    while (list) {
        prev = list;
        list = list->next;
    }
    new_user->info = info;
    new_user->channel = NULL;
    new_user->next = NULL;
    new_user->team = NULL;
    new_user->thread = NULL;
    list = new_user;
    if (prev)
        prev->next = new_user;
    return new_user;
}