/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread
*/

#include "packet.h"
#include "macros.h"
#include <stdio.h>

/**
 * @brief Handle the thread packet
 * @details Handle the thread packet
 *
 * @param packet the packet
 */
void thread_packet_handler(packet_t *packet)
{
    UNUSED thread_t *thread = get_thread_from_packet(packet);

    switch (packet->code) {
        default:
            printf("Unknown packet code\n");
            break;
    }
}
