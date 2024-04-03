/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** type
*/

#include "server_teams.h"
#include "reply_code.h"
#include "clientllist.h"
#include <sys/select.h>

/**
 * @brief Type
 * @details Type
 *
 * @param client the client to type
*/
void type(client_t client, UNUSED char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    client->current_code = COMMAND_OK;
}
