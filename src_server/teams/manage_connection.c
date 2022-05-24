/*
** EPITECH PROJECT, 2022
** manage_connectiion.c
** File description:
** manage_connection
*/

#include "my_teams.h"

int login(client_t *client, char **arg, data_server_t *data)
{
    userinfo_t *info = get_user_info_by_name(arg[1], data);
    char *response = NULL;

    if (client->user) {
        client->data_send = add_send(client->data_send, "102 Already logged-in.\n");
        return (0);
    }
    if (len_array(arg) != 2) {
        client->data_send = add_send(client->data_send, "502 Missing arguments.\n");
        return (0);
    }
    client->user = init_user(arg[1], data, info);
    if (!info)
        asprintf(&response, "301\a%s\a%s\n", info->name, info->id);
    else
        asprintf(&response, "302\a%s\a%s\n", info->name, info->id);
    client->data_send = add_send(client->data_send, response);
    client->user->client = client;
    return (0);
}

int logout(client_t *client, char **arg, data_server_t *data)
{
    char *response = NULL;
    users_t *user = client->user;

    if (user) {
        asprintf(&response, "303\a%s\a%s\n", user->info->name, user->info->id);
        client->data_send = add_send(client->data_send, response);
        server_event_user_logged_out(client->user->info->id);
        client->user = NULL;
    } else
        client->data_send = add_send(client->data_send, "503 - Not logged-in.\n");
    return (0);
}