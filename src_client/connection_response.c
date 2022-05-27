/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** success_response
*/

#include "teams_client.h"

void code_301(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_logged_in(data[0], data[1]);
    free_array(data);
}

void code_302(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_logged_in(data[0], data[1]);
    free_array(data);
}

void code_303(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_logged_out(data[1], data[0]);
    free_array(data);
}
