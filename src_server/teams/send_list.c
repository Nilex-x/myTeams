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
        free(response);
        users = users->next;
    }
    // free(response);
    return (0);
}

static int send_all_messages(client_t *user, userinfo_t *to)
{
    message_t *msg = user->user->info->messages;
    char *res = NULL;

    while (msg) {
        printf("msg info from: [%s] to: [%s] msg: [%s] status: [%s]\n", msg->from, msg->to, msg->message, msg->isRead ? "read" : "pending");
        if (strcmp(msg->from, to->id) == 0 || strcmp(msg->to, to->id) == 0) {
            printf("nice msg: [%s] from: [%s]\n", msg->message, msg->from);
            asprintf(&res, "314\a%s\a%d\a%s\n", msg->to, msg->timestamp, msg->message);
            user->data_send = add_send(user->data_send, res);
            free(res);
        }
        msg = msg->next;
    }
    return (0);
}

int cmd_messages(client_t *c, char **arg, data_server_t *data)
{
    userinfo_t *user = NULL;
    char *response = NULL;

    if (len_array(arg) != 2)
        c->data_send = add_send(c->data_send, "501\n");
    if (!c->user)
        c->data_send = add_send(c->data_send, "502\n");
    if (len_array(arg) != 2 || !c->user)
        return (0);
    user = get_user_info_by_uuid(arg[1], data);
    if (!user) {
        asprintf(&response, "521\a%s\n", arg[1]);
        c->data_send = add_send(c->data_send, response);
        return (0);
    }
    else
        send_all_messages(c, user);
    return (0);
}

int send_team_subscribed(client_t *c, userinfo_t *user, data_server_t *data)
{
    team_t *team = data->teams;
    char *response = NULL;

    while (team) {
        if (get_subscribe_by_id(team, user->id)) {
            asprintf(&response, "317\a%s\a%s\a%s\n", team->id, team->name,
                                                    team->description);
            c->data_send = add_send(c->data_send, response);
        }
        team = team->next;
    }
    free(response);
    return (0);
}

int cmd_subscribed(client_t *c, char **arg, data_server_t *data)
{
    team_t *team = NULL;
    char *response = NULL;

    if (!c->user) {
        c->data_send = add_send(c->data_send, "502\n");
        return (0);
    }
    if (len_array(arg) == 2) {
        team = get_teams_by_id(arg[1], data);
        if (!team) {
            asprintf(&response, "522\a%s\n", arg[1]);
            c->data_send = add_send(c->data_send, response);
            free(response);
        } else
            send_subscribed(c, team, data);
    } else
        send_team_subscribed(c, c->user->info, data);
    return (0);
}