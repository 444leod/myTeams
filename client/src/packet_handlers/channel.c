/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** channel
*/

#include "packet.h"
#include "reply_code.h"
#include "macros.h"
#include "logging_client.h"
#include <stdio.h>

/**
 * @brief Handle the channel type packets
 * @details Handle the channel type packets
 *
 * @param packet the packet
 */
void handle_channel_type_packet(packet_t *packet)
{
    channel_t *channel = get_channel_from_packet(packet);
    char *uuid = get_uuid_as_string(channel->uuid);

    switch (packet->code) {
        case CHANNEL_CREATED:
            printf("Channel created with uuid: %s\n", uuid);
            client_event_channel_created(uuid, channel->channel_name,
                channel->description);
            break;
    }
}

/**
 * @brief Handle the channel packet
 * @details Handle the channel packet
 *
 * @param packet the packet
 */
void channel_packet_handler(packet_t *packet)
{
    switch (packet->code) {
        case CHANNEL_CREATED:
            handle_channel_type_packet(packet);
            break;
        default:
            printf("Unknown packet code\n");
            break;
    }
}
