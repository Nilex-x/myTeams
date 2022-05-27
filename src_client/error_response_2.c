/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** error_response_2
*/

#include "teams_client.h"

// wrong user uuid
void code_521(char *response)
{
    char **data = str_to_array(response, '\a');

    client_error_unknown_user(data[0]);
    free_array(data);
}

// wrong team uuid
void code_522(char *response)
{
    char **data = str_to_array(response, '\a');

    client_error_unknown_team(data[0]);
    free_array(data);
}

// wrong channel uuid
void code_523(char *response)
{
    char **data = str_to_array(response, '\a');

    client_error_unknown_channel(data[0]);
    free_array(data);
}

// wrong thread uuid
void code_524(char *response)
{
    char **data = str_to_array(response, '\a');

    client_error_unknown_thread(data[0]);
    free_array(data);
}
