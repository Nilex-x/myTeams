/*
** EPITECH PROJECT, 2022
** manage_replies.c
** File description:
** manage_replies
*/

#include "my_teams.h"

reply_t *get_reply_by_id(char *id, thread_t *thread)
{
    reply_t *temp = thread->replies;

    while (temp) {
        if (strcmp(temp->id, id) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

reply_t *create_add_reply(char *body, userinfo_t *user, thread_t *thread)
{
    reply_t *new = malloc(sizeof(reply_t));
    reply_t *temp = thread->replies;

    if (!new)
        return (NULL);
    new->id = generate_uuid();
    new->creator_id = strdup(user->id);
    new->timestamp = time(NULL);
    new->body = strdup(body);
    new->next = NULL;
    if (!thread->replies) {
        thread->replies = new;
        return (new);
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new;
    return (new);
}

void free_replies(reply_t *replies)
{
    reply_t *next = NULL;

    while (replies) {
        next = replies->next;
        free(replies->id);
        free(replies->body);
        free(replies->creator_id);
        free(replies);
        replies = next;
    }
}