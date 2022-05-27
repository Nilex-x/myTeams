/*
** EPITECH PROJECT, 2022
** sort_command.c
** File description:
** sort_command
*/

#include "my_teams.h"

int send_msg(client_t *c, char **arg, data_server_t *data)
{
    if (!c->user) {
        c->data_send = add_send(c->data_send, "503 - Not logged-in.\n");
        c->status = WRITE;
        return (0);
    }
    if (len_array(arg) != 3) {
        c->data_send = add_send(c->data_send, "502 - Missing arguments.\n");
        c->status = WRITE;
        return (0);
    }
    if (!get_user_info_by_uuid(arg[1], data)) {
        c->data_send = add_send(c->data_send, "521 - Wrong user uuid.\n");
        c->status = WRITE;
        return (0);
    }
    return send_message(c, get_user_info_by_uuid(arg[1], data), arg[2], data);
}

int sort_command(client_t *c, data_server_t *data, char *cmd)
{
    bool find = false;
    char **tab = str_to_word_array_separator(clear_str(cmd), '\a');
    char **commands = my_str_to_word_array("LOGIN LOGOUT CREATE SEND "
                                            "SUBSCRIBE UNSUBSCRIBE");
    int (*cmds[6])(client_t *, char **, data_server_t *) = { login, logout,
                            sort_create, send_msg, subscribe, unsubscribe};

    for (int i = 0; commands[i] && !find; i++) {
        if (strcmp(commands[i], tab[0]) == 0) {
            printf("Nice command: %s\n", commands[i]);
            cmds[i](c, tab, data);
            find = true;
        }
    }
    !find ? c->data_send = add_send(c->data_send, "500 command unkwon\n") : 0;
    free_array(commands);
    free_array(tab);
    return (0);
}
