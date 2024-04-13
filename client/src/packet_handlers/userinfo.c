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
#include <stdio.h>

/**
 * @brief Display the user logged in
 * @details Display the user logged in and log it
 *
 * @param user the user
 */
static void display_user_logged_in(user_information_t *user, bool is_global)
{
    char *uuid = get_uuid_as_string(user->user_uuid);

    client_event_logged_in(uuid, user->username);
    printf("User logged in (username: \"%s\", uuid: \"%s\")\n",
        user->username, uuid);
    if (!is_global)
        is_logged(true);
}

/**
 * @brief Display the user logged out
 * @details Display the user logged out
 *
 * @param user the user
 */
static void display_user_logged_out(user_information_t *user, bool is_global)
{
    char *uuid = get_uuid_as_string(user->user_uuid);

    client_event_logged_out(uuid, user->username);
    printf("User logged out (username: \"%s\", uuid: \"%s\")\n",
        user->username, uuid);
    if (!is_global)
        my_exit(0);
}

/**
 * @brief Display the user created
 * @details Display the user created and log it
 *
 * @param user the user
 */
static void display_user_created(user_information_t *user, bool is_global)
{
    char *uuid = get_uuid_as_string(user->user_uuid);

    printf("User created (username: \"%s\", uuid: \"%s\")\n",
        user->username, uuid);
    if (!is_global)
        is_logged(true);
}

/**
 * @brief Handle the userinfo packet
 * @details Handle the userinfo packet
 *
 * @param packet the packet
 */
void userinfo_packet_handler(packet_t *packet)
{
    user_information_t *user = get_userinfo_from_packet(packet);

    switch (packet->code) {
        case USER_LOGGED_IN:
            display_user_logged_in(user, packet->is_global);
            break;
        case USER_LOGGED_OUT:
            display_user_logged_out(user, packet->is_global);
            break;
        case USER_CREATED:
            display_user_created(user, packet->is_global);
            break;
        default:
            break;
    }
}
