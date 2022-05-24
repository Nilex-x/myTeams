/*
** EPITECH PROJECT, 2022
** manage_connectiion.c
** File description:
** manage_connection
*/

#include "my_teams.h"

int login(client_t *c, char **arg, data_server_t *data)
{
    char *name = NULL;
    userinfo_t *info = NULL;
    char *response = NULL;
    int code = 301 ;

    if (c->user)
        c->data_send = add_send(c->data_send, "102 Already logged-in.\n");
    if (len_array(arg) != 2)
        c->data_send = add_send(c->data_send, "502 Missing arguments.\n");
    if (c->user || len_array(arg) != 2)
        return (0);
    name = get_quotes_content(arg[1]);
    info = get_user_info_by_name(name, data);
    code = !info ? 301 : 302;
    c->user = init_user(arg[1], data, info);
    asprintf(&response, "%d\a%s\a%s\n", code, info->name, info->id);
    c->data_send = add_send(c->data_send, response);
    c->user->client = c;
    free(name);
    return (0);
}

int logout(client_t *client, char **arg, data_server_t *data)
{
    char *response = NULL;
    users_t *user = client->user;

    if (user) {
        client->isQuit = true;
        asprintf(&response, "303\a%s\a%s\n", user->info->name, user->info->id);
        client->data_send = add_send(client->data_send, response);
        server_event_user_logged_out(client->user->info->id);
        client->user = NULL;
    } else
        client->data_send = add_send(client->data_send, "503 - Not logged-in.\n");
    return (0);
}