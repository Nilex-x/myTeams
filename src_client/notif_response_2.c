/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** notif_response_2
*/

#include "teams_client.h"

void code_221(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_team_created(data[0], data[1], data[2]);
    free_array(data);
}

void code_222(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_channel_created(data[0], data[1], data[2]);
    free_array(data);
}

void code_223(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_thread_created(data[0], data[1], atoi(data[2]), data[3], data[4]);
    free_array(data);
}
