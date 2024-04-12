/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** login
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"

bool is_command_valid(client_t client, char **command)
{
    if (tablen((void **)command) != 2) {
        client->packet = build_packet(SYNTAX_ERROR_IN_PARAMETERS, "");
        return false;
    }
    if (client->user) {
        client->packet = build_packet(ALREADY_LOGGED_IN, "");
        return false;
    }
    if (strlen(command[1]) > 32) {
        client->packet = build_packet(NAME_TOO_LONG, "");
        return false;
    }
    return true;
}

user_t create_user(char *username, int *code)
{
    user_t new_user;
    char *username_buffer = my_malloc(sizeof(char) * 33);
    char *uuid_string;

    memset(username_buffer, 0, sizeof(char) * 33);
    add_user_by_username(username);
    new_user = get_user_by_username(username);
    *code = USER_CREATED;
    memcpy(username_buffer, new_user->username, 33);
    uuid_string = get_uuid_as_string(new_user->uuid);
    server_event_user_created(uuid_string, username_buffer);
    return new_user;
}

void login(client_t client, char **command)
{
    user_t user;
    int code;

    if (!is_command_valid(client, command))
        return;
    user = get_user_by_username(command[1]);
    if (!user) {
        user = create_user(command[1], &code);
    } else
        code = USER_LOGGED_IN;
    client->user = user;
    user->status = STATUS_LOGGED_IN;
    client->packet = build_userinfo_packet(code, user->username, user->uuid);
    server_event_user_logged_in(get_uuid_as_string(user->uuid));
}
