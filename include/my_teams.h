/*
** EPITECH PROJECT, 2022
** my_teams.h
** File description:
** my_teams
*/

#ifndef MY_TEAMS_H_
    #define MY_TEAMS_H_
    #include "lib.h"
    #include "teams_serv.h"
    #include "file_io.h"
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <uuid/uuid.h>

    #define UUID_REGEX "([0-9a-fA-F]{8}\b-[0-9a-fA-F]{4}\b-[0-9a-fA-F]{4}\b-\
                        [0-9a-fA-F]{4}\b-[0-9a-fA-F]{12})"

typedef struct message_s
{
    char *message;
    char *from;
    char *to;
    bool isRead;
    struct message_s *next;
} message_t;

typedef struct userinfo_s
{
    char *name;
    char *id;
    message_t *messages;
    struct userinfo_s *next;
} userinfo_t;

typedef struct thread_s
{
    char *id;
    char *name;
    char *description;
    char **comment;
    struct thread_s *next;
} thread_t;

typedef struct channel_s
{
    char *id;
    char *name;
    char *description;
    thread_t *threads;
    struct channel_s *next;
} channel_t;

typedef struct team_s
{
    char *id;
    char *name;
    char *description;
    channel_t *channels;
    userinfo_t *subcribed;
    struct team_s *next;
} team_t;

typedef struct users_s
{
    userinfo_t *info;
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    struct data_server_s *data;
    struct users_s *next;
} users_t;

typedef struct data_server_s
{
    struct file_io_s *list;
    userinfo_t *userinfos;
    users_t *users;
    team_t *teams;
} data_server_t;

struct client_s;

int sort_command(struct client_s *client, data_server_t *data, char *value);
users_t *init_user(userinfo_t *info, data_server_t *data);

#endif /* !MY_TEAMS_H_ */
