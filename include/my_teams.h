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
    #define COMMANDS "LOGIN LOGOUT CREATE SEND SUBSCRIBE "\
                    "UNSUBSCRIBE INFO USER USERS HELP MESSAGES"

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
    char *creator_id;
    char *title;
    char *body;
    time_t timestamp;
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
    struct client_s *client;
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

typedef struct client_s client_t;

/*                  command handle function                              */

/**
 * @brief Sort command given on paramete
 *
 * @param client the client who made the command
 * @param data data_server_t struct
 * @param cmd the command string
 * @return int
 */
int sort_command(client_t *client, data_server_t *data, char *cmd);

/*                       init function                                   */

/**
 * @brief Create user with userinfo given on parameter
 *
 * @param name name of user to find
 * @param info info of user if found
 * @param data data_server_t struct
 * @param c client link to user
 * @return users_t *
 */
users_t *init_user(char *name, data_server_t *data,
                                userinfo_t *i, client_t *c);

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

/**
 * @brief Get the user info by uuid string
 *
 * @param uuid uuid of user to find
 * @param data data_server_t struct
 * @return userinfo_t*
 */
userinfo_t *get_user_info_by_uuid(char *uuid, data_server_t *data);

/**
 * @brief Get the user info by name string
 *
 * @param name name of userinfo to find
 * @param data data_server_t struct
 * @return userinfo_t*
 */
userinfo_t *get_user_info_by_name(char *name, data_server_t *data);

/**
 * @brief
 *
 * @param torm userinfo struct to remove
 * @param data data_server_t struct
 */
void remove_userinfo(userinfo_t *torm, data_server_t *data);

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

/**
 * @brief send message to user even if disconnected
 *
 * @param c client sending the message
 * @param user user receiving the message
 * @param message message to send
 * @param data data_server_t struct
 * @return 0 if message sent, 0 if not
 */
int send_message(struct client_s *c, struct userinfo_s *user
, char *message, data_server_t *data);

/**
 * @brief loads messages received while disconnected and send them to the user
 *
 * @param c client who received the message
 * @param data data_server_t struct
 * @return void
 */
void load_unread_messages(struct client_s *c, data_server_t *data);

/*                                  infos                                  */

/**
 * @brief sends infos of the current user to the user
 *
 * @param c client who asked for information
 * @param data data_server_t struct
 * @return 0 on succeed, 1 on fail
 */
int info_user(struct client_s *c, data_server_t *data);

/**
 * @brief sends infos of the team he is in to the user
 *
 * @param c client who asked for information
 * @param data data_server_t struct
 * @return 0 on succeed, 1 on fail
 */
int info_team(struct client_s *c, data_server_t *data);

/**
 * @brief sends infos of the channel he is in to the user
 *
 * @param c client who asked for information
 * @param data data_server_t struct
 * @return 0 on succeed, 1 on fail
 */
int info_channel(struct client_s *c, data_server_t *data);

/**
 * @brief sends infos of the thread he is in to the user
 *
 * @param c client who asked for information
 * @param data data_server_t struct
 * @return 0 on succeed, 1 on fail
 */
int info_thread(struct client_s *c, data_server_t *data);

/*                          team                                         */

/**
 * @brief Get the teams by id string
 *
 * @param uuid id to find
 * @param data the data struct of server
 * @return team_t*
 */
team_t *get_teams_by_id(char *uuid, data_server_t *data);

/**
 * @brief Get the teams by name string
 *
 * @param name
 * @param data
 * @return team_t*
 */
team_t *get_teams_by_name(char *name, data_server_t *data);

/**
 * @brief Create a add teams struct with name and dscription given in parameter
 *
 * @param name name of new team
 * @param desc description of new team
 * @param data the data struct of server
 * @return team_t*
 */
team_t *create_add_teams(char *name, char *desc, data_server_t *data);

/**
 * @brief free team list
 *
 * @param teams the list of team to free
 */
void free_teams(team_t *teams);

/**
 * @brief Subscribe to a team
 *
 * @param c Client who do command
 * @param args Array of command arguments
 * @param data Server data struct
 * @return int
 */
int subscribe(client_t *c, char **args, data_server_t *data);

/**
 * @brief Unsubscribe to a team
 *
 * @param c Client who do command
 * @param args Array of command arguments
 * @param data Server data struct
 * @return int
 */
int unsubscribe(client_t *c, char **args, data_server_t *data);

/**
 * @brief Get the subscribe by id string
 *
 * @param team team who find a user
 * @param uuid user uuid to find
 * @return userinfo_t*
 */
userinfo_t *get_subscribe_by_id(team_t *team, char *uuid);

/*                         create                                        */

/**
 * @brief sort create command compared to context of user
 *
 * @param arg Array of command arguments
 * @param client Client who do command
 * @param data Server data struct
 * @return int
 */
int sort_create(client_t *client, char **args, data_server_t *data);

/*                          login/logout                                 */

/**
 * @brief login client to link with an user
 *
 * @param client Client who do command
 * @param arg Array of command arguments
 * @param data Server data struct
 * @return int
 */
int login(client_t *client, char **arg, data_server_t *data);

/**
 * @brief Logout and disconnect client
 *
 * @param client Client who do command
 * @param arg,Array of command arguments
 * @param data Server data struct
 * @return int
 */
int logout(client_t *client, char **arg, data_server_t *data);

/*                          List                                         */

/**
 * @brief Send list of users
 *
 * @param c Client who do command
 * @param arg,Array of command arguments
 * @param data Server data struct
 * @return int
 */
int send_list_of_users(client_t *c, char **arg, data_server_t *data);

/**
 * @brief Send all message to client
 *
 * @param c Client who do command
 * @param arg,Array of command arguments
 * @param data Server data struct
 * @return int
 */
int cmd_messages(client_t *c, char **arg, data_server_t *data);

#endif /* !MY_TEAMS_H_ */
