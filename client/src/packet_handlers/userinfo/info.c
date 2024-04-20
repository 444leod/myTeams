/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** user infos
*/

#include "reply_code.h"
#include "packet.h"
#include "lib.h"
#include "logging_client.h"
#include "client_teams.h"
#include <stdio.h>

/**
 * @brief Display the user info
 * @details Display the user info
 *
 * @param user the user
 */
static void display_user_info(user_information_t *user)
{
    char *uuid = get_uuid_as_string(user->user_uuid);

    printf("User info (username: \"%s\", uuid: \"%s\", %d)\n",
        user->username, uuid, user->is_logged);
    client_print_user(uuid, user->username, user->is_logged);
}

/**
 * @brief Display the users list
 * @details Display the users list
 *
 * @param user the user
 */
static void display_users_list(user_information_t *user)
{
    char *uuid = get_uuid_as_string(user->user_uuid);

    printf("Users list: (username: \"%s\", uuid: \"%s\")\n",
        user->username, uuid);
    client_print_users(uuid, user->username, user->is_logged);
}

/**
 * @brief Handle the inexistant user packet
 * @details Handle the inexistant user packet
 *
 * @param packet the packet
 */
void handle_inexistant_user_packet(packet_t *packet)
{
    char *uuid = my_strdup(packet->packet_body);

    printf("User with uuid %s does not exist.\n", uuid);
    client_error_unknown_user(uuid);
}

/**
 * @brief Handle the userinfo packet for user informations
 * @details Handle the userinfo packet for user informations
 *
 * @param packet the packet
 */
void user_command_packet_handler(packet_t *packet)
{
    user_information_t *user = get_userinfo_from_packet(packet);

    switch (packet->code) {
        case USER_INFO:
            display_user_info(user);
            break;
        case USERS_LIST:
            display_users_list(user);
            break;
        case INEXISTANT_USER:
            handle_inexistant_user_packet(packet);
            break;
        default:
            break;
    }
}
