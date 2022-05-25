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
    info->data->list = file_io_create(FILEPATH_SAVE);
}

users_t *init_user(char *name, data_server_t *data, userinfo_t *i, client_t *c)
{
    users_t *user = NULL;

    if (!i) {
        i = create_user_by_name(data->list, name);
        add_userinfo(i, data);
        server_event_user_created(i->id, i->name);
    }
    user = malloc(sizeof(users_t));
    if (!user)
        return NULL;
    user->info = i;
    user->channel = NULL;
    user->team = NULL;
    user->thread = NULL;
    user->client = c;
    add_user(user, data);
    server_event_user_logged_in(i->id);
    return user;
}