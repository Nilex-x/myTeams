/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** str_to_array
*/

#include "teams_client.h"

void remove_dquotes(char *str)
{
    int nb_quotes = 0;
    int i = 0;

    while ((i + nb_quotes) < strlen(str)) {
        if (str[i + nb_quotes] == '"')
            nb_quotes++;
        else {
            str[i] = str[i + nb_quotes];
            i++;
        }
    }
    str[i] = '\0';
}

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
    int word_len = 0;

    for (int i = 0; i < (int) strlen(str); i++)
        if (str[i] == c)
            nb_sep++;
    res = malloc(sizeof(char*) * (nb_sep + 2));
    for (int i = 0; i < (int) strlen(str); i++) {
        if (str[i] == c || str[i] == '\n') {
            res[word_count] = strndup(str + (i - word_len), word_len);
            word_count++;
            word_len = 0;
        }
        word_len++;
    }
    res[nb_sep + 1] = '\0';
    return res;
}

void free_array(char **array)
{
    int i = 0;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}
