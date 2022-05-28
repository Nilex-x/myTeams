/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** server_response
*/

#include "teams_client.h"

int return_code(char *response)
{
    void (*code_command[15])(char *data) =
    {&code_101, &code_102, &code_103, &code_104,
    &code_301, &code_302, &code_303 ,&code_313,
    &code_315, &code_318, &code_319, &code_321, &code_322,
    &code_323, &code_324};
    char *codes[15] =
    {"101", "102", "103", "104", "301", "302", "303", "313",
    "315", "318", "319", "321", "322", "323", "324"};

    for (int i = 0; i < 15; i++) {
        if (strncmp(codes[i], response, 3) == 0) {
            code_command[i](response + 4);
            return 1;
        }
    }
    return 0;
}

int return_notif(char *response)
{
    void (*data_command[7])(char *data) =
    {&code_201, &code_202, &code_211, &code_212,
    &code_221, &code_222, &code_223};
    const char *codes[7] =
    {"201", "202", "211", "212", "221", "222", "223"};

    for (int i = 0; i < 7; i++)
        if (strncmp(codes[i], response, 3) == 0) {
            data_command[i](response + 4);
            return 1;
        }
    return 0;
}

int return_data(char *response)
{
    void (*data_command[13])(char *data) =
    {&code_311, &code_312, &code_314, &code_316,
    &code_317, &code_331, &code_332, &code_333,
    &code_334, &code_341, &code_342, &code_343,
    &code_344};
    const char *codes[13] =
    {"311", "312", "314", "316", "317", "331", "332", "333", "334"
    , "341", "342", "343", "344"};

    for (int i = 0; i < 13; i++)
        if (strncmp(codes[i], response, 3) == 0) {
            data_command[i](response + 4);
            return 1;
        }
    return 0;
}

int return_errors(char *response)
{
    void (*error_command[11])(char *data) =
    {&code_500, &code_501, &code_502, &code_503,
    &code_511, &code_512, &code_513, &code_521,
    &code_522, &code_523, &code_524};
    const char *codes[11] =
    {"500", "501", "502", "503", "511", "512"
    , "513", "521", "522", "523", "524"};

    for (int i = 0; i < 11; i++)
        if (strncmp(codes[i], response, 3) == 0) {
            error_command[i](response + 4);
            return 1;
        }
    return 0;
}

void server_response(char *response, info_t *info)
{
    if (response[0] == '5')
        return_errors(response);
    else if (response[0] == '2')
        return_notif(response);
    else if (!return_code(response))
        return_data(response);
    if (strncmp(response, "303", 3) == 0)
        info->quit = 1;
    free(response);
}
