/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** channel
*/

#include "packet.h"
#include "macros.h"
#include <stdio.h>

/**
 * @brief Handle the channel packet
 * @details Handle the channel packet
 *
 * @param packet the packet
 */
void channel_packet_handler(packet_t *packet)
{
    UNUSED channel_t *channel = get_channel_from_packet(packet);

    switch (packet->code) {
        default:
            printf("Unknown packet code\n");
            break;
    }
}
