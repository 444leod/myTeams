/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_thread
*/

#include "data_structures.h"
#include <string.h>

/**
 * @brief Get the thread by uuid
 * @details Get the thread by uuid
 *
 * @param thread_uuid the thread uuid
 *
 * @return thread_t* the thread
 */
thread_t *get_thread_by_uuid(uuid_t thread_uuid)
{
    threads_t *threads = get_threads();
    threads_t tmp = *threads;

    while (tmp) {
        if (uuid_compare(tmp->thread->thread_uuid, thread_uuid) == 0)
            return tmp->thread;
        tmp = tmp->next;
    }
    return NULL;
}

/**
 * @brief Get the thread by title
 * @details Get the thread by title
 *
 * @param title the title
 *
 * @return thread_t* the thread
 */
thread_t *get_thread_by_title(char *title)
{
    threads_t *threads = get_threads();
    threads_t tmp = *threads;

    while (tmp) {
        if (strcmp(tmp->thread->title, title) == 0)
            return tmp->thread;
        tmp = tmp->next;
    }
    return NULL;
}
