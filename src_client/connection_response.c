/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** success_response
*/

#include "teams_client.h"

// log-in create user
void code_301(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_logged_in(data[0], data[1]);
    free_array(data);
}

// log-in
void code_302(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_logged_in(data[0], data[1]);
    free_array(data);
}

//log-out
void code_303(char *response)
{
    char **data = str_to_array(response, '\a');

    client_event_logged_out(data[0], data[1]);
    free_array(data);
}
