/*
** EPITECH PROJECT, 2022
** manage_buffer.c
** File description:
** manage_buffer
*/

#include "lib.h"

void init_buffer(buffer_t *buff, int length_command)
{
    for (int i = 0; i < length_command; i++)
       buff->buffer[i] = '\0';
    buff->rdonly = buff->buffer;
    buff->wronly = buff->buffer;
}

char *read_to_buffer(buffer_t *buff, char end_of_line, int length_max)
{
    int len = count_until_char(buff->rdonly, '\n');
    char *value = NULL;
    int i = 0;

    if (len == -1)
        return NULL;
    value = malloc(sizeof(char) * (len + 2));
    if (!value)
        return (NULL);
    for (; buff->rdonly[0] != end_of_line; buff->rdonly++, i++) {
        if ((buff->rdonly - buff->buffer) == length_max)
            buff->rdonly = buff->buffer;
        value[i] = buff->rdonly[0];
        value[i + 1] = '\0';
    }
    value[i] = '\n';
    value[i + 1] = '\0';
    buff->rdonly++;
    return (value);
}

void add_to_write(buffer_t *buff, char *value, int length_max)
{
    int len = strlen(value);
    printf("len: %d\n", len);

    if (!value)
        return;
    for (int i = 0; value[i]; i++, buff->wronly++) {
        if ((buff->wronly - buff->buffer) == length_max)
            buff->wronly = buff->buffer;
        buff->wronly[0] = value[i];
    }
}