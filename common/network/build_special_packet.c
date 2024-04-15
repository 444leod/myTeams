/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** build_custom_packet
*/

#include "packet.h"
#include "garbage_collector.h"
#include <unistd.h>
#include <string.h>

/**
 * @brief Build a packet with a code and a user information
 * @details Build a packet with the given code and user information, its type
 *       is set to USER_INFORMATION
 *
 * @param code the code
 * @param username the username
 * @param uuid the uuid
 * @param is_logged the is_logged
 *
 * @return the created packet
*/
packet_t *build_userinfo_packet(int code, username_t username, uuid_t uuid,
    bool is_logged)
{
    packet_t *packet = my_malloc(PACKET_SIZE);
    user_information_t *user = my_malloc(USER_INFORMATION_SIZE);

    packet->code = code;
    packet->packet_type = USER_INFORMATION;
    packet->is_global = false;
    memcpy(user->username, username, sizeof(username_t));
    memcpy(user->user_uuid, uuid, sizeof(uuid_t));
    user->is_logged = is_logged;
    memcpy(packet->packet_body, user, USER_INFORMATION_SIZE);
    return packet;
}

/**
 * @brief Build a packet with a code and a thread
 * @details Build a packet with the given code and thread, its type is set to
 *        THREAD
 *
 * @param code the code
 * @param thread the thread
 *
 * @return the created packet
*/
packet_t *build_thread_packet(int code, thread_t *thread)
{
    packet_t *packet = my_malloc(PACKET_SIZE);

    packet->code = code;
    packet->packet_type = THREAD;
    packet->is_global = false;
    memcpy(packet->packet_body, thread, THREAD_SIZE);
    return packet;
}

/**
 * @brief Build a packet with a code and a team informations
 * @details Build a packet with the given code and team, its type is set to
 *        TEAM
 *
 * @param code the code
 * @param title the title
 * @param description the description
 * @param creator_uuid the creator_uuid
 *
 * @return the created packet
*/
packet_t *build_team_packet(int code, title_t team_name,
    description_t description, uuid_t creator_uuid)
{
    packet_t *packet = my_malloc(PACKET_SIZE);
    team_t *team = my_malloc(TEAM_SIZE);

    packet->code = code;
    packet->packet_type = TEAM;
    packet->is_global = false;
    memcpy(team->team_name, team_name, sizeof(title_t));
    memcpy(team->description, description, sizeof(description_t));
    memcpy(team->creator_uuid, creator_uuid, sizeof(uuid_t));
    memcpy(packet->packet_body, team, TEAM_SIZE);
    return packet;
}

/**
 * @brief Build a reply packet with a code and reply informations
 * @details Build a packet with the given code and reply info,
 *  its type is set to REPLY
 *
 * @param code the code
 * @param body the body
 * @param creator_uuid the creator_uuid
 * @param thread_uuid the thread_uuid
 *
 * @return the created packet
*/
packet_t *build_reply_packet(int code, body_t body, uuid_t creator_uuid,
    uuid_t thread_uuid)
{
    packet_t *packet = my_malloc(PACKET_SIZE);
    reply_t *reply = my_malloc(REPLY_SIZE);

    packet->code = code;
    packet->packet_type = REPLY;
    packet->is_global = false;
    memcpy(reply->body, body, sizeof(body_t));
    memcpy(reply->creator_uuid, creator_uuid, sizeof(uuid_t));
    memcpy(reply->thread_uuid, thread_uuid, sizeof(uuid_t));
    memcpy(packet->packet_body, reply, REPLY_SIZE);
    return packet;
}

/**
 * @brief Build a packet with a code and channel informations
 * @details Build a packet with the given code, a channel name, a description
 * and a team uuid, its type is set to CHANNEL
 *
 * @param code the code
 * @param channel_name the channel_name
 * @param description the description
 * @param team_uuid the team_uuid
 *
 * @return the created packet
*/
packet_t *build_channel_packet(int code, title_t channel_name,
    description_t description, uuid_t team_uuid)
{
    packet_t *packet = my_malloc(PACKET_SIZE);
    channel_t *channel = my_malloc(CHANNEL_SIZE);

    packet->code = code;
    packet->packet_type = CHANNEL;
    packet->is_global = false;
    memcpy(channel->channel_name, channel_name, sizeof(title_t));
    memcpy(channel->description, description, sizeof(description_t));
    memcpy(channel->team_uuid, team_uuid, sizeof(uuid_t));
    memcpy(packet->packet_body, channel, CHANNEL_SIZE);
    return packet;
}
