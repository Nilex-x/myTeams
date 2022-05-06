/*
** EPITECH PROJECT, 2022
** sort_command.c
** File description:
** sort_command
*/

#include "my_teams.h"

int login(client_t *client, char **arg)
{
    if (client->user) {
        client->data_send = strdup("511 Already logged-in\n");
        client->status = WRITE;
    } else {
        // if create user here ←

    }
    return (0);
}

int logout(client_t *client, char **arg)
{
    return (0);
}

void sort_command(client_t *client, data_server_t *data, char *value)
{
    char **tab = my_str_to_word_array(clear_str(value));
    char **commands = my_str_to_word_array("LOGIN LOGOUT");
    int (*cmd[2])(client_t *, char **) = { login, logout };

    for (int i = 0; commands[i]; i++) {
        if (strcmp(commands[i], tab[0]) == 0) {
            cmd[i](client, tab);
            free_array(tab);
            return;
        }
    }
    free_array(tab);
    free_array(commands);
    client->data_send = strdup("500 command unkwon\n");
    client->status = WRITE;
    return;
}