/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** cdup
*/

#include "server_teams.h"
#include "clientllist.h"
#include "reply_code.h"
#include "lib.h"
#include <sys/select.h>

/**
 * @brief Verify the path
 * @details Verify the path of the client based on the server path
 *
 * @param client the client to verify the path of
 * @param server_path the server path
*/
static void verify_path(client_t client, char *server_path)
{
    char *new_path = get_current_dir();

    if (new_path == NULL) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    if (strncmp(new_path, server_path, strlen(server_path)) != 0){
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    client->current_code = REQUESTED_FILE_ACTION_COMPLETED;
    client->pwd = supercat(2, new_path + strlen(server_path), "/");
}

/**
 * @brief Change to parent directory
 * @details Change to parent directory, verify the client status and the path
 * to handle errors
 *
 * @param client the client to execute the command for
 * @param server_info the server_info
*/
static void change_to_parent_directory(client_t client,
    server_info_t server_info)
{
    char *path = NULL;

    if (client->status != STATUS_LOGGED_IN) {
        client->current_code = NOT_LOGGED_IN;
        return;
    }
    path = supercat(2, server_info->path, client->pwd);
    chdir(path);
    if (chdir("..") == -1) {
        client->current_code = FILE_UNAVAILABLE;
        return;
    }
    verify_path(client, server_info->path);
}

/**
 * @brief Change to parent directory
 *
 * @param client the client to execute the command for
 * @param server_info the server_info
*/
void cdup(client_t client, UNUSED char **args,
    UNUSED fd_set *readfds, server_info_t server_info)
{
    change_to_parent_directory(client, server_info);
    chdir(server_info->path);
}
