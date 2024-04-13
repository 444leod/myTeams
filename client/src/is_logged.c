/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** is_logged
*/

#include <stdbool.h>

/**
 * @brief Check if the user is logged
 * @details Check if the user is logged
 *
 * @param change if true, change the value of is_logged
*/
bool is_logged(bool change)
{
    static bool is_logged = false;

    if (change)
        is_logged = !is_logged;
    return is_logged;
}
