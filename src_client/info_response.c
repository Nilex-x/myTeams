/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** info_response
*/

#include "teams_client.h"

// info no context
void code_341(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_user(data[0], data[1], 1);
    free_array(data);
}

// info team defined
void code_342(char *response)
{
    printf("342 -> info channel.\n");
    char **data = str_to_array(response, '\a');

    client_print_team(data[0], data[1], data[2]);
    free_array(data);
}

//info channel defined
void code_343(char *response)
{
    printf("343 -> info threads.\n");
    char **data = str_to_array(response, '\a');

    client_print_channel(data[0], data[1], data[2]);
    free_array(data);
}

//info thread defined
void code_344(char *response)
{
    printf("344 -> info replies.\n");
    char **data = str_to_array(response, '\a');
    time_t tim_t;

    strptime(data[2], "%Y-%m-%d %H:%M:%S", tim_t);
    client_print_thread(data[0], data[1], tim_t, data[3], data[4]);
    free_array(data);
}
