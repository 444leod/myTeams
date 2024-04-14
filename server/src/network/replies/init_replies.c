/*
** EPITECH PROJECT, 2024
** myreplies
** File description:
** init_replies
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
 * @brief Read the replies from the save file
 * @details Read the replies from the save file
 *
 * @param fd the file descriptor
*/
void read_replies(int fd)
{
    team_t *new_team;
    int rd = 0;

    while (1) {
        new_team = my_malloc(sizeof(team_t));
        rd = read(fd, new_team, sizeof(team_t));
        if (rd <= 0 || rd != sizeof(team_t)) {
            my_free(new_team);
            break;
        }
        add_to_list((void *)new_team, (node_t *)get_replies());
    }
}

/**
 * @brief Init the replies linked list
 * @details Init the replies linked list using the .save/.replies file
*/
void init_replies(void)
{
    replies_t *replies = get_replies();
    int fd = open(SAVE_FOLDER".replies", O_RDONLY);

    *replies = NULL;
    DEBUG_PRINT("Init replies\n");
    if (fd == -1) {
        printf("replies: No save file\n");
        return;
    }
    if (!is_magic_number_valid(fd)) {
        printf("replies: Invalid magic number\n");
        close(fd);
        return;
    }
    read_replies(fd);
    close(fd);
}
