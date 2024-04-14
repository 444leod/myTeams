/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** read_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include "lib.h"

/**
 * @brief Read a packet from a file descriptor
 * @details Read a packet from a file descriptor
 *
 * @param fd the file descriptor
 *
 * @return packet_t* the packet
 */
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

/**
 * @brief Get a string from a packet
 * @details Get a string from a packet
 *
 * @param packet the packet
 *
 * @return char* the string
 */
char *get_string_from_packet(packet_t *packet)
{
    return my_strdup(packet->packet_body);
}
