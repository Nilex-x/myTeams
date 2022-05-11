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

    #define FILEPATH_SAVE "./info.save"
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

typedef struct subscribed_s
{
    struct userinfo_s *user;
    struct subscribed_s *next;
} subscribed_t;

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
    subscribed_t *subcribed;
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

/*                  command handle function                              */
/**
 * @brief Sort command given on paramete
 *
 * @param client the client who made the command
 * @param data data_server_t struct
 * @param cmd the command string
 * @return int
 */
int sort_command(struct client_s *client, data_server_t *data, char *cmd);


/*                       init function                                   */
/**
 * @brief Create user with userinfo given on parameter
 *
 * @param name name of user to find
 * @param info info of user if found
 * @param data data_server_t struct
 * @return users_t *
 */
users_t *init_user(char *name, data_server_t *data, userinfo_t *info);


/*                          users                                        */

/**
 * @brief Add user in list from data_server_t *data
 *
 * @param toadd user struct to add in list
 * @param data data_server_t struct
 */
void add_user(users_t *toadd, data_server_t *data);

/**
 * @brief Get the user by uuid string
 *
 * @param uuid uuid of user to find
 * @param data data_server_t struct
 * @return users_t *
 */
users_t *get_user_by_uuid(char *uuid, data_server_t *data);
/**
 * @brief Get the user by name strign
 *
 * @param name name of user to find
 * @param data data_server_t struct
 * @return users_t*
 */
users_t *get_user_by_name(char *name, data_server_t *data);
/**
 * @brief Remove user in list from data_server_t *data
 *
 * @param torm user struct to remove
 * @param data data_server_t struct
 */
void remove_user(users_t *torm, data_server_t *data);
/**
 * @brief Free users list
 *
 * @param users users list to free
 */
void free_users(users_t *users);


/*                        userinfos                                      */

/**
 * @brief Add user in list from data_server_t *data
 *
 * @param toadd user struct to add in list
 * @param data data_server_t struct
 */
void add_userinfo(userinfo_t *toadd, data_server_t *data);
/* get user by uuid */
/**
 * @brief Get the user info by uuid string
 *
 * @param uuid uuid of user to find
 * @param data data_server_t struct
 * @return userinfo_t*
 */
userinfo_t *get_user_info_by_uuid(char *uuid, data_server_t *data);
/* get user by name */
/**
 * @brief Get the user info by name string
 *
 * @param name name of userinfo to find
 * @param data data_server_t struct
 * @return userinfo_t*
 */
userinfo_t *get_user_info_by_name(char *name, data_server_t *data);
/* remove userinfo in list from data_server_t *data */
/**
 * @brief
 *
 * @param torm userinfo struct to remove
 * @param data data_server_t struct
 */
void remove_userinfo(userinfo_t *torm, data_server_t *data);
/* free userinfo list */
/**
 * @brief
 *
 * @param infos userinfo struct to free
 */
void free_user_infos(userinfo_t *infos);

/*                        messages                                       */

/**
 * @brief Create message and add in list from userinfo_t *info
 *
 * @param info userinfo struct of user receive message
 * @param from userinfo struct of user send message
 * @param message message string of user
 */
void add_message(userinfo_t *info, char *from, char *message);
/**
 * @brief  free message list
 *
 * @param msgs
 */
void free_message(message_t *msgs);


#endif /* !MY_TEAMS_H_ */
