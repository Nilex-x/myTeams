/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** test
*/

#include "file_io.h"

int main()
{
    data_server_t * data = get_server_data("test.save");

    append_to_list(&data->list->lines, "USER\a4cd09e4b-721e-4294-a947-cd5ad096398e\anicolas");
    append_to_list(&data->list->lines, "USER\a6280619c-2e78-4bc4-a316-44118c9da186\alucas");

    append_to_list(&data->list->lines, "MESSAGE\aR\a4cd09e4b-721e-4294-a947-cd5ad096398e\a6280619c-2e78-4bc4-a316-44118c9da186\aSalut");
    append_to_list(&data->list->lines, "MESSAGE\aR\a6280619c-2e78-4bc4-a316-44118c9da186\a4cd09e4b-721e-4294-a947-cd5ad096398e\aSalut");
    append_to_list(&data->list->lines, "MESSAGE\aN\a6280619c-2e78-4bc4-a316-44118c9da186\a4cd09e4b-721e-4294-a947-cd5ad096398e\aBite");

    append_to_list(&data->list->lines, "CREATE\aTEAM\a6250619c-2e78-4bc4-a316-44118c9da186\ateam 1\ateam 1 description");
    append_to_list(&data->list->lines, "CREATE\aTEAM\a6240619c-2e78-4bc4-a316-44118c9da186\ateam 2\ateam 2 description");

    append_to_list(&data->list->lines, "CREATE\aCHANNEL\a6250619c-2e78-4bc4-a316-44118c9da186\a6250619c-2e78-4bc4-a316-44118c9da185\ach1-team1\ach1-team1 description");
    append_to_list(&data->list->lines, "CREATE\aCHANNEL\a6250619c-2e78-4bc4-a316-44118c9da186\a6250619c-2e78-4bc4-a316-44118c9da184\ach2-team1\ach2-team1 description");
    append_to_list(&data->list->lines, "CREATE\aCHANNEL\a6240619c-2e78-4bc4-a316-44118c9da186\a6240619c-2e78-4bc4-a316-44118c9da185\ach1-team2\ach1-team2 description");
    append_to_list(&data->list->lines, "CREATE\aCHANNEL\a6240619c-2e78-4bc4-a316-44118c9da186\a6240619c-2e78-4bc4-a316-44118c9da184\ach2-team2\ach2-team2 description");

    append_to_list(&data->list->lines, "CREATE\aTHREAD\a6240619c-2e78-4bc4-a316-44118c9da186\a6240619c-2e78-4bc4-a316-44118c9da185\a6250619c-2e77-4bc4-a316-44118c9da184\a4cd09e4b-721e-4294-a947-cd5ad096398e\a1653656699\athread1-ch1-team2\ach1-team2 description");
    append_to_list(&data->list->lines, "CREATE\aTHREAD\a6240619c-2e78-4bc4-a316-44118c9da186\a6240619c-2e78-4bc4-a316-44118c9da184\a6250619c-2e76-4bc4-a316-44118c9da184\a4cd09e4b-721e-4294-a947-cd5ad096398e\a1653656720\athread2-ch2-team2\ach2-team2 description");

    append_to_list(&data->list->lines, "SUBSCRIBED\a6250619c-2e78-4bc4-a316-44118c9da186\a4cd09e4b-721e-4294-a947-cd5ad096398e");
    append_to_list(&data->list->lines, "SUBSCRIBED\a6240619c-2e78-4bc4-a316-44118c9da186\a4cd09e4b-721e-4294-a947-cd5ad096398e");
    append_to_list(&data->list->lines, "SUBSCRIBED\a6240619c-2e78-4bc4-a316-44118c9da186\a6280619c-2e78-4bc4-a316-44118c9da186");

    file_rewrite(data->list);

    printf("Users created :\n");
    for (userinfo_t *curr = data->userinfos; curr != NULL; curr = curr->next) {
        printf("\tname %s; id %s\n", curr->name, curr->id);
        printf("\tHis messages :\n");
        for (message_t *curr2 = curr->messages; curr2 != NULL; curr2 = curr2->next) {
            printf("\t\tfrom %s; to %s; message : [%s]\n", curr2->from, curr2->to, curr2->message);
        }
    }
    printf("\nTeams created :\n");
    for(team_t *curr = data->teams; curr != NULL; curr = curr->next) {
        printf("\tname %s; id %s; description %s\n", curr->name, curr->id, curr->description);
        printf("\tHis channels :\n");
        for (channel_t *curr2 = curr->channels; curr2 != NULL; curr2 = curr2->next) {
            printf("\t\tname %s; id %s; description %s\n", curr2->name, curr2->id, curr2->description);
            printf("\t\tHis threads :\n");
            for (thread_t *curr3 = curr2->threads; curr3 != NULL; curr3 = curr3->next) {
                printf("\t\t\ttitle %s; id %s; creator id %s; timestamp %ld, msg %s\n", curr3->title, curr3->id, curr3->creator_id, curr3->timestamp, curr3->body);
            }
            printf("\n");
        }
        printf("\n");
    }

    file_io_destroy(data->list);
    return 0;
}