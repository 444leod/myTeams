/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** toggle
*/

#include <stdbool.h>

/**
 * @brief Check if we need to read
 * @details Check if we need to read
 *
 * @param change the change
 * @param status the status
 *
 * @return bool the status
 */
bool need_to_read(bool change, bool status)
{
    static bool toggle = false;

    if (change)
        toggle = status;
    return toggle;
}
