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
#include <stdio.h>

static void display_user_logged_in(user_information_t *user)
{
    char *uuid = get_uuid_as_string(user->user_uuid);

    client_event_logged_in(uuid, user->username);
    printf("User logged in (username: \"%s\", uuid: \"%s\")\n",
        user->username, uuid);
}

static void display_user_logged_out(user_information_t *user)
{
    char *uuid = get_uuid_as_string(user->user_uuid);

    client_event_logged_out(uuid, user->username);
    printf("User logged out (username: \"%s\", uuid: \"%s\")\n",
        user->username, uuid);
}

static void display_user_created(user_information_t *user)
{
    char *uuid = get_uuid_as_string(user->user_uuid);

    printf("User created (username: \"%s\", uuid: \"%s\")\n",
        user->username, uuid);
}

void userinfo_packet_handler(packet_t *packet)
{
    user_information_t *user = get_userinfo_from_packet(packet);

    switch (packet->code) {
        case USER_LOGGED_IN:
            display_user_logged_in(user);
            break;
        case USER_LOGGED_OUT:
            display_user_logged_out(user);
            break;
        case USER_CREATED:
            display_user_created(user);
            break;
        default:
            break;
    }
}
