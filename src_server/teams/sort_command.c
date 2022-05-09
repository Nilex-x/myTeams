/*
** EPITECH PROJECT, 2022
** sort_command.c
** File description:
** sort_command
*/

#include "my_teams.h"

int login(struct client_s *client, char **arg, data_server_t *data)
{
    if (client->user) {
        client->data_send = strdup("102 Already logged-in.\n");
        client->status = WRITE;
    } else if (len_array(arg) == 2) {
        // if create user here ←
        client->user = init_user(create_user_by_name(data->list, arg[1]), data);
        client->data_send = strdup("301 User created.\n");
        client->status = WRITE;
    } else {
        client->data_send = strdup("502 Command missing arguments.\n");
        client->status = WRITE;
    }
    return (0);
}

int logout(struct client_s *client, char **arg, data_server_t *data)
{
    if (client->user) {
        client->data_send = strdup("303 - User disconnected.\n");
        client->status = WRITE;
        client->user = NULL;
    } else {
        client->data_send = strdup("503 - Not logged-in.\n");
        client->status = WRITE;
    }
    return (0);
}

int sort_command(struct client_s *client, data_server_t *data, char *value)
{
    char **tab = my_str_to_word_array(clear_str(value));
    char **commands = my_str_to_word_array("LOGIN LOGOUT");
    int (*cmd[2])(struct client_s *, char **, data_server_t *) = { login, logout };

    for (int i = 0; commands[i]; i++) {
        if (strcmp(commands[i], tab[0]) == 0) {
            printf("Nice command: %s\n", commands[i]);
            cmd[i](client, tab, data);
            free_array(commands);
            free_array(tab);
            return (0);
        }
    }
    free_array(tab);
    free_array(commands);
    client->data_send = strdup("500 command unkwon\n");
    client->status = WRITE;
    return (0);
}