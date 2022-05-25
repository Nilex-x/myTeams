/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** str_to_array
*/

#include "teams_client.h"

void replace_char(char *str)
{
	int count = 0;

	for (int i = 0; i < (int) strlen(str); i++) {
		if (str[i] == '"')
			count++;
		if (str[i] == ' ' && !(count % 2))
			str[i] = '\a';
	}
}

char **str_to_array(char *str, char c)
{
	char **res = NULL;
	int nb_sep = 0;
	int word_count = 0;
	int world_len = 0;

	for (int i = 0; i < (int) strlen(str); i++)
		if (str[i] == c)
			nb_sep++;
	res = malloc(sizeof(char) * nb_sep + 2);
	for (int i = 0; i < (int) strlen(str); i++) {
		world_len++;
		if (str[i] == c) {
			res[word_count] = strndup(str + i, world_len);
			word_count++;
			world_len = 0;
		}
	}
	res[nb_sep + 1] = '\0';
	return res;
}

void free_array(char **array)
{
	int i = 0;

	while (array[i] != NULL)
		free(array[i]);
	free(array);
}