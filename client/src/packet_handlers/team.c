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
#include "client_teams.h"
#include <stdio.h>

/**
 * @brief Log the team structure with the given function
 * @details Log the team structure with the given function
 *
 * @param f the function to use to log
 * @param team the team
 */
static void log_team(int (*f) (const char *, const char *, const char *),
    team_t *team)
{
    char *uuid = get_uuid_as_string(team->uuid);

    f(uuid, team->name, team->description);
}

/**
 * @brief Print the team structure following the given format
 * @details Print the team structure following the given format
 *
 * @param format the format
 * @param team the team
 */
static void print_team(char *format, team_t *team)
{
    char *uuid = get_uuid_as_string(team->uuid);

    printf(format, team->name, uuid, team->description);
}

/**
 * @brief Handle the team type packet (TEAM_LIST, TEAM_INFO, TEAM_CREATED)
 * @details Handle the team type packet (TEAM_LIST, TEAM_INFO, TEAM_CREATED)
 *
 * @param packet the packet
*/
static void handle_team_type_packet(packet_t *packet)
{
    team_t *team = get_team_from_packet(packet);

    switch (packet->code) {
        case TEAM_LIST:
            log_team(client_print_teams, team);
            print_team("Team list: %s (uuid: \"%s\") %s\n", team);
            break;
        case TEAM_INFO:
            log_team(client_print_team, team);
            print_team("Team info: %s (uuid: \"%s\") %s\n", team);
            break;
        case TEAM_CREATED:
            log_team(client_event_team_created, team);
            if (!packet->is_global)
                log_team(client_print_team_created, team);
            print_team("Team created: %s (uuid: \"%s\") %s\n", team);
            break;
    }
}

/**
 * @brief Handle the user type packet (USERS_LIST, EMPTY_USER_LIST)
 * @details Handle the user type packet (USERS_LIST, EMPTY_USER_LIST)
 *
 * @param packet the packet
*/
static void handle_user_type_packet(packet_t *packet)
{
    user_information_t *user = get_userinfo_from_packet(packet);
    char *uuid = get_uuid_as_string(user->user_uuid);

    switch (packet->code) {
        case USERS_LIST:
            client_print_users(uuid, user->username, user->is_logged);
            printf("Subscribed list: %s (uuid: \"%s\") %s\n", user->username,
                uuid, user->is_logged ? "logged" : "not logged");
            break;
        case EMPTY_USER_LIST:
            printf("No user subscribed to this team\n");
            break;
    }
}

/**
 * @brief Handle the subscription packet (TEAM_SUBSCRIBED, TEAM_UNSUBSCRIBED)
 * @details Handle the subscription packet (TEAM_SUBSCRIBED, TEAM_UNSUBSCRIBED)
 *
 * @param packet the packet
*/
static void handle_subscription_packet(packet_t *packet)
{
    team_t *team = get_team_from_packet(packet);

    switch (packet->code) {
        case TEAM_SUBSCRIBED:
            client_print_subscribed(get_uuid_as_string(team->uuid),
                get_uuid(false, NULL));
            printf("You subscribed to team %s\n", team->name);
            break;
        case TEAM_UNSUBSCRIBED:
            client_print_unsubscribed(get_uuid_as_string(team->uuid),
                get_uuid(false, NULL));
            printf("You unsubscribed from team %s\n", team->name);
            break;
    }
}

/**
 * @brief Handle the empty list (EMPTY_TEAM_LIST, NO_SUBSCRIBED_TEAMS)
 * @details Handle the empty list (EMPTY_TEAM_LIST, NO_SUBSCRIBED_TEAMS)
 *
 * @param code the code
*/
static void handle_empty_list(int code)
{
    switch (code) {
        case EMPTY_TEAM_LIST:
            printf("There is not any team.\n");
            break;
        case NO_SUBSCRIBED_TEAMS:
            printf("You are not subscribed to any team\n");
            break;
    }
}

/**
 * @brief Handle the errors (INEXISTANT_TEAM, ALREADY_EXISTS)
 * @details Handle the errors (INEXISTANT_TEAM, ALREADY_EXISTS)
 *
 * @param packet the packet
*/
static void handle_errors(packet_t *packet)
{
    switch (packet->code) {
        case INEXISTANT_TEAM:
            client_error_unknown_team(my_strdup(packet->packet_body));
            printf("Team does not exist\n");
            break;
        case ALREADY_EXISTS:
            printf("This team already exist!\n");
            client_error_already_exist();
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
    switch (packet->code) {
        case TEAM_SUBSCRIBED:
        case TEAM_UNSUBSCRIBED:
            handle_subscription_packet(packet);
            break;
        case EMPTY_TEAM_LIST:
        case NO_SUBSCRIBED_TEAMS:
            handle_empty_list(packet->code);
            break;
        case INEXISTANT_TEAM:
        case ALREADY_EXISTS:
            handle_errors(packet);
            break;
        default:
            printf("Team packet handler: Unknown packet code.\n");
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
        case USERS_LIST:
        case EMPTY_USER_LIST:
            handle_user_type_packet(packet);
            break;
        case TEAM_SUBSCRIBED:
        case TEAM_UNSUBSCRIBED:
        case EMPTY_TEAM_LIST:
        case INEXISTANT_TEAM:
        case NO_SUBSCRIBED_TEAMS:
        case ALREADY_EXISTS:
        default:
            handle_text_type_packet(packet);
            break;
    }
}
