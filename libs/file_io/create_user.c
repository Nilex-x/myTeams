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
    regfree(&regex);
    free(pattern);
    return NULL;
}

message_t *create_message(line_t *c, char *id)
{
    message_t *msg = malloc(sizeof(message_t));
    char *ts = strndup(c->line + 84, 10);

    msg->timestamp = atoi(ts);
    free(ts);
    msg->message = strdup(c->line + 95);
    msg->isRead = (c->line[8] == 'R') ? true : false;
    msg->next = NULL;
    if (strncmp(c->line + 10, id, 36) == 0) {
        msg->from = strdup(id);
        msg->to = strndup(c->line + 47, 36);
        return msg;
    }
    msg->from = strndup(c->line + 10, 36);
    msg->to = strdup(id);
    return msg;
}

message_t *get_messages_by_user(file_io_t *file_io, char *id)
{
    message_t *messages = NULL;
    message_t *msg = NULL;
    message_t *cmsg = NULL;

    for (line_t *c = file_io->lines; c; c = c->next) {
        if (c->type == MESSAGE && (strncmp(c->line + 10, id, 36) == 0
        || strncmp(c->line + 47, id, 36) == 0)) {
            msg = create_message(c, id);
            (msg) ? (cmsg) ? (cmsg->next = msg) : (messages = msg) : 0;
            (msg) ? cmsg = msg : 0;
        }
    }
    return messages;
}

userinfo_t *create_user_by_name(file_io_t *file_io, char *name)
{
    userinfo_t *user = malloc(sizeof(userinfo_t));
    char *line = NULL;

    if (!user)
        return NULL;
    if (!get_uid_by_name(file_io, name)) {
        user->id = generate_uuid();
        asprintf(&line, "USER\a%s\a%s", user->id, name);
        append_to_list(&file_io->lines, line);
        user->messages = NULL;
        user->name = strdup(name);
        free(line);
        return user;
    } else
        user->messages = get_messages_by_user(file_io, user->id);
    free(user);
    return NULL;
}

userinfo_t *get_all_user_infos(file_io_t *file_io)
{
    userinfo_t *users = NULL;
    userinfo_t *user = NULL;
    userinfo_t *cuser = NULL;

    for (line_t *c = file_io->lines; c; c = c->next) {
        if (c->type == USER) {
            user = malloc(sizeof(userinfo_t));
            user->id = strndup(c->line + 5, 36);
            user->name = strdup(c->line + 42);
            user->messages = get_messages_by_user(file_io, user->id);
            user->next = NULL;
            (user) ? (users) ? (cuser->next = user) : (users = user) : 0;
            (user) ? cuser = user : 0;
        }
    }
    return users;
}
