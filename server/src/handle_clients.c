/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_clients
*/

#include "clientllist.h"
#include <sys/select.h>
#include "lib.h"
#include "server_teams.h"
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Send the correct reply code to the client
 * @details Send the correct reply code to the client
 * based on the current_code of the client
 * update the client status based on the next_commands
 *
 * @param client the client to send the reply code to
*/
static void send_buffer(client_t client)
{
    if (client->current_code) {
        reply_code(client);
        client->current_code = 0;
        if (client->next_commands == NULL) {
            client->data_status = READING;
            return;
        }
        if (strstr(client->next_commands, "\r\n") == NULL)
            client->data_status = READING;
        else
            client->data_status = PROCESSING;
    }
}

/**
 * @brief Read the buffer of a client
 *
 * @param client the client to read the buffer of
*/
static void read_buffer(client_t client)
{
    char buffer[1024] = {0};
    int valread = 0;

    valread = read(client->fd, buffer, 1024);
    if (valread == -1)
        my_error(supercat(2, "read failed: ", strerror(errno)));
    if (valread == 0) {
        remove_client(client->fd);
        return;
    }
    if (valread > 0) {
        if (client->next_commands)
            client->next_commands = supercat(2, client->next_commands, buffer);
        else
            client->next_commands = my_strdup(buffer);
        client->data_status = PROCESSING;
    }
}

/**
 * @brief Queue the next command of a client
 * @details Queue the next command of a client
 * if the client has a next command, queue it
 * if the client sent multiple commands, queue them into the next_commands
 *
 * @param client the client to queue the command of
*/
static void queue_command(client_t client)
{
    char *after_crlf = NULL;
    int i = 0;

    print_escaped(client->next_commands);
    if (client->next_commands) {
        after_crlf = strstr(client->next_commands, "\r\n");
        if (after_crlf) {
            i = after_crlf - client->next_commands;
            client->command = my_strndup(client->next_commands, i);
            client->next_commands = my_strdup(client->next_commands + i + 2);
        }
    }
}

/**
 * @brief Trigger the action of a client based on its status
 * @details Trigger the action of a client based on its status
 * if the client is ready to read, read the buffer
 * if the client is ready to process, queue the command
 * if the client has a command, handle the command
 * if the client is ready to write, send the buffer
 *
 * @param client the client to trigger the action of
 * @param readfds the readfds to check
 * @param writefds the writefds to check
 * @param server_info the server_info
*/
static void trigger_action(client_t client, fd_set *readfds,
    fd_set *writefds, UNUSED server_info_t server_info)
{
    if (FD_ISSET(client->fd, readfds))
        read_buffer(client);
    if (client->data_status == PROCESSING) {
        queue_command(client);
        if (client->command)
            printf("Command: %s\n", client->command);
        else
            client->data_status = READING;
        client->command = NULL;
    }
    if (FD_ISSET(client->fd, writefds))
        send_buffer(client);
}

/**
 * @brief Loop through the clients and trigger their actions
 * @details Loop through the clients and trigger their actions
 *
 * @param clients the clients to loop through
 * @param readfds the readfds to check
 * @param writefds the writefds to check
 * @param server_info the server_info
*/
void loop_clients(client_t *clients, fd_set *readfds,
    fd_set *writefds, server_info_t server_info)
{
    client_t tmp = *clients;
    int tempFd = 0;

    while (tmp) {
        tempFd = tmp->fd;
        trigger_action(tmp, readfds, writefds, server_info);
        if (tmp && tmp->fd == tempFd)
            tmp = tmp->next;
    }
}
