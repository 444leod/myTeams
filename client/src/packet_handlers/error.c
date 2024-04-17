/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** error
*/

#include "packet.h"
#include "macros.h"
#include "reply_code.h"
#include "logging_client.h"
#include "lib.h"
#include <stdio.h>

/**
 * @brief Handle the error packet
 * @details Handle the error packet
 *
 * @param packet the packet
 */
void error_packet_handler(UNUSED packet_t *packet)
{
    switch (packet->code) {
        default:
            if (strlen(packet->packet_body) > 0) {
                printf("Error: %s\n", packet->packet_body);
                return;
            }
            break;
    }
    printf("Error packet handler: Unknown packet code.\n");
}
