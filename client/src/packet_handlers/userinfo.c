/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** user
*/

#include "reply_code.h"
#include "packet.h"
#include "lib.h"
#include "logging_client.h"
#include "client_teams.h"
#include "packet_handler.h"
#include <stdio.h>

/**
 * @brief Handle the userinfo packet
 * @details Handle the userinfo packet
 *
 * @param packet the packet
 */
void userinfo_packet_handler(packet_t *packet)
{
    switch (packet->code) {
        case USER_LOGGED_IN:
        case USER_LOGGED_OUT:
        case USER_CREATED:
            log_command_packet_handler(packet);
            break;
        case USER_INFO:
        case USERS_LIST:
        case INEXISTANT_USER:
            user_command_packet_handler(packet);
            break;
        default:
            printf("Userinfo packet handler: Unknown packet code.\n");
            break;
    }
}
