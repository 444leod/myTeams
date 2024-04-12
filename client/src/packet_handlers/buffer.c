/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** buffer
*/

#include "packet.h"
#include "lib.h"
#include <stdio.h>

/**
 * @brief Handle the buffer packet
 * @details Handle the buffer packet
 *
 * @param packet the packet
 */
void buffer_packet_handler(packet_t *packet)
{
    printf("%s\n", my_strdup(packet->packet_body));
}
