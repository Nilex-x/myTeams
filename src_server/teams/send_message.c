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
    new->timestamp = msg->timestamp;
    new->next = NULL;
    return new;
}

void append_message_to_udata(userinfo_t *f, userinfo_t *t, char *msg, bool r)
{
    message_t *mesg = malloc(sizeof(message_t));
    message_t *mesg_sec = NULL;
    message_t *f_msg = f->messages;
    message_t *t_msg = t->messages;

    mesg->from = strdup(f->id);
    mesg->to = strdup(t->id);
    mesg->message = strdup(msg);
    mesg->isRead = r;
    mesg->next = NULL;
    mesg->timestamp = time(NULL);
    mesg_sec = dup_msg(mesg);
    while (f_msg && f_msg->next)
        f_msg = f_msg->next;
    while (t_msg && t_msg->next)
        t_msg = t_msg->next;
    (f_msg) ? (f_msg->next = mesg) : (f->messages = mesg);
    (t_msg) ? (t_msg->next = mesg_sec) : (t->messages = mesg_sec);
}

char *alloc_message(char *from_id, char *to_id, char *message, bool is_read)
{
    char *line = NULL;
    time_t ts = time(NULL);

    if (is_read)
        asprintf(&line, "MESSAGE\aR\a%s\a%s\a%ld\a%s", from_id, to_id, ts, message);
    else
        asprintf(&line, "MESSAGE\aN\a%s\a%s\a%ld\a%s", from_id, to_id, ts, message);
    return (line);
}

void send_message_connected_user(struct client_s *cli
, struct userinfo_s *user, char *msg, data_server_t *data)
{
    char *line = NULL;
    message_t *curr = NULL;
    time_t t = time(NULL);

    append_message_to_udata(cli->user->info, user, msg, true);
    asprintf(&line, "MESSAGE\aR\a%s\a%s\a%ld\a%s", cli->user->info->id
    , user->id, t, msg);
    append_to_list(&data->list->lines, line);
    free(line);
    cli->data_send = add_send(cli->data_send, "313 - Message sent.\n");
    curr = user->messages;
    for (; curr->next; curr = curr->next);
    for (users_t *u = data->users; u; u = u->next)
        if (u->info->id == user->id) {
            asprintf(&line, "211\a%s\a%s\a%ld\n", curr->from, msg, t);
            u->client->data_send = add_send(u->client->data_send, line);
            u->client->status = WRITE;
            free(line);
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
        c->data_send = add_send(c->data_send, "503 - Command too long.\n");
    else if (!get_user_by_uuid(user->id, data)) {
        append_message_to_udata(c->user->info, user, message, false);
        line = alloc_message(c->user->info->id, user->id, message, false);
        append_to_list(&data->list->lines, line);
        free(line);
        c->data_send = add_send(c->data_send, "313 - Message sent.\n");
        server_event_private_message_sended(c->user->info->id, user->id, message);
    } else
        send_message_connected_user(c, user, message, data);
    return (c->status = WRITE);
}
