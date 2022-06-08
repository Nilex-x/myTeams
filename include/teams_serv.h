/*
** EPITECH PROJECT, 2022
** my_teams
** File description:
** my_teams
*/

#ifndef TEAMS_SERV_H_
    #define TEAMS_SERV_H_
    #include "lib.h"
    #include "my_teams.h"
    #include "logging_server.h"
    #include <stdbool.h>
    #include <sys/select.h>
    #include <stddef.h>

    #define NB_LISTEN 32
    #define WRITE 0
    #define READ 1
    #define LENGTH_COMMAND 512

typedef struct data_send_s {
    char *data;
    struct data_send_s *next;
} data_send_t;

typedef struct client_s {
    int socket;
    int status;
    bool isQuit;
    data_send_t *data_send;
    buffer_t *buff_read;
    struct users_s *user;
    struct client_s *next;
    struct client_s *prev;
} client_t;

typedef struct server_s
{
    int port;
    int fd_server;
    int max_fd;
    fd_set wfds;
    fd_set efds;
    fd_set rfds;
    client_t *list_client;
    struct data_server_s *data;
}server_t;

/**
 * @brief Create a socket of server
 *
 * @param info Info struct server
 * @return int
 */
int create_socket(server_t *info);

/**
 * @brief Read client socket
 *
 * @param info Server struct information
 * @param client Client to read
 * @return int
 */
int read_client(server_t *info, client_t *client);

/**
 * @brief Get the client command string
 *
 * @param info Server struct information
 * @param client Client to get command
 * @return char *
 */
char *get_client_command(server_t *info, client_t *client);

/**
 * @brief Remove client to list given in parameter
 *
 * @param info Server struct information
 * @param client Client to remove
 */
void remove_client(server_t *info, int client);

/**
 * @brief Manage connection of client
 *
 * @param info Server struct information
 * @return int
 */
int handler_connection(server_t *info);

/**
 * @brief Initialization server struct
 *
 * @param info Server struct information
 */
void init_client(server_t *info);

/**
 * @brief Add client in list
 *
 * @param info Server struct information
 * @param client Client to add in list
 * @return client_t *
 */
client_t *add_client(server_t *info, int client);

/**
 * @brief Find specific client in list given in parameter
 *
 * @param info Server struct information
 * @param client Client socket to find
 * @return client_t*
 */
client_t *find_client(server_t *info, int client);

/**
 * @brief Free all occurence to list of client
 *
 * @param client Client List to free
 */
void free_client(client_t *client);

/**
 * @brief Accept connection to server
 *
 * @param info Server struct information
 */
void accept_connect(server_t *info);

/**
 * @brief Write to client socket
 *
 * @param info Server struct information
 * @param s_client Client socket to write
 */
void write_client(server_t *info, int s_client);

/**
 * @brief Close server
 *
 * @param info Server struct information
 */
void close_server(server_t *info);

/**
 * @brief Initializationof buffer
 *
 * @param node Client buffer to initialization
 */
void init_buff_client(client_t *node);

/**
 * @brief Mannage command of client
 *
 * @param info Server struct information
 * @param client Client who do command
 */
void handle_command(server_t *info, client_t *client);

/**
 * @brief Add data for send to client
 *
 * @param data_send List contain data
 * @param data Data to send
 * @return data_send_t *
 */
data_send_t *add_send(data_send_t *data_send, char *data);

/**
 * @brief Get the next data to send of client
 *
 * @param data_send List contain data
 * @return char *
 */
char *get_next_data_to_send(data_send_t **data_send);

/**
 * @brief Get the size data to send string
 *
 * @param data_send List contain data
 * @return size_t
 */
size_t get_size_data_to_send(data_send_t *data_send);

/**
 * @brief Free List data send
 *
 * @param send List to free
 */
void free_data_send(data_send_t *send);

#endif /* !TEAMS_SERV_H_ */
