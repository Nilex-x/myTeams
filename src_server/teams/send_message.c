/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** send_message
*/

#include "my_teams.h"

void append_message_to_udata(userinfo_t *from, userinfo_t *to, char *msg, bool isRead)
{
    message_t *mesg = malloc(sizeof(message_t));
    message_t *f_msg = from->messages;
    message_t *t_msg = to->messages;

    printf("\t1\n");
    mesg->from = strdup(from->id);
    printf("\t2\n");
    mesg->to = strdup(to->id);
    printf("\t3\n");
    mesg->message = strdup(msg);
    printf("\t4\n");
    mesg->isRead = isRead;
    printf("\t5\n");
    mesg->next = NULL;
    printf("\t6\n");
    while (f_msg && f_msg->next)
        f_msg = f_msg->next;
    while (t_msg && t_msg->next)
        t_msg = t_msg->next;
    printf("\t7\n");
    (f_msg) ? (f_msg->next = mesg) : (from->messages = mesg);
    printf("\t8\n");
    (t_msg) ? (t_msg->next = mesg) : (to->messages = mesg);
}

char *alloc_message(char *from_id, char *to_id, char *message, int is_read)
{
    char *line = malloc(strlen(message) + 85);

    if (is_read)
        sprintf(line, "MESSAGE R %s %s \"%s\"", from_id, to_id, message);
    else
        sprintf(line, "MESSAGE N %s %s \"%s\"", from_id, to_id, message);
    return (line);
}

int send_message_connected_user(struct client_s *cli
, struct userinfo_s *user, char *message, data_server_t *data)
{
    char *line = NULL;
    message_t *curr = NULL;

    append_message_to_udata(cli->user->info, user, message, true);
    line = alloc_message(cli->user->info->id, user->id, message, 1);
    append_to_list(&data->list->lines, line);
    free(line);
    cli->data_send = add_send(cli->data_send, "313 - Message sent.\n");
    cli->status = WRITE;
    curr = user->messages;
    for (; curr->next; curr = curr->next);
    line = malloc(81 + strlen(message));
    for (users_t *u = data->users; u; u = u->next)
        if (u->info->id == user->id) {
            sprintf(line, "201 %s %s \"%s\"", curr->from, curr->to, message);
            u->client->data_send = add_send(u->client->data_send, line);
        }
    free(line);
    return 0;
}

int send_message(struct client_s *c, struct userinfo_s *user
, char *message, data_server_t *data)
{
    char *line = NULL;

    if (strcmp(c->user->info->id, user->id) == 0) {
        c->data_send = add_send(c->data_send,"521 - Wrong user uuid.\n");
        c->status = WRITE;
        return (0);
    }
    if (strlen(message) > 512)
        c->data_send = add_send(c->data_send, "504 - Command too long.\n");
    else if (!get_user_by_uuid(user->id, data)) {
        append_message_to_udata(user, c->user->info, message, false);
        line = alloc_message(c->user->info->id, user->id, message, 0);
        append_to_list(&data->list->lines, line);
        free(line);
        c->data_send = add_send(c->data_send, "313 - Message sent.\n");
    } else
        return send_message_connected_user(c, user, message, data);
    c->status = WRITE;
    return (0);
}
