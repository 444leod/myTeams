/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** reply_code
*/

#include "fcntl.h"
#include <stdio.h>
#include <stdbool.h>
#include "reply_code.h"
#include "clientllist.h"
#include "lib.h"
#include "garbage_collector.h"

/**
 * @brief The custom messages list
 * @details The list of custom messages that the server can send to the client
 * it uses the client buffer to send the message
*/
const int custom_messages_list[] = {
    HELP_MESSAGE,
    USER_CREATED,
    USER_LOGGED_IN,
    USER_LOGGED_OUT,
    USERS_LIST,
    USER_INFO,
    TEAM_LIST,
    CHANNEL_LIST,
    THREAD_LIST,
    REPLY_LIST,
    CURRENT_USER_INFO,
    TEAM_INFO,
    CHANNEL_INFO,
    THREAD_INFO,
    INEXISTANT_USER,
    INEXISTANT_TEAM,
    INEXISTANT_CHANNEL,
    INEXISTANT_THREAD,
    -1
};

/**
 * @brief The server messages
 * @details The messages that the server can send to the client based on the
 * current code
*/
const server_message_t serverMessages[] = {
    {COMMAND_OK, "Command okay."},

    {GLOBAL_CONTEXT_SET, "Global context set."},
    {TEAM_CONTEXT_SET, "Team context set."},
    {CHANNEL_CONTEXT_SET, "Channel context set."},
    {THREAD_CONTEXT_SET, "Thread context set."},

    {NEW_USER, "Service ready for new user."},

    {MESSAGE_SENT, "Message sent."},

    {TEAM_SUBSCRIBED, "Team subscribed."},
    {TEAM_UNSUBSCRIBED, "Team unsubscribed."},
    {TEAM_IS_SUBSCRIBED, "Current user is subscribed."},
    {TEAM_IS_NOT_SUBSCRIBED, "Current user is not subscribed."},
    {TEAM_CREATED, "Team created."},
    {CHANNEL_CREATED, "Channel created."},
    {THREAD_CREATED, "Thread created."},
    {REPLY_CREATED, "Reply created."},

    {SYNTAX_ERROR, "Syntax error, command unrecognized."},
    {SYNTAX_ERROR_IN_PARAMETERS,
        "Syntax error in parameters or arguments."},
    {COMMAND_NOT_IMPLEMENTED, "Command not implemented."},
    {BAD_COMMAND_SEQUENCE, "Bad sequence of commands."},
    {COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER,
        "Command not implemented for that parameter."},
    {NAME_TOO_LONG, "Name too long."},
    {DESCRIPTION_TOO_LONG, "Description too long."},
    {BODY_TOO_LONG, "Body too long."},
    {ALREADY_SUBSCRIBED, "Already subscribed."},
    {NOT_SUBSCRIBED, "Not subscribed."},
    {ALREADY_LOGGED_IN, "Already logged in."},
    {ALREADY_LOGGED_OUT, "Already logged out."},
    {ALREADY_EXISTS, "Already exists."},
    {UNSUFFICIENT_PERMISSIONS,
        "Unsufficient permissions to perform this action."},
    {FORBIDDEN_CHARACTERS,
        "Forbidden characters used, only alphanumerical "
        "characters are allowed."},
    {NOT_LOGGED_IN, "Not logged in."},
    {USER_ALREADY_LOGGED_IN, "User already logged in."},
    {-1, "Something went wrong with the server."}
};

/**
 * @brief Check if the code is a special reply code
 * @details Check if the code is a special reply code
 *
 * @param code the code to check
 * @return true if the code is a special reply code
 * @return false if the code is not a special reply code
*/
static bool special_reply_code(int code)
{
    for (uint16_t i = 0; custom_messages_list[i] != -1; i++) {
        if (code == custom_messages_list[i])
            return true;
    }
    return false;
}

/**
 * @brief Rebuild the packet with the current code
 * @details Rebuild the packet with the current code, using the serverMessages
 * list or the custom_messages_list
 * If it's a custom message, it will use the client buffer to send the message
 *
 * @param code the code to rebuild the packet with
 * @param packet the packet to rebuild
 *
 * @return the rebuilt packet
*/
packet_t *rebuild_packet(int code, packet_t *packet)
{
    uint16_t i = 0;

    if (special_reply_code(code))
        return packet;
    for (i = 0; serverMessages[i].code != -1; i++) {
        if (serverMessages[i].code == code) {
            my_free(packet);
            packet = build_packet(code, my_strdup(serverMessages[i].message));
            return packet;
        }
    }
    my_free(packet);
    packet = build_packet(UNKNOWN_ERROR, my_strdup(serverMessages[i].message));
    return packet;
}

/**
 * @brief Reply to the client with the current code
 * @details Reply to the client with the current code
 *
 * @param client the client to reply to
*/
void reply_code(client_t client)
{
    packet_t *packet = pop_packet_from_queue(&client->packet_queue);
    int socketFd = client->fd;
    int code = packet->code;

    packet = rebuild_packet(code, packet);
    send_packet(socketFd, packet);
}
