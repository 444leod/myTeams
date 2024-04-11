/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** init_users
*/

#include "clientllist.h"
#include "fcntl.h"
#include "lib.h"
#include "garbage_collector.h"
#include "magic_number.h"
#include <unistd.h>
#include <stdlib.h>

void read_users(int fd)
{
    user_t new_user;
    int rd = 0;

    while (1) {
        new_user = my_malloc(sizeof(struct user_s));
        rd = read(fd, new_user, sizeof(struct user_s));
        if (rd <= 0) {
            my_free(new_user);
            break;
        }
        new_user->next = NULL;
        new_user->status = STATUS_NOT_LOGGED_IN;
        add_user(new_user);
    }
}

/**
 * @brief Init the users linked list
 * @details Init the users linked list using the .save/.users file
*/
void init_users(void)
{
    client_t *clients = get_clients();
    int fd = open(USER_SAVE_PATH, O_RDONLY);

    *clients = NULL;
    DEBUG_PRINT("Init users\n");
    if (fd == -1) {
        printf("No save file\n");
        return;
    }
    if (!is_magic_number_valid(fd)) {
        printf("Invalid magic number\n");
        close(fd);
        return;
    }
    read_users(fd);
    close(fd);
}
