/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_threads
*/

#include "data_structures.h"

/**
 * @brief Get the threads
 * @details Get the threads
 *
 * @return threads_t* the threads
 */
threads_t *get_threads(void)
{
    static threads_t threads = NULL;

    return &threads;
}
