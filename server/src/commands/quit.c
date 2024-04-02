/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** quit
*/

#include "server_teams.h"
#include "clientllist.h"
#include "lib.h"
#include "reply_code.h"
#include <sys/select.h>

/**
 * @brief Quit the client
 * @details Quit the client
 *
 * @param client the client to quit
 */
void quit(client_t client, char **args,
    UNUSED fd_set *readfds, UNUSED server_info_t server_info)
{
    if (tablen((void **)args) != 1) {
        client->current_code = SYNTAX_ERROR;
        return;
    }
    client->current_code = SERVICE_CLOSING_CONTROL_CONNECTION;
}
