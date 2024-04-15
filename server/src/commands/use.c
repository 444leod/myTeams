/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** use
*/

#include "commands.h"
#include "reply_code.h"
#include "logging_server.h"
#include "garbage_collector.h"
#include "packet.h"
#include "lib.h"

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
    if (tablen((void **)command) > 4) {
        add_packet_to_queue(&client->packet_queue,
            build_packet(SYNTAX_ERROR_IN_PARAMETERS, ""));
        return false;
    }
    if (!client->user) {
        add_packet_to_queue(&client->packet_queue,
            build_packet(NOT_LOGGED_IN, ""));
        return false;
    }
    return true;
}

/**
 * @brief Check if the uuids given are real
 * @details Check if the uuids given are real
 *
 * @param client the client
 * @param command the command
 *
 * @return true if the uuids are valid
 * @return false if the uuids are not valid
 */
static bool are_uuid_valid(client_t client, char **command)
{
    int codes[3] = {INEXISTANT_TEAM, INEXISTANT_CHANNEL, INEXISTANT_THREAD};
    void *(*func[])(uuid_t) = {
        (void *(*)(unsigned char *))get_team_by_uuid,
        (void *(*)(unsigned char *))get_channel_by_uuid,
        (void *(*)(unsigned char *))get_thread_by_uuid};
    uuid_t uuid;

    for (int i = 1; i < tablen((void **)command); i++) {
        get_uuid_from_string(command[i], uuid);
        if (!is_uuid_valid(command[i]) || !func[i - 1](uuid)) {
            add_packet_to_queue(&client->packet_queue,
                build_error_packet(codes[i - 1], command[i]));
            return false;
        }
    }
    return true;
}

/**
 * @brief set the current client used items using the given uuids
 * @details set the current client used items using the given uuids
 *
 * @param client the client
 * @param command the command
 */
static int set_used_items(client_t client, char **command)
{
    uuid_t uuids[3] = {0};
    int code[3] = {TEAM_CONTEXT_SET, CHANNEL_CONTEXT_SET, THREAD_CONTEXT_SET};

    switch (tablen((void **)command)) {
        case 4:
            get_uuid_from_string(command[3], uuids[2]);
            client->thread = get_thread_by_uuid(uuids[2]);
            break;
        case 3:
            get_uuid_from_string(command[2], uuids[1]);
            client->channel = get_channel_by_uuid(uuids[1]);
            break;
        case 2:
            get_uuid_from_string(command[1], uuids[0]);
            client->team = get_team_by_uuid(uuids[0]);
            break;
    }
    return code[tablen((void **)command) - 2];
}

/**
 * @brief Check if the uuids are unrelated
 * @details Check if the uuids are unrelated
 *
 * @param client the client
 *
 * @return true if the uuids are unrelated
 * @return false if the uuids are related
 */
static bool are_uuids_unrelated(client_t client)
{
    if (client->channel && uuid_compare(client->channel->team_uuid,
        client->team->team_uuid) != 0) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(INEXISTANT_CHANNEL, ""));
        return false;
    }
    if (client->thread && uuid_compare(client->thread->channel_uuid,
        client->channel->channel_uuid) != 0) {
        add_packet_to_queue(&client->packet_queue,
            build_error_packet(INEXISTANT_THREAD, ""));
        return false;
    }
    return true;
}

/**
 * @brief Check if the command is a special case
 * @details Check if the command is a special case, if so, handle it
 *
 * @param client the client
 * @param command the command
 *
 * @return true if the command is a special case
 * @return false if the command is not a special case
 */
static bool is_special_case(client_t client, char **command)
{
    if (tablen((void **)command) == 1) {
        client->team = NULL;
        client->channel = NULL;
        client->thread = NULL;
        add_packet_to_queue(&client->packet_queue,
            build_packet(GLOBAL_CONTEXT_SET, ""));
        return true;
    }
    return false;
}

/**
 * @brief /use command handler
 * @details /use command handler
 *
 * @param client the client
 * @param command the command
 */
void use(client_t client, char **command)
{
    void *old_iteams[3] = {client->team, client->channel, client->thread};
    int code = 0;

    if (!is_command_valid(client, command) || is_special_case(client, command))
        return;
    if (!are_uuid_valid(client, command))
        return;
    client->team = NULL;
    client->channel = NULL;
    client->thread = NULL;
    code = set_used_items(client, command);
    if (!are_uuids_unrelated(client)) {
        printf("uuids are unrelated\n");
        client->team = old_iteams[0];
        client->channel = old_iteams[1];
        client->thread = old_iteams[2];
        return;
    }
    add_packet_to_queue(&client->packet_queue, build_packet(code, ""));
}
