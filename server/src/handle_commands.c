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
*/
static void execute_command(UNUSED char **command, UNUSED client_t client)
{
    size_t i = 0;

    DEBUG_PRINT("Executing command: %s\n", command[0]);
    if (command[0] == NULL) {
        unknown_command(client, command);
        return;
    }
    for (; commands[i].command; i++) {
        if (strcmp(commands[i].command, command[0]) == 0) {
            commands[i].func(client, command);
            return;
        }
    }
    commands[i].func(client, command);
}

/**
 * @brief Handle the command of a client
 * @details Handle the command of a client
 * by parsing it and executing it
 *
 * @param client the client to handle the command of
*/
void handle_command(client_t client)
{
    char *command = my_strdup(client->command);
    char **args = str_to_word_array(command, " \t");

    DEBUG_PRINT("Handling command: %s\n", get_escaped_string(client->command));
    while (args[0] && args[0][0] == '\0')
        ++args;
    execute_command(args, client);
    client->data_status = WRITING;
}
