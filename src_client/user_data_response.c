/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** user_data
*/

#include "teams_client.h"

// Users
void code_311(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_user(data[0], data[1], atoi(data[2]));
}

// User user "uuid"
void code_312(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_user(data[0], data[1], atoi(data[2]));
}

// messages
void code_314(char *response)
{
    char **data = str_to_array(response, '\a');

    client_private_message_print_messages(data[0], atoi(data[1]), data[2]);
}

// subscribed "team"
void code_316(char *response)
{
    char **usr_info = str_to_array(response, '\a');

    client_print_users(usr_info[0], usr_info[1], atoi(usr_info[2]));
}

// subscribed
void code_317(char *response)
{
    char **team_info = str_to_array(response, '\a');

    client_print_teams(team_info[0], team_info[1], team_info[2]);
}
