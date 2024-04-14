/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** parse_reply
*/

#include "client_teams.h"
#include "lib.h"
#include "reply_code.h"
#include "magic_number.h"
#include "logging_client.h"
#include "packet.h"
#include "packet_handler.h"
#include <unistd.h>

/**
 * @brief The packet handlers
 * @details The packet handlers, each packet has a type and a handler
*/
const packet_handler_t packet_handlers[] = {
    {NONE, &buffer_packet_handler},
    {USER_INFORMATION, &userinfo_packet_handler},
    {THREAD, &thread_packet_handler},
    {TEAM, &team_packet_handler},
    {REPLY, &reply_packet_handler},
    {-1, &error_packet_handler}
};

/**
 * @brief Display the message by type
 * @details Display the message by type, using the correct handler, if the
 *  packet sent is correct and has a type.
 *
 * @param type the type of the packet
 * @param packet the packet
*/
void display_message_by_type(int type, packet_t *packet)
{
    uint16_t i = 0;

    printf("%d - ", packet->code);
    need_to_read(1, 0);
    for (i = 0; packet_handlers[i].type != -1; i++) {
        if (packet_handlers[i].type == type) {
            packet_handlers[i].func(packet);
            return;
        }
    }
    packet_handlers[i].func(packet);
}

/**
 * @brief Parse the reply from the server
 * @details Parse the reply from the server, read the packet and display
 * the message
 *
 * @param socketFd the socket file descriptor
*/
void parse_reply(int socketFd)
{
    packet_t *packet = NULL;

    if (!is_magic_number_valid(socketFd)) {
        printf("Server closed.\n");
        my_exit(0);
    }
    packet = read_packet(socketFd);
    if (packet == NULL) {
        printf("Something went wrong with server packet.\n");
        return;
    }
    display_message_by_type(packet->packet_type, packet);
}
