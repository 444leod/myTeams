/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** unknown_command
*/

#include "commands.h"
#include "reply_code.h"

void unknown_command(client_t client, UNUSED char **command)
{
    if (!client->user) {
        client->current_code = NOT_LOGGED_IN;
    } else {
        client->current_code = SYNTAX_ERROR;
    }
}
