/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** global_packet_send
*/

#include "packet.h"
#include "clientllist.h"
#include "garbage_collector.h"
#include <string.h>

/**
 * @brief Send a packet to all logged users
 * @details Send a packet to all logged users
 *
 * @param packet the packet
 * @param client the client
 */
void send_packet_to_logged_users(packet_t *packet, client_t client)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;
    packet_t *new_packet = my_malloc(sizeof(packet_t));

    memcpy(new_packet, packet, sizeof(packet_t));
    new_packet->is_global = true;
    while (tmp) {
        if (tmp == client) {
            tmp = tmp->next;
            continue;
        }
        if (tmp->user && tmp->user->status == STATUS_LOGGED_IN) {
            add_packet_to_queue(&tmp->packet_queue, new_packet);
        }
        tmp = tmp->next;
    }
}
