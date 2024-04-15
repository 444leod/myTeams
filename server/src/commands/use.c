/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** use
*/

#include "commands.h"
#include "reply_code.h"
#include "macros.h"

void use(client_t client, UNUSED char **command)
{
    add_packet_to_queue(&client->packet_queue,
        build_packet(COMMAND_NOT_IMPLEMENTED, ""));
}
