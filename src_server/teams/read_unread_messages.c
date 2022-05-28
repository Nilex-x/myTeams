/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** read_unread_messages
*/

#include "my_teams.h"

line_t *find_unread_message(file_io_t *fio, char *from, char *to, char *msg)
{
    line_t *curr = fio->lines;
    char *line = malloc(strlen(msg) + 87);

    sprintf(line, "MESSAGE N %s %s \"%s\"", from, to, msg);
    while (curr) {
        if (strcmp(curr->line, line) == 0) {
            free(line);
            return curr;
        }
        curr = curr->next;
    }
    free(line);
    return NULL;
}

void load_unread_messages(struct client_s *c, data_server_t *data)
{
    char *line = NULL;
    line_t *cur_msg = NULL;
    char *to = c->user->info->id;

    if (!c || !data)
        return;
    for (message_t *curr = c->user->info->messages; curr; curr = curr->next)
        if (!curr->isRead && strncmp(curr->to, to, 36) == 0) {
            cur_msg = find_unread_message(data->list, curr->from, 
            to, curr->message);
            (cur_msg) ? (cur_msg->line)[8] = 'R' : 0;
            line = malloc(82 + strlen(curr->message));
            sprintf(line, "201\a%s\a%s\a%s\n", curr->from, to, curr->message);
            c->data_send = add_send(c->data_send, line);
            free(line);
            curr->isRead = true;
        }
}
