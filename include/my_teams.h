/*
** EPITECH PROJECT, 2022
** my_teams.h
** File description:
** my_teams
*/

#ifndef MY_TEAMS_H_
    #define MY_TEAMS_H_
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

typedef struct data_server_s
{
    userinfo_t *userinfos;
    users_t *users;
    team_t *teams;
} data_server_t;

typedef struct message_s
{
    char *message;
    userinfo_t *from;
    userinfo_t *to;
    bool isRead;
    struct message_s *next;
} message_t;

typedef struct userinfo_s
{
    char *name;
    char *id;
    message_t *messages;
} userinfo_t;

typedef struct users_s
{
    userinfo_t *info;
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    struct users_s *next;
} users_t;

typedef struct thread_s
{
    char *description;
    char **comment;
    struct thread_s *next;
} thread_t;

typedef struct channel_s
{
    char *description;
    thread_t *threads;
    struct channel_s *next;
} channel_t;

typedef struct team_s
{
    char *description;
    channel_t *channels;
    userinfo_t *subcribed;
    struct team_s *next;
} team_t;


#endif /* !MY_TEAMS_H_ */
