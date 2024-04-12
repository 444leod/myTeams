/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** unknown_command
*/

#include "commands.h"
#include "reply_code.h"
#include "packet.h"

void unknown_command(client_t client, UNUSED char **command)
{
    if (!client->user) {
        client->packet = build_packet(NOT_LOGGED_IN, "");
    } else {
        client->packet = build_packet(SYNTAX_ERROR, "");
    }
}
