/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** read_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include "lib.h"

packet_t *read_packet(int fd)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    memset(packet, 0, sizeof(packet_t));
    if (read(fd, packet, PACKET_SIZE) == -1) {
        my_free(packet);
        return NULL;
    }
    return packet;
}

char *get_string_from_packet(packet_t *packet)
{
    return my_strdup(packet->packet_body);
}

user_information_t *get_userinfo_from_packet(packet_t *packet)
{
    user_information_t *userinfo = my_malloc(USER_INFORMATION_SIZE);

    memcpy(userinfo, packet->packet_body, USER_INFORMATION_SIZE);
    return userinfo;
}
