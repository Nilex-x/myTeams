/*
** EPITECH PROJECT, 2022
** send_list.c
** File description:
** send_list
*/

#include "my_teams.h"

int send_list_of_users(client_t *c, char **arg, data_server_t *data)
{
    userinfo_t *users = data->userinfos;
    char *response = NULL;

    (void) arg;
    while (users) {
        printf("Nikzebi name: [%s] id: [%s]\n", users->name, users->id);
        asprintf(&response, "311\a%s\a%s\a%d\n", users->id, users->name,
                                get_user_by_uuid(users->id, data) ? 1 : 0);
        c->data_send = add_send(c->data_send, response);
        users = users->next;
    }
    free(response);
    return (0);
}