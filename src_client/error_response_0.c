/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** error_response
*/

#include "teams_client.h"

void code_500(char *response)
{
    printf("500 -> Unknown command.\n");
}

void code_501(char *response)
{
    printf("501 -> Missing argument.\n");
}

// not logged in
void code_502(char *response)
{
    client_error_unauthorized();
}

void code_503(char *response)
{
    printf("503 -> Too long command.\n");
}
