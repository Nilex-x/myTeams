/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** user_code
*/

#include "teams_client.h"
#include <stdio.h>

void code_313(char *response)
{
    printf("313 -> Message sent.\n");
}

// succesfully subscribed
void code_315(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_subscribed(data[0], data[1]);
    free_array(data);
}

// unsubscribe
void code_318(char *response)
{
    char **data = str_to_array(response, '\a');

    client_print_unsubscribed(data[0], data[1]);
    free_array(data);
}

void code_319(char *response)
{
    printf("319 -> New context specified.\n");
}
