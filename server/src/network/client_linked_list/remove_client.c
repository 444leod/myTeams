/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** remove_client
*/

#include "clientllist.h"
#include "garbage_collector.h"
#include "logging_server.h"
#include "lib.h"
#include <unistd.h>

/**
 * @brief Destroy the fds
 * @details Destroy the fds of the client
 *
 * @param tmp the client
*/
static void destroy_fds(client_t tmp)
{
    if (tmp->fd != -1) {
        close(tmp->fd);
    }
    if (tmp->user)
        tmp->user->status = STATUS_NOT_LOGGED_IN;
    server_event_user_logged_out(get_uuid_as_string(tmp->user->uuid));
}

/**
 * @brief Remove a client from the linked list
 * @details Remove a client from the linked list
 *
 * @param fd the fd of the client to remove
*/
void remove_client(int fd)
{
    client_t *clients = get_clients();
    client_t tmp = *clients;
    client_t prev = NULL;

    if (tmp && tmp->fd == fd) {
        *clients = tmp->next;
        destroy_fds(tmp);
        return;
    }
    while (tmp && tmp->fd != fd) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (!tmp)
        return;
    destroy_fds(tmp);
    prev->next = tmp->next;
    my_free(tmp);
}
