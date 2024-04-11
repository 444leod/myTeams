/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_clients
*/

#include "clientllist.h"
#include <string.h>
#include <uuid/uuid.h>

/**
 * @brief Get the clients
 * @details Get the clients linked list
*/
client_t *get_clients(void)
{
    static client_t clients = NULL;

    return &clients;
}

client_t get_client_by_uuid(uuid_t uuid)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;
    user_t current_user = NULL;

    while (tmp) {
        current_user = tmp->user;
        if (!current_user) {
            tmp = tmp->next;
            continue;
        }
        if (uuid_compare(current_user->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

client_t get_client_by_fd(int fd)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;

    while (tmp) {
        if (tmp->fd == fd)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

client_t get_client_by_username(char *username)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;
    user_t current_user = NULL;

    while (tmp) {
        current_user = tmp->user;
        if (!current_user) {
            tmp = tmp->next;
            continue;
        }
        if (strcmp(current_user->username, username) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
