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

const enum REPLY_CODES custom_messages_list[] = {
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
};

/**
 * @brief The server messages
 * @details The messages that the server can send to the client based on the
 * current code
*/
const server_message_t serverMessages[] = {
    {COMMAND_OK, "%d Command okay.\n"},
    {HELP_MESSAGE, "%d-%s\n%d Help message.\n"},
    {GLOBAL_CONTEXT_SET, "%d Global context set.\n"},
    {TEAM_CONTEXT_SET, "%d Team context set.\n"},
    {CHANNEL_CONTEXT_SET, "%d Channel context set.\n"},
    {THREAD_CONTEXT_SET, "%d Thread context set.\n"},
    {USER_CREATED,
        "%d User created (username: \"%s\", uuid: \"%s\"). User logged in.\n"},
    {USER_LOGGED_IN, "%d User logged in, proceed.\n"},
    {USER_LOGGED_OUT, "%d User logged out.\n"},
    {SERVICE_READY_NEW_USER, "%d Service ready for new user.\n"},
    {MESSAGE_SENT, "%d Message sent.\n"},
    {TEAM_SUBSCRIBED, "%d Team subscribed.\n"},
    {TEAM_UNSUBSCRIBED, "%d Team unsubscribed.\n"},
    {TEAM_IS_SUBSCRIBED, "%d Current user is subscribed.\n"},
    {TEAM_IS_NOT_SUBSCRIBED, "%d Current user is not subscribed.\n"},
    {TEAM_CREATED, "%d Team created.\n"},
    {CHANNEL_CREATED, "%d Channel created.\n"},
    {THREAD_CREATED, "%d Thread created.\n"},
    {REPLY_CREATED, "%d Reply created.\n"},

    {SYNTAX_ERROR, "%d Syntax error, command unrecognized.\n"},
    {SYNTAX_ERROR_IN_PARAMETERS,
        "%d Syntax error in parameters or arguments.\n"},
    {COMMAND_NOT_IMPLEMENTED, "%d Command not implemented.\n"},
    {BAD_COMMAND_SEQUENCE, "%d Bad sequence of commands.\n"},
    {COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER,
        "%d Command not implemented for that parameter.\n"},
    {NAME_TOO_LONG, "%d Name too long.\n"},
    {DESCRIPTION_TOO_LONG, "%d Description too long.\n"},
    {BODY_TOO_LONG, "%d Body too long.\n"},
    {INEXISTANT_TEAM, "%d Inexistant team.\n"},
    {INEXISTANT_CHANNEL, "%d Inexistant channel.\n"},
    {INEXISTANT_THREAD, "%d Inexistant thread.\n"},
    {INEXISTANT_USER, "%d Inexistant user.\n"},
    {ALREADY_SUBSCRIBED, "%d Already subscribed.\n"},
    {NOT_SUBSCRIBED, "%d Not subscribed.\n"},
    {ALREADY_LOGGED_IN, "%d Already logged in.\n"},
    {ALREADY_LOGGED_OUT, "%d Already logged out.\n"},
    {ALREADY_EXISTS, "%d Already exists.\n"},
    {UNSUFFICIENT_PERMISSIONS,
        "%d Unsufficient permissions to perform this action.\n"},
    {FORBIDDEN_CHARACTERS,
        "%d Forbidden characters used, only alphanumerical "
        "characters are allowed.\n"},
    {NOT_LOGGED_IN, "%d Not logged in.\n"},
    {-1, (void *)0}
};

/**
 * @brief Check if the current code is a special reply code
 * @details Check if the current code is a special reply code, if it is, reply
 *   to the client with the special message and return true
 *
 * @param client the client to check
 *
 * @return true if the current code is a special reply code
*/
static bool special_reply_code(client_t client)
{
    int socketFd = client->fd;
    int code = client->current_code;

    switch (code) {
        case USER_LOGGED_OUT:
            dprintf(socketFd, serverMessages[6].message, code);
            remove_client(client->fd);
            return true;
        case HELP_MESSAGE:
            dprintf(socketFd, serverMessages[4].message, code,
                client->buffer, code);
            return true;
        case USER_CREATED:
            dprintf(socketFd, serverMessages[6].message, code,
                client->user->username,
                get_uuid_as_string(client->user->uuid));
            return true;
    }
    return false;
}

/**
 * @brief Reply to the client with the current code
 * @details Reply to the client with the current code
 *
 * @param client the client to reply to
*/
void reply_code(client_t client)
{
    int socketFd = client->fd;
    int code = client->current_code;

    if (special_reply_code(client))
        return;
    for (int i = 0; serverMessages[i].code != -1; i++) {
        if (serverMessages[i].code == code) {
            dprintf(socketFd, serverMessages[i].message, code);
            return;
        }
    }
    dprintf(socketFd, "%d Unknown reply code.\n", code);
}
