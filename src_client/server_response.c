/*
** EPITECH PROJECT, 2022
** myTeams
** File description:
** server_response
*/

#include "teams_client.h"

int return_code(char *response)
{
	void (*code_command[15])(void) =
    {&code_101, &code_102, &code_103, &code_104,
	&code_301, &code_302, &code_303, &code_304,
	&code_313, &code_315, &code_319, &code_321,
	&code_322, &code_323, &code_324};
	char *codes[15] =
	{"101", "102", "103", "104", "301", "302", "303", "304", "313",
	 "315", "319", "321", "322", "323", "324"};

	for (int i = 0; i < 15; i++) {
		if (strncmp(codes[i], response, 3) == 0) {
			code_command[i]();
			return 1;
		}
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
	void (*error_command[12])(void) =
    {&code_500, &code_501, &code_502, &code_503,
	&code_504, &code_511, &code_512, &code_513,
	&code_521, &code_522, &code_523, &code_524};
	const char *codes[12] =
	{"500", "501", "502", "503", "504", "511", "512"
	, "513", "521", "522", "523", "524"};

	for (int i = 0; i < 12; i++)
		if (strncmp(codes[i], response, 3) == 0) {
			error_command[i]();
			return 1;
		}
	return 0;
}

int server_response(char *response)
{
	if (response[0] == '5')
		return_errors(response);
	else if (!return_code(response))
		return_data(response);
	if (strncmp(response, "304", 3) == 0)
		return 1;
	free(response);
	return 0;
}
