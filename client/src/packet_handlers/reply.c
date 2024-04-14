/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** reply
*/

#include "packet.h"
#include "macros.h"
#include <stdio.h>

/**
 * @brief Handle the reply packet
 * @details Handle the reply packet
 *
 * @param packet the packet
 */
void reply_packet_handler(packet_t *packet)
{
    UNUSED reply_t *reply = get_reply_from_packet(packet);

    switch (packet->code) {
        default:
            printf("Unknown packet code\n");
            break;
    }
}
