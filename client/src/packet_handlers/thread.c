/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread
*/

#include "packet.h"
#include "macros.h"
#include "reply_code.h"
#include "logging_client.h"
#include <stdio.h>

/**
 * @brief Handle the thread type packets
 * @details Handle the thread type packets
 *
 * @param packet the packet
 */
void handle_thread_type_packet(packet_t *packet)
{
    thread_t *thread = get_thread_from_packet(packet);
    char *uuid = get_uuid_as_string(thread->uuid);

    switch (packet->code) {
        case THREAD_CREATED:
            printf("Thread created by %s: \"%s\"\n",
                get_uuid_as_string(thread->creator_uuid), thread->title);
            client_event_thread_created(uuid,
                get_uuid_as_string(thread->creator_uuid),
                thread->timestamp,
                thread->title,
                thread->body);
            break;
    }
}

/**
 * @brief Handle the thread packet
 * @details Handle the thread packet
 *
 * @param packet the packet
 */
void thread_packet_handler(packet_t *packet)
{
    switch (packet->code) {
        default:
            printf("Unknown packet code\n");
            break;
    }
}
