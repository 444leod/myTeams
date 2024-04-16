/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** reply
*/

#include "packet.h"
#include "macros.h"
#include "reply_code.h"
#include "logging_client.h"
#include <stdio.h>

/**
 * @brief Handle the reply type packets
 * @details Handle the reply type packets
 *
 * @param packet the packet
 */
void handle_reply_type_packet(packet_t *packet)
{
    reply_t *reply = get_reply_from_packet(packet);

    switch (packet->code) {
        case REPLY_CREATED:
            printf("Reply from %s on thread %s: \"%s\"\n",
                get_uuid_as_string(reply->creator_uuid),
                get_uuid_as_string(reply->thread_uuid), reply->body);
            client_event_thread_reply_received(
                get_uuid_as_string(reply->team_uuid),
                get_uuid_as_string(reply->thread_uuid),
                get_uuid_as_string(reply->creator_uuid), reply->body);
            break;
    }
}

/**
 * @brief Handle the reply packet
 * @details Handle the reply packet
 *
 * @param packet the packet
 */
void reply_packet_handler(packet_t *packet)
{
    switch (packet->code) {
        case REPLY_CREATED:
            handle_reply_type_packet(packet);
            break;
        default:
            printf("Unknown packet code\n");
            break;
    }
}
