/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** unknown_command
*/

#include "server_teams.h"
#include "clientllist.h"
#include "reply_code.h"
#include <sys/select.h>

/**
 * @brief Unknown command
 * @details Print the unknown command message
 *
 * @param client the client to print the unknown command message for
*/
void unknown_command(client_t client, UNUSED char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
    } else {
        client->current_code = SYNTAX_ERROR;
    }
    client->data_status = WRITING;
}
