/*
** EPITECH PROJECT, 2022
** manage_users.c
** File description:
** manage_users
*/

#include "my_teams.h"

void remove_user(users_t *torm, data_server_t *data)
{
    users_t *temp = data->users;
    users_t *prev = NULL;

    while(temp) {
        if (temp == torm) {
            prev->next = temp->next;
            free(torm);
            return;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    return;
}

users_t *get_user_by_uuid(char *uuid, data_server_t *data)
{
    users_t *temp = data->users;

    while (temp) {
        if (strcmp(temp->info->id, uuid) == 0)
            return temp;
        temp = temp->next;
    }
    return (NULL);
}

users_t *get_user_by_name(char *name, data_server_t *data)
{
    users_t *temp = data->users;

    while (temp) {
        if (strcmp(temp->info->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return (NULL);
}

void add_user(users_t *toadd, data_server_t *data)
{
    users_t *temp = data->users;

    toadd->next = NULL;
    if (!temp) {
        data->users = toadd;
        return;
    }
    while(temp->next)
        temp = temp->next;
    temp->next = toadd;
    return;
}

void free_users(users_t *users)
{
    users_t *next = NULL;

    while (users) {
        next = users->next;
        free(users);
        users = next;
    }
    return;
}
