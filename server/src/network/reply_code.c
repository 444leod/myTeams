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
 * @brief The server messages
 * @details The messages that the server can send to the client based on the
 * current code
*/
const server_message_s serverMessages[] = {
    {SERVICE_READY,
        "%d Service ready in %d minutes.\n"},
    {DATA_CONNECTION_ALREADY_OPEN,
        "%d Data connection already open; transfer starting.\n"},
    {FILE_STATUS_OK,
        "%d File status okay; about to open data connection.\n"},
    {COMMAND_OK,
        "%d Command okay.\n"},
    {HELP_MESSAGE,
        "%d-%s\n%d Help message.\n"},
    {SERVICE_READY_NEW_USER,
        "%d Service ready for new user.\n"},
    {SERVICE_CLOSING_CONTROL_CONNECTION,
        "%d Service closing control connection.\n"},
    {CLOSING_DATA_CONNECTION,
        "%d Closing data connection.\n"},
    {ENTERING_PASSIVE_MODE,
        "%d Entering Passive Mode (%s).\n"},
    {USER_LOGGED_IN,
        "%d User logged in, proceed.\n"},
    {REQUESTED_FILE_ACTION_COMPLETED,
        "%d Requested file action okay, completed.\n"},
    {PATHNAME_CREATED,
        "%d \"%s\".\n"},
    {USERNAME_OK_NEED_PASSWORD,
        "%d Username okay, need password.\n"},
    {NEED_ACCOUNT_FOR_LOGIN,
        "%d Need account for login.\n"},
    {SYNTAX_ERROR,
        "%d Syntax error, command unrecognized.\n"},
    {SYNTAX_ERROR_IN_PARAMETERS,
        "%d Syntax error in parameters or arguments.\n"},
    {COMMAND_NOT_IMPLEMENTED,
        "%d Command not implemented.\n"},
    {BAD_COMMAND_SEQUENCE,
        "%d Bad sequence of commands.\n"},
    {COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER,
        "%d Command not implemented for that parameter.\n"},
    {NOT_LOGGED_IN,
        "%d Not logged in.\n"},
    {NEED_ACCOUNT_FOR_STORING_FILES,
        "%d Need account for storing files.\n"},
    {FILE_UNAVAILABLE,
        "%d File unavailable (e.g., file not found, no access).\n"},
    {PAGE_TYPE_UNKNOWN,
        "%d Page type unknown.\n"},
    {EXCEEDED_STORAGE_ALLOCATION,
        "%d Exceeded storage allocation.\n"},
    {BAD_FILENAME,
        "%d Bad filename.\n"},
    {CANT_OPEN_DATA_CONNECTION,
        "%d Can't open data connection.\n"},
    {-1, (void *)0}
};

/**
 * @brief Display the current pwd to the client
 * @details Send the current pwd to the client
 *
 * @param client the client to send the pwd to
 * @param socketFd the socket to send the pwd to
 * @param code the code to send
 *
 * @return true if the pwd was sent
*/
static bool display_pwd(client_t client, int socketFd, int code)
{
    char *pwd = my_strdup(client->pwd);

    if (strlen(pwd) > 2 && pwd[strlen(pwd) - 1] == '/')
        pwd[strlen(pwd) - 1] = '\0';
    dprintf(socketFd, serverMessages[11].message, code, pwd);
    my_free(pwd);
    return true;
}

/**
 * @brief Check if the current code is a special reply code
 * @details Check if the current code is a special reply code, if it is, reply
 *  to the client with the special message and return true
 *
 * @param client the client to check
 * @param code the code to check
 * @param socketFd the socket to reply to
 *
 * @return true if the current code is a special reply code
*/
static bool special_reply_codes2(client_t client, int code, int socketFd)
{
    switch (code) {
        case PATHNAME_CREATED:
            return display_pwd(client, socketFd, code);
        case ENTERING_PASSIVE_MODE:
            dprintf(socketFd, serverMessages[8].message, code, client->buffer);
            return true;
        case SERVICE_CLOSING_CONTROL_CONNECTION:
            dprintf(socketFd, serverMessages[6].message, code);
            remove_client(client->fd);
            return true;
        case HELP_MESSAGE:
            dprintf(socketFd, serverMessages[4].message, code,
                client->buffer, code);
            return true;
    }
    return false;
}

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
        case SERVICE_READY:
            dprintf(socketFd, serverMessages[0].message, code, 0);
            return true;
        case HELP_MESSAGE:
        case PATHNAME_CREATED:
        case ENTERING_PASSIVE_MODE:
        case SERVICE_CLOSING_CONTROL_CONNECTION:
            return special_reply_codes2(client, code, socketFd);
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
}
