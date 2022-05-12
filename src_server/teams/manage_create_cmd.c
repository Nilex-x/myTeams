/*
** EPITECH PROJECT, 2022
** manage_create_cmd.c
** File description:
** manage_create_cmd
*/

#include "my_teams.h"

int sort_create(char **args, client_t *client, data_server_t *data)
{
    int len = len_array(args);

    if (!client->user->team && len == 2) {
        // create_teams
        printf("create Teams name: %s - description: %s\n");
        return (0);
    }
    if (!client->user->channel && len == 2) {
        // create channel
        return (0);
    }
    if (!client->user->thread && len == 2) {
        //create thread
        return (0);
    }
    return (0);
}