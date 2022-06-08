/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** create_response
*/

#include "teams_client.h"
#include <stdlib.h>
#include <stdio.h>

// new team created
void code_321(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_team_created(data[0], data[1], data[2]);
    free_array(data);
}

// new channel created
void code_322(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_channel_created(data[0], data[1], data[2]);
    free_array(data);
}

// new thread created
void code_323(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_thread_created(data[0], data[1], atoi(data[2]),
                                data[3], data[4]);
    free_array(data);
}

void code_324(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_reply_created(data[0], data[1], atoi(data[2]),
                                        data[3]);
    free_array(data);
}
