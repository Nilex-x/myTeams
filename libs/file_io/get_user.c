/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** get_subscribed
*/

#include "file_io.h"

userinfo_t *get_user_by_id(data_server_t *data, char *id)
{
    for (userinfo_t *user = data->userinfos; user; user = user->next)
        if (strcmp(user->id, id) == 0)
            return user;
    return NULL;
}
