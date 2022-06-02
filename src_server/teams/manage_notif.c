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
            temp->client->data_send = add_send(temp->client->data_send,
                                                text);
        temp = temp->next;
    }
    free(text);
    return (0);
}

int send_notif_channel(data_server_t *data, users_t *user, channel_t *c)
{
    subscribed_t *subs = user->team->subcribed;
    users_t *user_temp = NULL;
    char *text = NULL;

    if (!subs)
        return (0);
    asprintf(&text, "222\a%s\a%s\a%s\n", c->id, c->name, c->description);
    while (subs) {
        if (subs->user != user->info && get_user_by_id(data, subs->user->id)) {
            user_temp = get_user_by_uuid(subs->user->id, data);
            user_temp->client->data_send = add_send(
            user_temp->client->data_send, text);
        }
        subs = subs->next;
    }
    free(text);
    return (0);
}

int send_notif_thread(data_server_t *data, users_t *user, thread_t *trd)
{
    subscribed_t *subs = user->team->subcribed;
    users_t *user_temp = NULL;
    char *text = NULL;

    server_event_thread_created(user->channel->id, trd->id,
    user->info->id, trd->title, trd->body);
    if (!subs)
        return (0);
    asprintf(&text, "223\a%s\a%s\a%ld\a%s\a%s\n", trd->id, user->info->id,
    trd->timestamp, trd->title, trd->body);
    while (subs) {
        if (subs->user != user->info && get_user_by_id(data, subs->user->id)) {
            user_temp = get_user_by_uuid(subs->user->id, data);
            user_temp->client->data_send = add_send(
            user_temp->client->data_send, text);
        }
        subs = subs->next;
    }
    free(text);
    return (0);
}

int send_notif_reply(data_server_t *data, users_t *user, reply_t *r)
{
    subscribed_t *subs = user->team->subcribed;
    users_t *user_temp = NULL;
    char *text = NULL;

    if (!subs)
        return (0);
    asprintf(&text, "212\a%s\a%s\a%s\a%s\n", user->team->id, user->thread->id,
    r->creator_id, r->body);
    while (subs) {
        if (subs->user != user->info && get_user_by_id(data, subs->user->id)) {
            user_temp = get_user_by_uuid(subs->user->id, data);
            user_temp->client->data_send = add_send(
            user_temp->client->data_send, text);
        }
        subs = subs->next;
    }
    free(text);
    return (0);
}
