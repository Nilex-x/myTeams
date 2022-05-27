/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** error_response
*/

#include "teams_client.h"

void code_500()
{
    printf("500 -> Unknown command.\n");
}

void code_501()
{
    printf("501 -> Missing double quotes.\n");
}

void code_502()
{
    printf("502 -> Command missing arguments.\n");
}

void code_503()
{
    printf("503 -> Not logged-in.\n");
}

void code_504()
{
    printf("504 -> Too long command.\n");
}
