/*
** EPITECH PROJECT, 2022
** sort_command.c
** File description:
** sort_command
*/

#include "my_teams.h"

int login(struct client_s *c, char **arg, data_server_t *data)
{
    if (c->user) {
        c->data_send = add_send(c->data_send, "102 Already logged-in.\n");
        c->status = WRITE;
        return (0);
    }
    if (len_array(arg) != 2) {
        c->data_send = add_send(c->data_send, "502 Missing arguments.\n");
        c->status = WRITE;
        return (0);
    }
    if (!get_user_info_by_name(arg[1], data)) {
        c->user = init_user(arg[1], data, NULL);
        c->data_send = add_send(c->data_send, "301 User created.\n");
    } else {
        c->user = init_user(arg[1], data, get_user_info_by_name(arg[1], data));
        c->data_send = add_send(c->data_send, "302 User connected.\n");
    }
    c->status = WRITE;
    c->user->client = c;
    return (0);
}

int logout(struct client_s *c, char **arg, data_server_t *data)
{
    if (c->user) {
        c->data_send = add_send(c->data_send, "303 - User disconnected.\n");
        c->status = WRITE;
        server_event_user_logged_out(c->user->info->id);
        c->user = NULL;
    } else {
        c->data_send = add_send(c->data_send, "503 - Not logged-in.\n");
        c->status = WRITE;
    }
    return (0);
}

int send_msg(struct client_s *c, char **arg, data_server_t *data)
{
    if (!c->user) {
        printf("not logged\n");
        c->data_send = add_send(c->data_send, "503 - Not logged-in.\n");
        c->status = WRITE;
        return (0);
    }
    if (len_array(arg) != 3) {
        printf("missing args\n");
        c->data_send = add_send(c->data_send, "502 - Missing arguments.\n");
        c->status = WRITE;
        return (0);
    }
    if (!get_user_info_by_uuid(arg[1], data)) {
        printf("user info not found\n");
        c->data_send = add_send(c->data_send, "521 - Wrong user uuid.\n");
        c->status = WRITE;
        return (0);
    }
    printf("Allo je rentre !!\n");
    return send_message(c, get_user_info_by_uuid(arg[1], data), arg[2], data);
}

int sort_command(struct client_s *c, data_server_t *data, char *cmd)
{
    char **tab = my_str_to_word_array(clear_str(cmd));
    char **commands = my_str_to_word_array("LOGIN LOGOUT SEND");
    int (*cmds[3])(struct client_s *, char **, data_server_t *) = { \
                                                        login, logout, send_msg};

    for (int i = 0; commands[i]; i++) {
        if (strcmp(commands[i], tab[0]) == 0) {
            printf("Nice command: %s\n", commands[i]);
            cmds[i](c, tab, data);
            free_array(commands);
            free_array(tab);
            return (0);
        }
    }
    free_array(tab);
    free_array(commands);
    c->data_send = add_send(c->data_send, "500 command unkwon\n");
    c->status = WRITE;
    return (0);
}