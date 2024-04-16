/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** team
*/

#include "packet.h"
#include "macros.h"
#include "reply_code.h"
#include "logging_client.h"
#include "lib.h"
#include <stdio.h>

/**
 * @brief Handle the team type packet (TEAM_LIST, TEAM_INFO, TEAM_CREATED)
 * @details Handle the team type packet (TEAM_LIST, TEAM_INFO, TEAM_CREATED)
 *
 * @param packet the packet
*/
static void handle_team_type_packet(packet_t *packet)
{
    team_t *team = get_team_from_packet(packet);
    char *uuid = get_uuid_as_string(team->uuid);

    switch (packet->code) {
        case TEAM_LIST:
            client_print_teams(uuid, team->name, team->description);
            printf("Team list: %s (uuid: \"%s\") %s\n",
                team->name, uuid, team->description);
            break;
        case TEAM_INFO:
            client_print_team(uuid, team->name, team->description);
            printf("Team info: %s (uuid: \"%s\") %s\n",
                team->name, uuid, team->description);
            break;
        case TEAM_CREATED:
            client_print_team_created(uuid, team->name, team->description);
            printf("Team created: %s (uuid: \"%s\") %s\n",
                team->name, uuid, team->description);
            break;
    }
}

/**
 * @brief Handle the user type packet (USER_INFO, EMPTY_USER_LIST)
 * @details Handle the user type packet (USER_INFO, EMPTY_USER_LIST)
 *
 * @param packet the packet
*/
static void handle_user_type_packet(packet_t *packet)
{
    user_information_t *user = get_userinfo_from_packet(packet);
    char *uuid = get_uuid_as_string(user->user_uuid);

    switch (packet->code) {
        case USER_INFO:
            client_print_user(uuid, user->username, user->is_logged);
            printf("Subscribed list: %s (uuid: \"%s\") %s\n", user->username,
                uuid, user->is_logged ? "logged" : "not logged");
            break;
        case EMPTY_USER_LIST:
            printf("No user subscribed to this team\n");
            break;
    }
}

/**
 * @brief Handle the text type packet (TEAM_SUBSCRIBED, TEAM_UNSUBSCRIBED,
 *        EMPTY_TEAM_LIST, INEXISTANT_TEAM)
 * @details Handle the text type packet (TEAM_SUBSCRIBED, TEAM_UNSUBSCRIBED,
 *        EMPTY_TEAM_LIST, INEXISTANT_TEAM)
 *
 * @param packet the packet
*/
static void handle_text_type_packet(packet_t *packet)
{
    team_t *team = get_team_from_packet(packet);

    switch (packet->code) {
        case TEAM_SUBSCRIBED:
            printf("You subscribed to team %s\n", team->name);
            break;
        case TEAM_UNSUBSCRIBED:
            printf("You unsubscribed from team %s\n", team->name);
            break;
        case NO_SUBSCRIBED_TEAMS:
            printf("You are not subscribed to any team\n");
            break;
        case INEXISTANT_TEAM:
            printf("Team does not exist\n");
            break;
        default:
            printf("Unknown packet code (%d)\n", packet->code);
            break;
    }
}

/**
 * @brief Handle the team packet
 * @details Handle the team packet
 *
 * @param packet the packet
 */
void team_packet_handler(packet_t *packet)
{
    switch (packet->code) {
        case TEAM_LIST:
        case TEAM_INFO:
        case TEAM_CREATED:
            handle_team_type_packet(packet);
            break;
        case USER_INFO:
        case EMPTY_USER_LIST:
            handle_user_type_packet(packet);
            break;
        case TEAM_SUBSCRIBED:
        case TEAM_UNSUBSCRIBED:
        case EMPTY_TEAM_LIST:
        case INEXISTANT_TEAM:
        default:
            handle_text_type_packet(packet);
            break;
    }
}
