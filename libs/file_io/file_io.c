/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** file_io
*/

#include "file_io.h"

line_t *create_line(char *line)
{
    line_t *new_line = malloc(sizeof(line_t));

    if (!new_line)
        return NULL;
    new_line->line = strdup(line);
    if (line[0] == 'U')
        new_line->type = USER;
    else if (line[0] == 'M')
        new_line->type = MESSAGE;
    else
        new_line->type = (line[0] == 'C') ? CREATE : SUBSCRIBED;
    new_line->next = NULL;
    return new_line;
}

void append_to_list(line_t **list, char *line)
{
    line_t *new_line = create_line(line);
    line_t *curr = *list;

    if (!new_line)
        return;
    if (!*list) {
        *list = new_line;
        return;
    }
    while (curr->next && curr->next->type <= new_line->type)
        curr = curr->next;
    new_line->next = curr->next;
    curr->next = new_line;
}

void file_rewrite(file_io_t *file_io)
{
    FILE *file = fopen(file_io->file_name, "w");
    line_t *curr = file_io->lines;

    if (!file)
        return;
    while (curr) {
        fprintf(file, "%s\n", curr->line);
        if (curr->next != NULL && curr->next->type > curr->type)
            fprintf(file, "\n");
        curr = curr->next;
    }
    fclose(file);
}

void file_io_destroy(file_io_t *file_io)
{
    line_t *curr = file_io->lines;
    line_t *tmp = NULL;

    while (curr) {
        tmp = curr;
        curr = curr->next;
        free(tmp->line);
        free(tmp);
    }
    free(file_io->file_name);
    free(file_io);
}

file_io_t *file_io_create(char *filepath)
{
    file_io_t *file_io = malloc(sizeof(file_io_t));
    FILE *file = fopen(filepath, "r");
    size_t len = 0;
    ssize_t read;
    char *line = NULL;

    if (!file_io)
        return (NULL);
    file_io->file_name = strdup(filepath);
    file_io->lines = NULL;
    if (!file)
        return file_io;
    while ((read = getline(&line, &len, file)) != -1) {
        line[strlen(line) - 1] = '\0';
        (strlen(line) < 4) ? 0 : append_to_list(&file_io->lines, line);
    }
    (line) ? free(line) : 0;
    fclose(file);
    return (file_io);
}
