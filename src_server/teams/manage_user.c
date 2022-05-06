/*
** EPITECH PROJECT, 2022
** manage_user.c
** File description:
** manage_user
*/

#include "my_teams.h"

userinfo_t *find_user_info_by_name(users_t *user, char *name)
{
    userinfo_t *list = user->data->userinfos;
}

userinfo_t *connect_user(users_t *user, char *name)
{
    uuid_t binuuid;

    userinfo_t *list = user->data->userinfos;
    if (!list)
        list = malloc(sizeof(userinfo_t));
    while (list->next)
        list = list->next;
    uuid_generate_random(binuuid);
    list->id = malloc(37);
    uuid_unparse(binuuid, list->id);
    list->name = strdup(name);
    printf("new user connect uuid: %s, name: %s\n", list->id, list->name);
    return (list);
}