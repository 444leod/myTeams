/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** error
*/

#include "packet.h"
#include "macros.h"
#include "reply_code.h"
#include <stdio.h>

/**
 * @brief Handle the error packet
 * @details Handle the error packet
 *
 * @param packet the packet
 */
void error_packet_handler(UNUSED packet_t *packet)
{
    printf("Something went wrong with this packet handling.\n");
}
