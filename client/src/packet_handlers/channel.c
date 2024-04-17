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
#include "lib.h"
#include <stdio.h>

/**
 * @brief Execute the given logging function using the channel structure
 * @details Execute the given logging function using the channel structure
 *
 * @param f the logging function
 * @param channel the channel
*/
static void log_channel(
    int (*f) (const char *, const char *, const char *), channel_t *channel)
{
    char *uuid = get_uuid_as_string(channel->uuid);

    f(uuid, channel->name, channel->description);
}

/**
 * @brief Print the channel structure following the given format
 * @details Print the channel structure following the given format
 *
 * @param format the format
 * @param channel the channel
*/
static void print_channel(char *format, channel_t *channel)
{
    char *uuid = get_uuid_as_string(channel->uuid);

    printf(format, channel->name, uuid, channel->description);
}

/**
 * @brief Handle the channel type packets
 * @details Handle the channel type packets
 *
 * @param packet the packet
 */
void handle_channel_type_packet(channel_t *channel, int code)
{
    switch (code) {
        case CHANNEL_CREATED:
            print_channel("Channel created: %s (uuid: \"%s\") %s\n", channel);
            log_channel(client_event_channel_created, channel);
            break;
        case CHANNEL_INFO:
            print_channel("Channel info: %s (uuid: \"%s\") %s\n", channel);
            log_channel(client_print_channel, channel);
            break;
        case CHANNEL_LIST:
            print_channel("Channel list: %s (uuid: \"%s\") %s\n", channel);
            log_channel(client_team_print_channels, channel);
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
    int code = packet->code;

    switch (code) {
        case CHANNEL_INFO:
        case CHANNEL_LIST:
        case CHANNEL_CREATED:
            handle_channel_type_packet(get_channel_from_packet(packet), code);
            break;
        case ALREADY_EXISTS:
            printf("This channel already exists\n");
            client_error_already_exist();
            break;
        default:
            printf("Unknown packet code\n");
            break;
    }
}
