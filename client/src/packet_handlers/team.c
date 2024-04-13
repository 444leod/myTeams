/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** team
*/

#include "packet.h"
#include "macros.h"
#include <stdio.h>

/**
 * @brief Handle the team packet
 * @details Handle the team packet
 *
 * @param packet the packet
 */
void team_packet_handler(packet_t *packet)
{
    UNUSED team_t *team = get_team_from_packet(packet);

    switch (packet->code) {
        default:
            printf("Unknown packet code\n");
            break;
    }
}
