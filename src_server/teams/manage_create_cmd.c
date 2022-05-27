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

int add_teams(client_t *c, char **args, data_server_t *data)
{
    team_t *new_team = get_teams_by_name(args[1], data);
    char *line = NULL;
    char *new_line = NULL;

    printf("name: [%s] desc: [%s]\n", args[1], args[2]);
    if (!new_team) {
        new_team = create_add_teams(args[1], args[2], data);
        asprintf(&new_line, "CREATE\aTEAM\a%s\a%s\a%s\n", new_team->id,
                            new_team->name, new_team->description);
        append_to_list(&data->list->lines, new_line);
        free(new_line);
    }
    c->user->team = new_team;
    asprintf(&line, "321\a%s\a%s\a%s\n", new_team->id, new_team->name,
                                new_team->description);
    c->data_send = add_send(c->data_send, line);
    free(line);
    server_event_team_created(new_team->id, new_team->name, c->user->info->id);
    send_notif_team(data, c->user, new_team);
    return (0);
}

int send_comment(client_t *client, char **args, data_server_t *data)
{
    return (0);
}

int sort_create(client_t *c, char **args, data_server_t *data)
{
    int len = len_array(args);

    if (!c->user)
        c->data_send = add_send(c->data_send, "503 Not logged-in\n");
    if (c->user && !c->user->team && len == 3)
        return (add_teams(c, args, data));
    if (c->user && !c->user->channel && len == 3)
        return (printf("create Channel %s desc: %s\n", args[1], args[2]));
    if (c->user && !c->user->thread && len == 3)
        return (printf("create Thread %s desc: %s\n", args[1], args[2]));
    if (c->user && c->user->thread && len == 2)
        return (send_comment(c, args, data));
    c->data_send = add_send(c->data_send, "502 Command missing arguments.\n");
    return (0);
}
