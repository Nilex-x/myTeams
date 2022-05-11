/*
** EPITECH PROJECT, 2022
** manage_messages.c
** File description:
** manage_messages
*/

#include "my_teams.h"

void add_message(userinfo_t *info, char *from, char *message)
{
    message_t *new_msg = malloc(sizeof(message_t));
    message_t *temp = info->messages;

    if (!new_msg)
        return;
    new_msg->from = strdup(from);
    new_msg->to = strdup(info->id);
    new_msg->message = strdup(message);
    new_msg->isRead = false;
    new_msg->next = NULL;
    if (!info->messages) {
        info->messages = new_msg;
        return;
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new_msg;
    return;
}

void free_message(message_t *msgs)
{
    message_t *next = NULL;

    while (msgs) {
        next = msgs->next;
        free(msgs->from);
        free(msgs->to);
        free(msgs->message);
        msgs = next;
    }
    return;
}