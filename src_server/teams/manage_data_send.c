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

    printf("Entering add-send\n");
    if (!new)
        return (NULL);
    new->data = strdup(data);
    new->next = NULL;
    printf("New data: %s\n", new->data);
    if (!data_send)
        return new;
    printf("First data is: %s\n", data_send->data);
    printf("Entering while\n");
    while (curr->next) {
        printf("\tIn while\n");
        curr = curr->next;
    }
    printf("Entering curr->next\n");
    curr->next = new;
    printf("Returning\n");
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
