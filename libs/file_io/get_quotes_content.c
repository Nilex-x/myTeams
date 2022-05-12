/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** get_quotes_content
*/

#include "file_io.h"

char *get_quotes_content(char *str)
{
    int i = 0;
    char *new_str = strdup(str + 1);

    while(new_str[i] != '"' && new_str[i] != '\0')
        i++;
    new_str[i] = '\0';

    return new_str;
}