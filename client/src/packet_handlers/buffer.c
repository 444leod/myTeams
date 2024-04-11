/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** buffer
*/

#include "packet.h"
#include "lib.h"
#include <stdio.h>

void buffer_packet_handler(packet_t *packet)
{
    printf("%s\n", my_strdup(packet->packet_body));
}
