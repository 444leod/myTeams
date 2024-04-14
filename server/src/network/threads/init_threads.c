/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** init_threads
*/

#include "data_structures.h"
#include "linked_lists.h"
#include "logging_server.h"
#include "debug.h"
#include "garbage_collector.h"
#include "magic_number.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

/**
 * @brief Read the threads from the save file
 * @details Read the threads from the save file
 *
 * TODO: add check of if channel exists
 *
 * @param fd the file descriptor
*/
void read_threads(int fd)
{
    thread_t *new_thread;
    int rd = 0;

    while (1) {
        new_thread = my_malloc(sizeof(thread_t));
        rd = read(fd, new_thread, sizeof(thread_t));
        if (rd <= 0 || rd != sizeof(thread_t)) {
            my_free(new_thread);
            break;
        }
        add_to_list((void *)new_thread, (node_t *)get_threads());
    }
}

/**
 * @brief Init the threads linked list
 * @details Init the threads linked list using the .save/.threads file
*/
void init_threads(void)
{
    threads_t *threads = get_threads();
    int fd = open(SAVE_FOLDER".threads", O_RDONLY);

    *threads = NULL;
    DEBUG_PRINT("Init threads\n");
    if (fd == -1) {
        printf("threads: No save file\n");
        return;
    }
    if (!is_magic_number_valid(fd)) {
        printf("threads: Invalid magic number\n");
        close(fd);
        return;
    }
    read_threads(fd);
    close(fd);
}
