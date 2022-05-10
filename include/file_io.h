/*
** EPITECH PROJECT, 2022
** myTeams_collaborate
** File description:
** file_io
*/

#ifndef FILE_IO_H_
    #define FILE_IO_H_

    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <regex.h>
    #include <uuid/uuid.h>
    #include "my_teams.h"

    typedef enum type_line {
        USER,
        MESSAGE,
        CREATE,
        SUBSCRIBED
    } type_line;

    typedef struct line_s {
        char *line;
        type_line type;
        struct line_s *next;
    } line_t;

    typedef struct file_io_s {
        char *file_name;
        line_t *lines;
    } file_io_t;

    /* Create a new file_io_t structure */
    file_io_t *file_io_create(char *filepath);

    /* Appends a line to the chained list of lines */
    void append_to_list(line_t **list, char *line);

    /* Free a file_io_t structure */
    void file_io_destroy(file_io_t *file_io);

    /* Rewrite the file */
    void file_rewrite(file_io_t *file_io);

    /* Gets user UUID with it's name */
    char *get_uid_by_name(file_io_t *file_io, char *name);

    /* Creates a user with it's name */
    struct userinfo_s *create_user_by_name(file_io_t *file_io, char *name);

    /* Gets all users from the save file */
    struct userinfo_s *get_all_user_infos(file_io_t *file_io);

    /* Gets a chained list of messages received and sent by the user */
    struct message_s *get_messages_by_user(file_io_t *file_io, char *id);

    /* Get a chained list of teams with it's channels and threads */
    struct team_s *get_teams(file_io_t *file_io);

    /* Get a chained list of channels with it's threads */
    struct channel_s *get_channels(file_io_t *file_io, char *team_id);

    /* Get a chained list of threads with it's messages */
    struct thread_s *get_threads(file_io_t *file_io, char *team_id, char *chan_id);

    /*                   SERVER                   */
    /* Get all the server data from the save file */
    struct data_server_s *get_server_data(char *file_name);

    /* TOOLS */

    /* Get quotes content from a string an alocate */
    char *get_quotes_content(char *str);

#endif /* !FILE_IO_H_ */
