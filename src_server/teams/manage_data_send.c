/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** manage_data_send
*/

#include "my_teams.h"

data_send_t *add_send(data_send_t *data_send, char *data)
{
    data_send_t *new = malloc(sizeof(data_send_t));
    data_send_t *curr = data_send;

    // printf("add_send\n");
    new->data = strdup(data);
    new->next = NULL;
    if (data_send == NULL) {
        // printf("pute\n");
        return new;
    }
    // printf("found a data\n");
    // if (curr->next)
    //     printf("J'en ai un !");
    while (curr->next) {
        // printf("\t%s -> %p\n", curr->data, curr->next);
        curr = curr->next;
    }
    // printf("ici\n");
    curr->next = new;
    // printf("out of add_send\n");
    return data_send;
}

char *get_next_data_to_send(data_send_t **data_send)
{
    char *data = NULL;
    data_send_t *curr = *data_send;

    if (!*data_send)
        return NULL;
    data = (*data_send)->data;
    *data_send = (*data_send)->next;
    free(curr);
    return data;
}

size_t get_size_data_to_send(data_send_t *data_send)
{
    size_t size = 0;

    while (data_send) {
        size++;
        data_send = data_send->next;
    }
    return size;
}
