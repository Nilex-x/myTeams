/*
** EPITECH PROJECT, 2022
** manage_create_cmd.c
** File description:
** manage_create_cmd
*/

#include "my_teams.h"

int send_comment(client_t *client, char **args, data_server_t *data)
{
    return (0);
}

int sort_create(client_t *client, char **args, data_server_t *data)
{
    int len = len_array(args);

    if (!client->user->team && len == 3) {
        // create_teams
        printf("create Teams name: %s - description: %s\n", args[1], args[2]);
        return (0);
    }
    if (!client->user->channel && len == 3) {
        // create channel
        printf("create Channel name: %s - description: %s\n", args[1], args[2]);
        return (0);
    }
    if (!client->user->thread && len == 3) {
        //create thread
        printf("create Thread name: %s - description: %s\n", args[1], args[2]);
        return (0);
    }
    if (client->user->thread && len == 2)
        send_comment(client, args, data);
    return (0);
}