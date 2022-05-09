/*
** EPITECH PROJECT, 2022
** manage_user_infos.c
** File description:
** manage_user_infos
*/

#include "my_teams.h"

void free_message(message_t *msgs)
{
    message_t *next = NULL;

    while (msgs) {
        next = msgs->next;
        free(msgs->from);
        free(msgs->to);
        free(msgs->message);
        msgs = next;
    }
    return;
}

void remove_userinfo(userinfo_t *torm, data_server_t *data)
{
    userinfo_t *temp = data->userinfos;
    userinfo_t *prev = NULL;

    while (temp) {
        if (temp == torm) {
            prev->next = temp->next;
            free_message(torm->messages);
            free(torm->id);
            free(torm->name);
            return;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
    return;
}

void add_userinfo(userinfo_t *toadd, data_server_t *data)
{
    userinfo_t *temp = data->userinfos;

    toadd->next = NULL;
    if (!temp) {
        data->userinfos = toadd;
        return;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = toadd;
    return;
}


void free_user_infos(userinfo_t *infos)
{
    userinfo_t *temp = NULL;

    while (infos) {
        temp = infos->next;
        free(infos->id);
        free(infos->name);
        free_message(infos->messages);
        free(infos);
        infos = temp;
    }
    return;
}