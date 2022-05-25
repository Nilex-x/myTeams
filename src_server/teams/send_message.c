/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** send_message
*/

#include "my_teams.h"

message_t *dup_msg(message_t *msg)
{
    message_t *new = malloc(sizeof(message_t));

    if (!new)
        return NULL;
    new->from = strdup(msg->from);
    new->to = strdup(msg->to);
    new->message = strdup(msg->message);
    new->isRead = msg->isRead;
    new->next = NULL;
    return new;
}

void append_message_to_udata(userinfo_t *from, userinfo_t *to, char *msg, bool isRead)
{
    message_t *mesg = malloc(sizeof(message_t));
    message_t *mesg_sec = NULL;
    message_t *f_msg = from->messages;
    message_t *t_msg = to->messages;

    mesg->from = strdup(from->id);
    mesg->to = strdup(to->id);
    mesg->message = strdup(msg);
    mesg->isRead = isRead;
    mesg->next = NULL;
    mesg_sec = dup_msg(mesg);
    while (f_msg && f_msg->next)
        f_msg = f_msg->next;
    while (t_msg && t_msg->next)
        t_msg = t_msg->next;
    (f_msg) ? (f_msg->next = mesg) : (from->messages = mesg);
    (t_msg) ? (t_msg->next = mesg_sec) : (to->messages = mesg_sec);
}

char *alloc_message(char *from_id, char *to_id, char *message, int is_read)
{
    char *line = malloc(strlen(message) + 87);

    if (is_read)
        sprintf(line, "MESSAGE R %s %s \"%s\"", from_id, to_id, message);
    else
        sprintf(line, "MESSAGE N %s %s \"%s\"", from_id, to_id, message);
    return (line);
}

void send_message_connected_user(struct client_s *cli
, struct userinfo_s *user, char *msg, data_server_t *data)
{
    char *line = NULL;
    message_t *curr = NULL;

    append_message_to_udata(cli->user->info, user, msg, true);
    line = alloc_message(cli->user->info->id, user->id, msg, 1);
    append_to_list(&data->list->lines, line);
    free(line);
    cli->data_send = add_send(cli->data_send, "313 - Message sent.\n");
    curr = user->messages;
    for (; curr->next; curr = curr->next);
    for (users_t *u = data->users; u; u = u->next) {
        if (u->info->id == user->id) {
            asprintf(&line, "201\a%s\a%s\a%s\n", curr->from, curr->to, msg);
            u->client->data_send = add_send(u->client->data_send, line);
            u->client->status = WRITE;
        }
        (line) ? free(line) : 0;
    }
    server_event_private_message_sended(cli->user->info->id, user->id, msg);
}

int send_message(struct client_s *c, struct userinfo_s *user
, char *message, data_server_t *data)
{
    char *line = NULL;

    if (strcmp(c->user->info->id, user->id) == 0) {
        asprintf(&line, "521\a%s\n", user->id);
        c->data_send = add_send(c->data_send,"521\n");
        free(line);
        return (c->status = WRITE);
    }
    if (strlen(message) > 512)
        c->data_send = add_send(c->data_send, "504 - Command too long.\n");
    else if (!get_user_by_uuid(user->id, data)) {
        append_message_to_udata(user, c->user->info, message, false);
        line = alloc_message(c->user->info->id, user->id, message, 0);
        append_to_list(&data->list->lines, line);
        free(line);
        c->data_send = add_send(c->data_send, "313 - Message sent.\n");
        server_event_private_message_sended(c->user->info->id, user->id, message);
    } else
        send_message_connected_user(c, user, message, data);
    return (c->status = WRITE);
}
