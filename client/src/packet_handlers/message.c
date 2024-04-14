/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** message
*/

#include "packet.h"
#include "macros.h"
#include "reply_code.h"
#include "logging_client.h"
#include "lib.h"
#include <stdio.h>

/**
 * @brief Handle the messages list
 * @details Handle the messages list
 *
 * @param packet the packet
 */
static void messages_list_handler(message_t *message)
{
    char *uuid = get_uuid_as_string(message->sender_uuid);

    printf("Messages list from %s: \"%s\"\n", uuid, message->body);
    client_private_message_print_messages(uuid, message->timestamp,
        my_strdup(message->body));
}

static void message_received_handler(message_t *message)
{
    char *uuid = get_uuid_as_string(message->sender_uuid);

    printf("Message received from %s: \"%s\"\n", uuid, message->body);
    client_event_private_message_received(uuid,
        my_strdup(message->body));
}

/**
 * @brief Handle the unknown user
 * @details Handle the unknown user
*/
static void unknown_user_handler(packet_t *packet)
{
    char *uuid = my_strdup(packet->packet_body);

    printf("Unknown user with uuid %s\n", uuid);
    client_error_unknown_user(uuid);
}

/**
 * @brief Handle the error packets
 * @details Handle the error packets
 *
 * @param packet the packet
 */
static void handle_error_packets(packet_t *packet)
{
    switch (packet->code) {
        case UNKNOWN_ERROR:
            printf("Unknown error\n");
            break;
        case INEXISTANT_USER:
            printf("Inexistant user\n");
            break;
        default:
            printf("Unknown packet code (%d)\n", packet->code);
            break;
    }
}

/**
 * @brief Handle the full packets
 * @details Handle the full packets
 *
 * @param packet the packet
 */
static void handle_full_packets(packet_t *packet)
{
    message_t *message = get_message_from_packet(packet);

    switch (packet->code) {
        case MESSAGE_SENT:
            printf("Message sent\n");
            break;
        case MESSAGE_RECEIVED:
            message_received_handler(message);
            break;
        case MESSAGES_LIST:
            messages_list_handler(message);
            break;
    }
}

/**
 * @brief Handle the message packet
 * @details Handle the message packet
 *
 * @param packet the packet
 */
void message_packet_handler(packet_t *packet)
{
    message_t *message = get_message_from_packet(packet);

    switch (packet->code) {
        case MESSAGE_SENT:
        case MESSAGE_RECEIVED:
        case MESSAGES_LIST:
            handle_full_packets(packet);
            break;
        case UNKNOWN_ERROR:
        case INEXISTANT_USER:
            handle_error_packets(packet);
            break;
        default:
            printf("Unknown packet code (%d)\n", packet->code);
            break;
    }
}
