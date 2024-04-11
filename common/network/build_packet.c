/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** build_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include <unistd.h>
#include <string.h>

packet_t *build_userinfo_packet(int code, username_t username, uuid_t uuid)
{
    packet_t *packet = my_malloc(PACKET_SIZE);
    user_information_t *user = my_malloc(USER_INFORMATION_SIZE);

    packet->code = code;
    packet->packet_type = USER_INFORMATION;
    memcpy(user->username, username, sizeof(username_t));
    memcpy(user->user_uuid, uuid, sizeof(uuid_t));
    memcpy(packet->packet_body, user, USER_INFORMATION_SIZE);
    return packet;
}

packet_t *build_packet(int code, char *buffer)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = NONE;
    memset(packet->packet_body, 0, sizeof(packet->packet_body));
    memcpy(packet->packet_body, buffer, strlen(buffer));
    return packet;
}
