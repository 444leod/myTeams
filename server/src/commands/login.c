/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** login
*/

#include "commands.h"
#include "reply_code.h"

void login(client_t client, char **command)
{
    user_t user;

    if (tablen((void **)command) != 2) {
        client->current_code = SYNTAX_ERROR_IN_PARAMETERS;
        return;
    }
    if (client->user) {
        client->current_code = ALREADY_LOGGED_IN;
        return;
    }
    user = get_user_by_username(command[1]);
    if (!user) {
        add_user_by_username(command[1]);
        user = get_user_by_username(command[1]);
        client->current_code = USER_CREATED;
    } else
        client->current_code = USER_LOGGED_IN;
    client->user = user;
    user->status = STATUS_LOGGED_IN;
}
