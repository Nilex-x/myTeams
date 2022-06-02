/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** teams_client
*/

#ifndef TEAMS_CLIENT_H_
    #define TEAMS_CLIENT_H_
    #define _GNU_SOURCE

    #include <sys/select.h>

    #include "lib.h"
    #include "logging_client.h"

    #define WRITE 0
    #define READ 1
    #define LENGTH_COMMAND 512

typedef struct info_s {
    int socket;
    int read_write;
    buffer_t read_buffer;
    char *write_buffer;
    fd_set readfds;
    fd_set writefds;
    fd_set exceptfds;
    int quit;
} info_t;

/**
 * @brief Get the server response in the client's structure.
 * Check for Ctrl+C and wrong cmds.
 * 
 * @param info The client's struct. 
 */
void get_server_command(info_t *info);

/**
 * @brief Get the user command in the client's structure.
 * 
 * @param info The client's struct.
 */
void get_user_command(info_t *info);

/**
 * @brief Write the user command to the server.
 * 
 * @param info The client's struct.
 */
void write_command(info_t *info);

/**
 * @brief Check after select behavior.
 * Do we read or  write ?
 * @param info The client's struct.
 */
void manage_client(info_t *info);

/**
 * @brief Set read and write lists to ZERO.
 * 
 * @param info The client's struct.
 */
void clear_list(info_t *info);


/**
 * @brief Translate user commands to client commands.
 * 
 * @param info The client's struct.
 */
int user_command(info_t *info);

/**
 * @brief Remove double quotes from the str.
 * 
 * @param str 
 */
int remove_dquotes(char *str);

/**
 * @brief Replaces every spaces excluding those inside double-quotes by '\\a'.
 * 
 * @param str 
 */
void replace_char(char *str);

/**
 * @brief Split a str to multiple str separated by a given character.
 * 
 * @param str To split.
 * @param c Given char.
 */
char **str_to_array(char *str, char c);

/**
 * @brief Free the array returned by (str_to_char).
 * 
 * @param array The splited array.
 */
void free_array(char **array);


/**
 * @brief Interpret the code received by the server.
 * 
 * @param response The server response
 * @param info The client's struct.
 */
void server_response(char *response, info_t *info);


//Display help
void code_101(char *response);
//Already logged-in
void code_102(char *response);
//Already subscribed
void code_103(char *response);
//Not subscribed
void code_104(char *response);

//log-in create user
void code_301(char *response);
//log-in existing user
void code_302(char *response);
//log-out
void code_303(char *response);

//send msg
void code_313(char *response);
//succesfully subscribed
void code_315(char *response);
//succesfully unsubscribed
void code_318(char *response);
//use
void code_319(char *response);

//users
void code_311(char *response);
//user
void code_312(char *response);
//list messages
void code_314(char *response);
//subscribed "team"
void code_316(char *response);
//subscribed
void code_317(char *response);

//create team
void code_321(char *response);
//create channel
void code_322(char *response);
//create thread
void code_323(char *response);
//create reply
void code_324(char *response);

//list teams
void code_331(char *response);
//list channels
void code_332(char *response);
//list threads
void code_333(char *response);
//list replies
void code_334(char *response);

// info user
void code_341(char *response);
//info team
void code_342(char *response);
//info channel
void code_343(char *response);
//info thread
void code_344(char *response);

//log-in notif
void code_201(char *response);
//log-out notif
void code_202(char *response);
//message reveived
void code_211(char *response);
//thread reply received
void code_212(char *response);
//team created notif
void code_221(char *response);
//channel created notif
void code_222(char *response);
//thread created notif
void code_223(char *response);

//unknown command
void code_500(char *response);
//missing args
void code_501(char *response);
//unauthorized action
void code_502(char *response);
//too long command
void code_503(char *response);
//already logged-in
void code_511(char *response);
//already exists
void code_512(char *response);
//not subscribed
void code_513(char *response);
//wrong user uuid
void code_521(char *response);
//wrong team uuid
void code_522(char *response);
//wrong channel uuid
void code_523(char *response);
//wrong thread uuid
void code_524(char *response);

#endif /* !TEAMS_CLIENT_H_ */
