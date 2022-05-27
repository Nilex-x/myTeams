/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** list_response
*/

#include "teams_client.h"

// LIST teams
void code_331(char *response)
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

// LIST channels
void code_332(char *response)
{
    char **channels = str_to_array(response, '\r');
    char **channel_info = NULL;

    for (int i = 0; channels[i] != NULL; i++) {
        channel_info = str_to_array(channels[i], '\a');
        client_team_print_channels(channel_info[0], channel_info[1], channel_info[2]);
        free_array(channel_info);
    }
    free_array(channels);
}

// LIST threads
void code_333(char *response)
{
    char **threads = str_to_array(response, '\r');
    char **thread_info = NULL;

    for (int i = 0; threads[i] != NULL; i++) {
        thread_info = str_to_array(threads[i], '\a');
        // client_channel_print_threads(thread_info[0], thread_info[1], thread_info[2]);
        free_array(thread_info);
    }
    free_array(threads);
}

// LIST replies
void code_334(char *response)
{
    printf("334 -> list replies.\n");
}
