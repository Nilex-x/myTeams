/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** error_response_1
*/

#include "teams_client.h"
#include <stdio.h>

void code_511(char *response)
{
    (void)response;

    printf("511 -> Already logged-in.\n");
}

void code_512(char *response)
{
    (void)response;

    client_error_already_exist();
    printf("512 -> Already exist.\n");
}

// not subscribed
void code_513(char *response)
{
    (void)response;

    client_error_unauthorized();
    printf("513 -> Not subscribed.\n");
}
