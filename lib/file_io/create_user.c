/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** create_user
*/

#include "file_io.h"

char *get_uid_by_name(file_io_t *file_io, char *name)
{
    line_t *c = file_io->lines;
    regex_t regex;
    regmatch_t mat[1];
    char *pattern = malloc(sizeof(char) * (strlen(name) + 29));

    sprintf(pattern, "^USER[ ]*([a-zA-Z0-9]*)[ ]\"%s\"", name);
    if (regcomp(&regex, pattern, 0) == 1)
        return (NULL);
    while (c) {
        if (c->type == USER && regexec(&regex, c->line, 1, mat, 0) == 0)
            return (c->line + mat[0].rm_so);
        c = c->next;
    }
    return NULL;
}

message_t *create_message(line_t *c, regmatch_t mat[3], char *id)
{
    message_t *msg = malloc(sizeof(message_t));

    if (strncmp(c->line + mat[0].rm_so, id, 36) == 0) {
        msg->from = strdup(id);
        msg->to = strdup(c->line + mat[1].rm_so);
        msg->message = strdup(c->line + mat[2].rm_so);
        msg->isRead = (c->line[8] == 'R') ? true : false;
        return msg;
    } else if (strncmp(c->line + mat[1].rm_so, id, 36) == 0) {
        msg->from = strdup(c->line + mat[0].rm_so);
        msg->to = strdup(id);
        msg->message = strdup(c->line + mat[2].rm_so);
        msg->isRead = (c->line[8] == 'R') ? true : false;
        return msg;
    }
    free(msg);
    return NULL;
}

message_t *get_messages_by_user(file_io_t *file_io, char *id)
{
    regex_t r;
    regmatch_t mat[3];
    message_t *messages = NULL;
    message_t *msg = NULL;
    message_t *cmsg = NULL;
    char *p = malloc(sizeof(char) * (strlen(id) + 29));

    sprintf(p, "^MESSAGE[ ]*[R-U][ ]*%s[ ]*%s[ ]*([\x20-\x7E]*)"
    , UUID_REGEX, UUID_REGEX);
    if (regcomp(&r, p, 0) == 1)
        return (NULL);
    for (line_t *c = file_io->lines; c; c = c->next)
        if (c->type == MESSAGE && regexec(&r, c->line, 3, mat, 0) == 0) {
            msg = create_message(c, mat, id);
            (msg) ? (cmsg) ? (cmsg->next = msg) : (messages = msg) : 0;
            (msg) ? cmsg = msg : 0;
        }
    free(p);
    return messages;
}

userinfo_t *create_user_by_name(file_io_t *file_io, char *name)
{
    userinfo_t *user = malloc(sizeof(userinfo_t));
    uuid_t uid;
    char *line = NULL;

    if (!user)
        return NULL;
    user->name = strdup(name);
    user->id = get_uid_by_name(file_io, name);
    if (!user->id) {
        uuid_generate(uid);
        user->id = malloc(sizeof(char) * 37);
        uuid_unparse(uid, user->id);
        line = malloc(sizeof(char) * (strlen(name) + 45));
        sprintf(line, "USER %s \"%s\"", user->id, name);
        append_to_list(&file_io->lines, line);
        user->messages = NULL;
        free(line);
    } else
        user->messages = get_messages_by_user(file_io, user->id);
    return user;
}