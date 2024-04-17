/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** info
*/

#include "commands.h"
#include "reply_code.h"
#include "macros.h"

/**
 * @brief Check if the command is valid
 * @details Check if the command is valid
 *
 * @param client the client
 * @param command the command
 *
 * @return true if the command is valid
 * @return false if the command is not valid
 */
static bool is_command_valid(client_t client, char **command)
{
    if (tablen((void **)command) > 1) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(SYNTAX_ERROR_IN_PARAMETERS, ""));
        return false;
    }
    if (!client->user) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(NOT_LOGGED_IN, ""));
        return false;
    }
    return true;
}

/**
 * @brief Handle the user info
 * @details Handle the user info
 *
 * @param client the client
 */
static void handle_user_info(client_t client)
{
    packet_t *packet = build_userinfo_packet(USER_INFO, client->user->username,
        client->user->uuid, client->user->status);

    add_packet_to_queue(&client->packet_queue, packet);
}

/**
 * @brief Handle the team info
 * @details Handle the team info
 *
 * @param client the client
 */
static void handle_team_info(client_t client)
{
    packet_t *packet = build_team_packet(TEAM_INFO, client->team);

    add_packet_to_queue(&client->packet_queue, packet);
}

/**
 * @brief Handle the channel info
 * @details Handle the channel info
 *
 * @param client the client
 */
static void handle_channel_info(client_t client)
{
    packet_t *packet = build_channel_packet(CHANNEL_INFO, client->channel);

    add_packet_to_queue(&client->packet_queue, packet);
}

/**
 * @brief Handle the thread info
 * @details Handle the thread info
 *
 * @param client the client
 */
static void handle_thread_info(client_t client)
{
    packet_t *packet = build_thread_packet(THREAD_INFO, client->thread);

    add_packet_to_queue(&client->packet_queue, packet);
}

/**
 * @brief Handle the info command
 * @details Handle the info command
 *
 * @param client the client
 * @param command the command
 */
void info(client_t client, UNUSED char **command)
{
    enum CONTEXT context = get_current_context(client);

    if (!is_command_valid(client, command))
        return;
    switch (context) {
        case GLOBAL_CONTEXT:
            handle_user_info(client);
            break;
        case TEAM_CONTEXT:
            handle_team_info(client);
            break;
        case CHANNEL_CONTEXT:
            handle_channel_info(client);
            break;
        case THREAD_CONTEXT:
            handle_thread_info(client);
            break;
    }
}
