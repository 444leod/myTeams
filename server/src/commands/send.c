/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** send
*/

#include "commands.h"
#include "reply_code.h"
#include "macros.h"

void my_send(client_t client, UNUSED char **command)
{
    add_packet_to_queue(&client->packet_queue,
        build_packet(COMMAND_NOT_IMPLEMENTED, ""));
}
