/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** print_fd_set
*/

#include <stdio.h>
#include <sys/select.h>
#include "debug.h"
#include "macros.h"
#include "lib.h"

UNUSED static char *dev_get_full_buffer(
    int *rfds,
    int rcount,
    int *wfds,
    int wcount)
{
    int offset = 0;
    char buffer[1024];

    offset += sprintf(buffer + offset, "[DEBUG] read fds: [");
    for (int i = 0; i < rcount - 1; ++i)
        offset += sprintf(buffer + offset, "%d, ", rfds[i]);
    offset += sprintf(buffer + offset, "%d]\n", rfds[rcount - 1]);
    offset += sprintf(buffer + offset, "[DEBUG] write fds: [");
    for (int i = 0; i < wcount - 1; ++i)
        offset += sprintf(buffer + offset, "%d, ", wfds[i]);
    offset += sprintf(buffer + offset, "%d]\n", wfds[wcount - 1]);
    return my_strdup(buffer);
}

/**
 * @brief Print a fd_set (debug)
 * @details Print a fd_set (only in dev mode)
 *
 * @param set the fd_set to print
*/
UNUSED static void dev_print_fd_set(fd_set *readfds, fd_set *writefds)
{
    int rfds[FD_SETSIZE] = {0};
    int wfds[FD_SETSIZE] = {0};
    int rcount = 0;
    int wcount = 0;
    UNUSED char *buffer;
    UNUSED static int print = 0;

    for (int i = 0; i < FD_SETSIZE; ++i) {
        if (FD_ISSET(i, readfds)) {
            rfds[rcount] = i;
            rcount++;
        }
        if (FD_ISSET(i, writefds)) {
            wfds[wcount] = i;
            wcount++;
        }
    }
    buffer = dev_get_full_buffer(rfds, rcount, wfds, wcount);
    SOMETIMES_DEBUG(&print, 5000, "%s", buffer);
}

/**
 * @brief Print a fd_set (debug)
 * @details Print a fd_set (only in dev mode)
 *
 * @param set the fd_set to print
*/
void print_fd_set(UNUSED fd_set *readfds, UNUSED fd_set *writefds)
{
    #ifndef DEV_MODE
    #else
    dev_print_fd_set(readfds, writefds);
    #endif
}
