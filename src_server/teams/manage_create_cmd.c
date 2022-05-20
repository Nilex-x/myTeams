/*
** EPITECH PROJECT, 2022
** manage_create_cmd.c
** File description:
** manage_create_cmd
*/

#include "my_teams.h"

int add_teams(client_t *client, char **args, data_server_t *data)
{
    team_t *new_team = create_add_teams(args[1], args[2], data);
    char *line = NULL;

    line = malloc(sizeof(char) * (strlen(new_team->name) +
                                strlen(new_team->description) +
                                strlen(new_team->id) + 8));
    if (!line)
        return (0);
    printf("create Teams name: %s - description: %s uuid: %s\n", new_team->name, new_team->description, new_team->id);
    client->user->team = new_team;
    sprintf(line, "321 %s %s %s\n", new_team->id, new_team->name,
                                new_team->description);
    client->data_send = add_send(client->data_send, line);
    free(line);
    return(0);
}

int send_comment(client_t *client, char **args, data_server_t *data)
{
    return (0);
}

int sort_create(client_t *client, char **args, data_server_t *data)
{
    int len = len_array(args);

    if (!client->user) {
        client->data_send = add_send(client->data_send, "503 Not logged-in\n");
        return (0);
    }
    if (!client->user->team && len == 3)
        return (add_teams(client, args, data));
    if (!client->user->channel && len == 3) {
        printf("create Channel name: %s - description: %s\n", args[1], args[2]);
        return (0);
    }
    if (!client->user->thread && len == 3) {
        printf("create Thread name: %s - description: %s\n", args[1], args[2]);
        return (0);
    }
    if (client->user->thread && len == 2)
        send_comment(client, args, data);
}