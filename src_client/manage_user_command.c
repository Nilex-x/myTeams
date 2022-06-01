/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** manage_user_command
*/

#include "teams_client.h"

int check_command(char *cmd)
{
    int i = 0;
    const char *commands[14] = {"/help", "/login", "/logout"
    , "/users", "/user", "/send", "/messages", "/subscribe"
    , "/subscribed", "/unsubscribe", "/use", "/create"
    , "/list", "/info"};

    while (i < 14 && (strcmp(commands[i], cmd) != 0))
        i++;
    return i;
}

char *get_cmd(char *cmd)
{
    int i = 0;
    char *res = NULL;

    while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '\n')
        i++;
    if (!i)
        return NULL;
    res = malloc(sizeof(char) * i + 1);
    if (!res)
        return NULL;
    strncpy(res, cmd, i);
    res[i] = '\0';
    return res;
}

char *get_args(char *cmd, int cmd_len)
{
    char *rest = NULL;

    if (cmd[cmd_len] == '\0')
        return NULL;
    rest = malloc(sizeof(char) * (strlen(cmd) - cmd_len) + 1);
    rest = strncpy(rest, cmd + cmd_len, strlen(cmd) - cmd_len);
    rest[strlen(cmd) - cmd_len] = '\0';
    return rest;
}

int client_cmd(char *command, char *args, const char **cmds, char **to_send)
{
    int quotes_cmds[6] = {1, 4, 5, 6, 7, 9};
    int index = check_command(command);
    int quotes;

    if (index < 14) {
        asprintf(to_send, "%s%s", cmds[index], args);
        replace_char(*to_send);
        quotes = remove_dquotes(*to_send);
    }
    for (int i = 0; i < 6; i++) {
        if (index == quotes_cmds[i] && !quotes) {
            free(command);
            free(args);
            return -1;
        }
    }
    free(command);
    free(args);
    return index;
}

int user_command(info_t *info)
{
    char *to_send = NULL;
    char *command = get_cmd(info->write_buffer);;
    char *args = get_args(info->write_buffer, strlen(command));
    const char *commands[14] = {"HELP", "LOGIN", "LOGOUT", "USERS", "USER",
    "SEND", "MESSAGES", "SUBSCRIBE", "SUBSCRIBED", "UNSUBSCRIBE", "USE",
    "CREATE", "LIST", "INFO"};
    int index = client_cmd(command, args, commands, &to_send);

    if (!command)
        return -1;
    if (index == -1) {
        free(to_send);
        return -2;
    }
    if (index < 14) {
        info->write_buffer = strdup(to_send);
        free(to_send);
        return 1;
    }
    return 0;
}
