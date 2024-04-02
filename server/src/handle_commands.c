/*
** EPITECH PROJECT, 2024
** myFTP
** File description:
** handle_commands
*/

#include "clientllist.h"
#include <sys/select.h>
#include "commands.h"
#include "reply_code.h"
#include "lib.h"
#include "server_teams.h"
#include <unistd.h>
#include <stdio.h>

/**
 * @brief Execute the command
 * @details Execute the command of the client using the commands array
 *
 * @param command the command to execute with its arguments
 * @param client the client to execute the command for
 * @param readfds the readfds
 * @param server_info the server_info
*/
static void execute_command(char **command, client_t client,
    fd_set *readfds, server_info_t server_info)
{
    size_t i = 0;

    if (command[0] == NULL) {
        unknown_command(client, command, readfds, server_info);
        return;
    }
    for (; commands[i].command; i++) {
        if (strcmp(commands[i].command, command[0]) == 0) {
            commands[i].func(client, command, readfds, server_info);
            return;
        }
    }
    commands[i].func(client, command, readfds, server_info);
}

/**
 * @brief Handle the command of a client
 * @details Handle the command of a client
 * by parsing it and executing it
 *
 * @param client the client to handle the command of
 * @param readfds the readfds
 * @param server_info the server_info
*/
void handle_command(client_t client, fd_set *readfds,
    server_info_t server_info)
{
    char *command = my_strdup(client->command);
    char **args = str_to_word_array(command, " \t");

    while (args[0] && args[0][0] == '\0')
        ++args;
    execute_command(args, client, readfds, server_info);
    client->data_status = WRITING;
}
