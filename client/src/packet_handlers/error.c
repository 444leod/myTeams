/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** error
*/

#include "packet.h"
#include "macros.h"
#include "reply_code.h"
#include "logging_client.h"
#include "lib.h"
#include <stdio.h>

/**
 * @brief Handle the inexistant item packet
 * @details Handle the inexistant item packet
 *
 * @param packet the packet
 */
void handle_inexistant_item_packet(packet_t *packet)
{
    char *uuid = my_strdup(packet->packet_body);
    int (*func[])(const char *uuid) = {
        client_error_unknown_team, client_error_unknown_channel,
        client_error_unknown_thread, client_error_unknown_user };

    switch (packet->code) {
        case INEXISTANT_TEAM:
            func[0](uuid);
            break;
        case INEXISTANT_CHANNEL:
            func[1](uuid);
            break;
        case INEXISTANT_THREAD:
            func[2](uuid);
            break;
        case INEXISTANT_USER:
            func[3](uuid);
            break;
    }
    printf("This uuid doesnt match the request: %s\n", uuid);
}

/**
 * @brief Handle the error packet
 * @details Handle the error packet
 *
 * @param packet the packet
 */
void error_packet_handler(UNUSED packet_t *packet)
{
    switch (packet->code) {
        case INEXISTANT_TEAM:
        case INEXISTANT_CHANNEL:
        case INEXISTANT_THREAD:
        case INEXISTANT_USER:
            handle_inexistant_item_packet(packet);
            return;
        default:
            if (strlen(packet->packet_body) > 0) {
                printf("Error: %s\n", packet->packet_body);
                return;
            }
            break;
    }
    printf("Something went wrong with this packet handling.\n");
}
