/*
** EPITECH PROJECT, 2022
** manage_create_cmd.c
** File description:
** manage_create_cmd
*/

#include "my_teams.h"

int send_notif_team(data_server_t *data, users_t *user, team_t *t)
{
    users_t *temp = data->users;
    char *text = NULL;

    if (!temp)
        return (0);
    asprintf(&text, "221\a%s\a%s\a%s\n", t->id, t->name, t->description);
    while (temp) {
        if (temp != user)
            temp->client->data_send = add_send(temp->client->data_send, text);
        temp = temp->next;
    }
    free(text);
    return (0);
}

int add_teams(client_t *client, char **args, data_server_t *data)
{
    team_t *new_team = get_teams_by_name(args[1], data);
    char *line = NULL;
    char *new_line = NULL;

    if (!new_team) {
        new_team = create_add_teams(args[1], args[2], data);
        asprintf(&new_line, "CREATE TEAM %s %s %s\n", new_team->id, new_team->name,
                                new_team->description);
        append_to_list(&data->list->lines, new_line);
        free(new_line);
    }
    printf("create Teams name: %s - description: %s uuid: %s\n", new_team->name, new_team->description, new_team->id);
    client->user->team = new_team;
    asprintf(&line, "321\a%s\a%s\a%s\n", new_team->id, new_team->name,
                                new_team->description);
    client->data_send = add_send(client->data_send, line);
    free(line);
    send_notif_team(data, client->user, new_team);
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