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
	const char *commands[15] = {"/help", "/login", "/logout"
	, "/users", "/user", "/send", "/messages", "/subscribe"
	, "/subscribed", "/unsubscribe", "/use", "/create"
	, "/list", "/info", "/quit"};

	while (i < 15 && (strcmp(commands[i], cmd) != 0))
		i++;
	return i;
}

char *get_cmd(char *cmd)
{
	int i = 0;
	char *res = NULL;

	while (cmd[i] != '\0' && cmd[i] != ' ')
		i++;
	if (!i)
		return NULL;
	res = malloc(sizeof(char) * i + 1);
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

int client_cmd(char *command, char *args, const char** cmds, char **to_send)
{
	int index = check_command(command);

	if (index < 15) {
		*to_send = malloc(sizeof(char) * (strlen(cmds[index])
		 + strlen(args) + 2));
		sprintf(*to_send, "%s%s", cmds[index], args);
	}
	return index;
}

int user_command(info_t *info)
{
	char *to_send = NULL;
	char *command = NULL;
	char *args = NULL;
	int index;
	const char *commands[15] = {"HELP", "LOGIN", "LOGOUT"
	, "USERS", "USER", "SEND", "MESSAGES", "SUBSCRIBE"
	, "subscribed", "UNSUBSCRIBE", "USE", "CREATE"
	, "LIST", "INFO", "QUIT"};

	command = get_cmd(info->write_buffer);
	if (!command)
		return -1;
	args = get_args(info->write_buffer, strlen(command));
	index = client_cmd(command, args, commands, &to_send);
	if (index < 15) {
		info->write_buffer = realloc(info->write_buffer, strlen(to_send) + 1);
		info->write_buffer = strdup(to_send);
		free(to_send);
	}
	printf("TO SEND: %s\n", info->write_buffer);
	return 1;
}
