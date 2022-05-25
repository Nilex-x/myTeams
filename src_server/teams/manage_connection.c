/*
** EPITECH PROJECT, 2022
** manage_connectiion.c
** File description:
** manage_connection
*/

#include "my_teams.h"

int notif_connection(data_server_t *data, users_t *user, bool isLog)
{
    users_t *temp = data->users;
    char *res = NULL;

    if (!temp)
        return (0);
    asprintf(&res, "%d\a%s\a%s\n", isLog ? 201 : 202, user->info->id,
                                                        user->info->name);
    while (temp) {
        if (temp != user)
            temp->client->data_send = add_send(temp->client->data_send, res);
        temp = temp->next;
    }
    free(res);
    return (0);
}

int send_log_to_client(client_t *c, data_server_t *data, bool created, bool log)
{
    char *res = NULL;

    if (log) {
        asprintf(&res, "%d\a%s\a%s\n", created ? 301 : 302, c->user->info->id,
                                        c->user->info->name);
    } else {
        asprintf(&res, "303\a%s\a%s\n", c->user->info->name,
                                        c->user->info->id);
    }
    c->data_send = add_send(c->data_send, res);
    free(res);
    return (0);
}

int login(client_t *c, char **arg, data_server_t *data)
{
    char *name = NULL;
    userinfo_t *info = NULL;

    if (c->user)
        c->data_send = add_send(c->data_send, "102 Already logged-in.\n");
    if (!c->user && len_array(arg) != 2)
        c->data_send = add_send(c->data_send, "502 Missing arguments.\n");
    if (c->user || len_array(arg) != 2)
        return (0);
    name = get_quotes_content(arg[1]);
    info = get_user_info_by_name(name, data);
    c->user = init_user(name, data, info, c);
    send_log_to_client(c, data, !info ? true : false, true);
    notif_connection(data, c->user, true);
    free(name);
    return (0);
}

int logout(client_t *c, char **arg, data_server_t *data)
{
    char *response = NULL;
    users_t *user = c->user;

    if (user) {
        send_log_to_client(c, data, false, false);
        notif_connection(data, user, false);
        server_event_user_logged_out(c->user->info->id);
        c->user->client = NULL;
        remove_user(c->user, data);
        c->isQuit = true;
        c->user = NULL;
        free(response);
    } else
        c->data_send = add_send(c->data_send, "503 - Not logged-in.\n");
    return (0);
}