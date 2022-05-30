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

static int send_all_messages(client_t *user, userinfo_t *to)
{
    message_t *msg = user->user->info->messages;
    char *res = NULL;

    while (msg) {
        if (strcmp(msg->from, to->id) == 0) {
            printf("nice msg: [%s] from: [%s]\n", msg->message, msg->from);
            asprintf(&res, "314\a%s\a%d\a%s\n", msg->from, 0, msg->message);
            user->data_send = add_send(user->data_send, res);
        }
        if (strcmp(msg->to, to->id) == 0) {
            printf("nice msg: [%s] to: [%s]\n", msg->message, msg->to);
            asprintf(&res, "314\a%s\a%d\a%s\n", msg->to, 0, msg->message);
            user->data_send = add_send(user->data_send, res);
        }
        msg = msg->next;
    }
    free(res);
    return (0);
}

int cmd_messages(client_t *c, char **arg, data_server_t *data)
{
    userinfo_t *user = NULL;

    if (len_array(arg) != 2)
        c->data_send = add_send(c->data_send, "\n");
    if (!c->user)
        c->data_send = add_send(c->data_send, "\n");
    if (len_array(arg) != 2 || !c->user)
        return (0);
    user = get_user_info_by_uuid(arg[1], data);
    if (!user) {
        c->data_send = add_send(c->data_send, "\n");
        return (0);
    }
    send_all_messages(c, user);
    return (0);
}