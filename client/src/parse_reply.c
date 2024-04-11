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

const packet_handler_t packet_handlers[] = {
    {NONE, &buffer_packet_handler},
    {USER_INFORMATION, &userinfo_packet_handler},
    {-1, &error_packet_handler}
};

void display_message_by_type(int type, packet_t *packet)
{
    uint16_t i = 0;

    printf("%d - ", packet->code);
    for (i = 0; packet_handlers[i].type != -1; i++) {
        if (packet_handlers[i].type == type) {
            packet_handlers[i].func(packet);
            return;
        }
    }
    packet_handlers[i].func(packet);
}

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
