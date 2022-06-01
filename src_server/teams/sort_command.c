/*
** EPITECH PROJECT, 2022
** sort_command.c
** File description:
** sort_command
*/

#include "my_teams.h"

static int send_msg(client_t *c, char **arg, data_server_t *data)
{
    char *line = NULL;

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
        asprintf(&line, "521\a%s\n", arg[1]);
        c->data_send = add_send(c->data_send, line);
        free(line);
        c->status = WRITE;
        return (0);
    }
    return send_message(c, get_user_info_by_uuid(arg[1], data), arg[2], data);
}

static int info(struct client_s *c, char **arg, data_server_t *data)
{
    int context = (c->user->team != NULL) + (c->user->channel != NULL) +
    (c->user->thread != NULL);
    int (*f[4])(struct client_s *, data_server_t *) = {
        &info_user, &info_team, &info_channel, &info_thread
    };

    (void) arg;
    if (!c->user) {
        c->data_send = add_send(c->data_send, "502 - Not logged-in.\n");
        c->status = WRITE;
        return (0);
    }
    return f[context](c, data);
}

static int send_user_info(client_t *c, char **arg, data_server_t *data)
{
    userinfo_t *info = NULL;
    char *response = NULL;

    if (len_array(arg) != 2)
        c->data_send = add_send(c->data_send, "501\n");
    if (!c->user)
        c->data_send = add_send(c->data_send, "502\n");
    if (len_array(arg) != 2 && !c->user)
        return (0);
    info = get_user_info_by_uuid(arg[1], data);
    if (!info) {
        asprintf(&response, "521\a%s\n", arg[1]);
    } else {
        asprintf(&response, "312\a%s\a%s\a%d\n", info->id, info->name,
                            get_user_by_uuid(info->id, data) ? 1 : 0);
    }
    c->data_send = add_send(c->data_send, response);
    free(response);
    return (0);
}

static int help(client_t *c, char **arg, data_server_t *data)
{
    (void) arg;
    (void) data;
    c->data_send = add_send(c->data_send, "101\aHELP\aLOGIN\aLOGOUT\aUSERS"
                                        "\aUSER\aSEND\aMESSAGES\aSUBSCRIBE"
                                        "\aSUBSCRIBED\aUNSUBSCRIBE\aUSE"
                                        "\aCREATE\aLIST\aINFO\n");
    return (0);
}

int sort_command(client_t *c, data_server_t *data, char *cmd)
{
    bool find = false;
    char **tab = str_to_word_array_separator(clear_str(cmd), '\a');
    char **commands = my_str_to_word_array(COMMANDS);
    int (*cmds[12])(client_t *, char **, data_server_t *) = { login, logout,
                            sort_create, send_msg, subscribe, unsubscribe,
                            info, send_user_info, send_list_of_users, help,
                            cmd_messages, list};

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
