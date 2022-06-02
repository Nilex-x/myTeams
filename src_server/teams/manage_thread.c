/*
** EPITECH PROJECT, 2022
** manage_thread.c
** File description:
** manage_thread
*/

#include "my_teams.h"

thread_t *get_thread_by_uuid(char *uuid, channel_t *channel)
{
    thread_t *thread = channel->threads;

    while (thread) {
        if (strcmp(thread->id, uuid) == 0)
            return (thread);
        thread = thread->next;
    }
    return NULL;
}

thread_t *get_thread_by_title(char *title, channel_t *channel)
{
    thread_t *thread = channel->threads;

    while (thread) {
        if (strcmp(thread->title, title) == 0)
            return (thread);
        thread = thread->next;
    }
    return NULL;
}

thread_t *create_add_thread(char *title, char *body, channel_t *channel,
userinfo_t *info)
{
    thread_t *thread = malloc(sizeof(thread_t));
    thread_t *temp = channel->threads;

    if (!thread)
        return (NULL);
    thread->id = generate_uuid();
    thread->creator_id = strdup(info->id);
    thread->title = strdup(title);
    thread->body = strdup(body);
    thread->timestamp = time(NULL);
    thread->replies = NULL;
    thread->next = NULL;
    if (!channel->threads) {
        channel->threads = thread;
        return (thread);
    }
    while (temp->next)
        temp = temp->next;
    temp->next = thread;
    return thread;
}

void free_thread(thread_t *thread)
{
    thread_t *next = NULL;

    while (thread) {
        next = thread->next;
        free(thread->id);
        free(thread->body);
        free(thread->title);
        free(thread->creator_id);
        free(thread);
        thread = next;
    }
    return;
}
