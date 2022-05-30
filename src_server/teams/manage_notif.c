/*
** EPITECH PROJECT, 2022
** manage_notif.c
** File description:
** manage_notif
*/

#include "my_teams.h"

int send_notif_team(data_server_t *data, users_t *user, team_t *t)
{
    users_t *temp = data->users;
    char *text = NULL;

    if (!temp)
        return (0);
    asprintf(&text, "221\a%s\a%s\a%s\n", t->id, t->name, t->description);
    while (temp) {
        if (temp != user)
            temp->client->data_send = add_send(temp->client->data_send, text);
        temp = temp->next;
    }
    free(text);
    return (0);
}