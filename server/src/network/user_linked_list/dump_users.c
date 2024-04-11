/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** dump_users
*/

#include "clientllist.h"
#include <fcntl.h>
#include <unistd.h>
#include "magic_number.h"

void dump_users(void)
{
    user_t *users = get_users();
    user_t tmp = *users;
    int fd = open(USER_SAVE_PATH, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    unsigned int magic_number = MAGIC_NUMBER;

    if (fd == -1)
        return;
    write(fd, &magic_number, sizeof(magic_number));
    while (tmp) {
        tmp->status = STATUS_NOT_LOGGED_IN;
        write(fd, tmp, sizeof(struct user_s));
        tmp = tmp->next;
    }
}
