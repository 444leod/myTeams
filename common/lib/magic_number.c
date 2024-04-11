/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** magic_number
*/

#include "magic_number.h"
#include <stdbool.h>
#include <unistd.h>

bool is_magic_number_valid(int fd)
{
    unsigned int magic_number = 0;

    if (read(fd, &magic_number, sizeof(magic_number)) == -1)
        return false;
    return (magic_number == MAGIC_NUMBER);
}

void write_magic_number(int fd)
{
    unsigned int magic_number = MAGIC_NUMBER;

    write(fd, &magic_number, sizeof(magic_number));
}
