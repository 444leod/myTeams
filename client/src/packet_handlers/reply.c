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
#include "lib.h"
#include "logging_client.h"
#include <stdio.h>

/**
 * @brief Handle the reply created
 * @details Handle the reply created
 *
 * @param packet the packet
 */
static void handle_reply_created(packet_t *packet)
{
    reply_t *reply = get_reply_from_packet(packet);
    char *creator_uuid = get_uuid_as_string(reply->creator_uuid);
    char *thread_uuid = get_uuid_as_string(reply->thread_uuid);
    char *team_uuid = get_uuid_as_string(reply->team_uuid);

    printf("Reply from %s on thread %s: \"%s\"\n", creator_uuid, thread_uuid,
        reply->body);
    client_event_thread_reply_received(team_uuid, thread_uuid,
        creator_uuid, reply->body);
    if (!packet->is_global)
        client_print_reply_created(thread_uuid, creator_uuid, reply->timestamp,
            reply->body);
}

/**
 * @brief Handle the reply list
 * @details Handle the reply list
 *
 * @param packet the packet
 */
static void handle_reply_list(packet_t *packet)
{
    reply_t *reply = get_reply_from_packet(packet);
    char *creator_uuid = get_uuid_as_string(reply->creator_uuid);
    char *thread_uuid = get_uuid_as_string(reply->thread_uuid);
    char *team_uuid = get_uuid_as_string(reply->team_uuid);

    printf("Reply list: %s\n", my_strdup(reply->body));
    client_thread_print_replies(thread_uuid, creator_uuid, reply->timestamp,
        reply->body);
}

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
            handle_reply_created(packet);
            break;
        case REPLY_LIST:
            handle_reply_list(packet);
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
        case REPLY_LIST:
            handle_reply_type_packet(packet);
            break;
        case EMPTY_REPLY_LIST:
            printf("Empty reply list.\n");
            break;
        default:
            printf("Reply packet handler: Unknown packet code.\n");
            break;
    }
}
