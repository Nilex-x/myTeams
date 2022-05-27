/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** notif_response_01
*/

#include "teams_client.h"

void code_201(char *response)
{
	char **data = str_to_array(response, '\a');

	client_event_logged_in(data[0], data[1]);
	free_array(data);
}

void code_202(char *response)
{
	char **data = str_to_array(response, '\a');

	client_event_logged_out(data[0], data[1]);
	free_array(data);
}

void code_211(char *response)
{
	char **data = str_to_array(response, '\a');

	client_event_private_message_received(data[0], data[1]);
	free_array(data);
}

void code_212(char *response)
{

}
