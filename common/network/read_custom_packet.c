/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** read_custom_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include "lib.h"


/**
 * @brief Get a user information from a packet
 * @details Get a user information from a packet
 *
 * @param packet the packet
 *
 * @return user_information_t* the user information
 */
user_information_t *get_userinfo_from_packet(packet_t *packet)
{
    user_information_t *userinfo = my_malloc(USER_INFORMATION_SIZE);

    memcpy(userinfo, packet->packet_body, USER_INFORMATION_SIZE);
    return userinfo;
}

/**
 * @brief Get a thread from a packet
 * @details Get a thread from a packet
 *
 * @param packet the packet
 *
 * @return thread_t* the thread
 */
thread_t *get_thread_from_packet(packet_t *packet)
{
    thread_t *thread = my_malloc(THREAD_SIZE);

    memcpy(thread, packet->packet_body, THREAD_SIZE);
    return thread;
}

/**
 * @brief Get a team from a packet
 * @details Get a team from a packet
 *
 * @param packet the packet
 *
 * @return team_t* the team
 */
team_t *get_team_from_packet(packet_t *packet)
{
    team_t *team = my_malloc(TEAM_SIZE);

    memcpy(team, packet->packet_body, TEAM_SIZE);
    return team;
}
