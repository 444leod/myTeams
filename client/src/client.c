/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** teams
*/

#include "client_teams.h"
#include "lib.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <netdb.h>

/**
 * @brief callback for SIGINT
 * @details exit the program by calling my_exit to free all the memory
 *     and correctly close the socket and the clients sockets.
*/
static void handle_sigint(UNUSED int sig)
{
    my_exit(0);
}

/**
 * @brief Initialize the server_info struct
 * @details correctly initialize the server_info struct with the port and the
 *    path of the server
 *
 * @param argv the arguments of the program
 *
 * @return the server_info struct
*/
static server_info_t init_server_info(char *argv[])
{
    server_info_t server_info = my_malloc(sizeof(struct server_info_s));
    struct hostent *he = gethostbyname(argv[1]);
    struct in_addr **addr_list;

    addr_list = (struct in_addr **)he->h_addr_list;
    server_info->port = atoi(argv[2]);
    server_info->ip = inet_ntoa(*addr_list[0]);
    return server_info;
}

/**
 * @brief Wrapper for the select function
 * @details wrapper for the select function, if the select function failed
 *   the program exit, else the function updates the fd_sets each 100ms.
 *
 * @param readfds the read fd_set
 * @param writefds the write fd_set
 * @param max_sd the max_sd variable
*/
static void select_wrapper(fd_set *readfds, fd_set *writefds, int max_sd)
{
    struct timeval timeout = {0, 100};
    int activity = 0;

    activity = select(max_sd, readfds, writefds, NULL, &timeout);
    if (activity < 0)
        my_error("select wrapper failed");
}

/**
 * @brief Check the arguments of the program
 * @details check the arguments of the program and exit if they are invalid
 *
 * @param argc the number of arguments
 * @param argv the arguments of the program
*/
void send_message(int socketFd, char **message)
{
    char *str = *message;

    if (*message == NULL)
        return;
    if (str[strlen(str) - 1] == '\n' || str[strlen(str) - 1] == ' ')
        str[strlen(str) - 1] = '\0';
    str = supercat(2, str, "\r\n");
    send(socketFd, str, strlen(str), 0);
    need_to_read(1, 1);
    my_free(*message);
    *message = NULL;
}

/**
 * @brief Get the input of the user
 * @details get the input of the user and store it in the message variable
 *
 * @param message the message to store
*/
void get_input(char **message)
{
    char *buffer = my_malloc(sizeof(char) * 1024);
    size_t size = 0;
    size_t total_size = 0;

    size = read(0, buffer, 1);
    while (size == 1 && buffer[total_size] != '\n') {
        total_size += size;
        size = read(0, buffer + total_size, 1);
    }
    buffer[total_size] = '\0';
    if (size == 0) {
        printf("Exiting\n");
        my_exit(0);
    }
    *message = my_strdup(buffer);
    DEBUG_PRINT("Message len is: %ld\n", strlen(*message));
    process_input(message);
}

/**
 * @brief Trigger the action of the client
 * @details trigger the action of the client based on the readfds and writefds
 *
 * @param socketFd the socket file descriptor
 * @param readfds the readfds
 * @param writefds the writefds
 * @param message the message to send
*/
static void trigger_action(int socketFd, fd_set *readfds,
    fd_set *writefds, char **message)
{
    if (FD_ISSET(socketFd, readfds))
        parse_reply(socketFd);
    if (FD_ISSET(socketFd, writefds))
        send_message(socketFd, message);
    if (FD_ISSET(0, readfds))
        get_input(message);
}

/**
 * @brief Set the fds
 * @details set the fds of the readfds and writefds
 *  if the user NEED to read, will not read what he wrote,
 *  will wait for the packet.
 *
 * @param readfds the readfds
 * @param writefds the writefds
 * @param socketFd the socket file descriptor
 * @param message the message to send
*/
static void set_fds(fd_set *readfds, fd_set *writefds,
    int socketFd, char *message)
{
    FD_SET(socketFd, readfds);
    if (!need_to_read(0, 0)) {
        if (message)
            FD_SET(socketFd, writefds);
        else
            FD_SET(0, readfds);
    }
}

/**
 * @brief Main Teams loop
 * @details the main loop of the Teams server, it accepts new clients and
 *  updates the clients status, also it calls the loop_clients function
 *  to handle the clients commands
 *
 * @param socketFd the socket file descriptor
 * @param server_info the server_info struct
*/
void client_loop(int socketFd, UNUSED server_info_t server_info)
{
    fd_set readfds;
    fd_set writefds;
    char *message = NULL;

    need_to_read(1, 1);
    while (1) {
        FD_ZERO(&readfds);
        FD_ZERO(&writefds);
        set_fds(&readfds, &writefds, socketFd, message);
        select_wrapper(&readfds, &writefds, socketFd + 1);
        trigger_action(socketFd, &readfds, &writefds, &message);
    }
}

/**
 * @brief Main Client function
 * @details the main function of the Client program,
 *  it initializes the server_info struct and the socket,
 *  then it calls the client_loop function
 *  talk to the server
 *
 * @param argc the number of arguments
 * @param argv the arguments of the program
 *
 * @return 0 if the program exited correctly
*/
int client(int argc, char *argv[])
{
    int socketFd = -1;
    server_info_t server_info;

    errno = 0;
    DEBUG_PRINT("Teams client started\n");
    signal(2, handle_sigint);
    check_args(argc, argv);
    server_info = init_server_info(argv);
    socketFd = get_socket();
    DEBUG_PRINT("Socket fd: %d\n", socketFd);
    prepare_exit(socketFd);
    DEBUG_PRINT("Server info: %s:%d\n", server_info->ip, server_info->port);
    connect_to_server(socketFd, server_info->ip, server_info->port);
    client_loop(socketFd, server_info);
    close(socketFd);
    return 0;
}
