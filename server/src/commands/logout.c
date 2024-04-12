/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** logout
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "packet.h"

/**
 * @brief Check if the command is valid
 * @details Check if the command is valid
 *
 * @param client the client
 * @param command the command
 *
 * @return true if the command is valid
 * @return false if the command is not valid
 */
static bool is_command_valid(client_t client, char **command)
{
    if (tablen((void **)command) != 1) {
        client->packet = build_packet(SYNTAX_ERROR_IN_PARAMETERS, "");
        return false;
    }
    if (!client->user) {
        client->packet = build_packet(NOT_LOGGED_IN, "");
        return false;
    }
    return true;
}

void logout(client_t client, char **command)
{
    user_t user = client->user;

    if (!is_command_valid(client, command))
        return;
    client->packet =
        build_userinfo_packet(USER_LOGGED_OUT, user->username, user->uuid);
    user->status = STATUS_NOT_LOGGED_IN;
    client->user = NULL;
    server_event_user_logged_out(get_uuid_as_string(user->uuid));
}
