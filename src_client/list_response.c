/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** list_response
*/

#include "teams_client.h"

// LIST teams
void code_331(char *response)
{
    char **team_info = str_to_array(response, '\a');

    client_print_teams(team_info[0], team_info[1], team_info[2]);
}

// LIST channels
void code_332(char *response)
{
    char **data = str_to_array(response, '\a');

    client_team_print_channels(data[0], data[1], data[2]);
}

// LIST threads
void code_333(char *response)
{
    char **data = str_to_array(response, '\a');

    client_channel_print_threads(data[0], data[1],
     atoi(data[2]), data[3], data[4]);
}

// LIST replies
void code_334(char *response)
{
    char **data = str_to_array(response, '\a');

    client_thread_print_replies(data[0], data[1],
     atoi(data[2]), data[3]);
}
