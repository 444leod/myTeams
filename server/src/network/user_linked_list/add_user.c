/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** add_user
*/

#include "clientllist.h"
#include "lib.h"

/**
 * @brief Add a user to the linked list
 * @details Add a user to the linked list
 *
 * @param new_user the user to add
*/
void add_user(user_t new_user)
{
    user_t *users = get_users();
    user_t tmp = *users;

    if (!*users) {
        *users = new_user;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_user;
}

void add_user_by_username(char *username)
{
    user_t new_user = malloc(sizeof(struct user_s));

    for (int i = 0; i < 33; i++)
        new_user->username[i] = 0;
    strcpy(new_user->username, username);
    uuid_generate(new_user->uuid);
    new_user->next = NULL;
    new_user->status = STATUS_NOT_LOGGED_IN;
    add_user(new_user);
}
