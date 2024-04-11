/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** send_packet
*/

#include "packet.h"
#include "magic_number.h"
#include <unistd.h>

void send_packet(int fd, packet_t *packet)
{
    write_magic_number(fd);
    write(fd, packet, PACKET_SIZE);
}
