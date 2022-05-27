/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** user_data
*/

#include "teams_client.h"

// Users
void code_311(char *response)
{
	char **sep_usr = str_to_array(response, '\r');
	char **usr_info = NULL;

	for (int i = 0; sep_usr[i] != NULL; i++) {
		usr_info = str_to_array(sep_usr[i], '\a');
		client_print_users(usr_info[0], usr_info[1], usr_info[2]);
		free_array(usr_info);
	}
	free_array(sep_usr);
}

// User
void code_312(char *response)
{
	printf("312 -> Show user informations.\n");
}

void code_314(char *response)
{
	printf("314 -> List exchanged messages.\n");
}

// subscribed "team"
void code_316(char *response)
{
	char **sep_usr = str_to_array(response, '\r');
	char **usr_info = NULL;

	for (int i = 0; sep_usr[i] != NULL; i++) {
		usr_info = str_to_array(sep_usr[i], '\a');
		client_print_users(usr_info[0], usr_info[1], usr_info[2]);
		free_array(usr_info);
	}
	free_array(sep_usr);
}

// subscribed
void code_317(char *response)
{
	char **sep_team = str_to_array(response, '\r');
	char **team_info = NULL;

	for (int i = 0; sep_team[i] != NULL; i++) {
		team_info = str_to_array(sep_team[i], '\a');
		client_print_teams(team_info[0], team_info[1], team_info[2]);
		free_array(team_info);
	}
	free_array(sep_team);
}
