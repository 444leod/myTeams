/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_uuid_as_string
*/

#include "garbage_collector.h"
#include <stdlib.h>
#include <uuid/uuid.h>

/**
 * @brief Get the uuid as string
 * @details Transform the uuid_t into a string
 * (37 is the size of a uuid string representation + 1 for the null byte)
 *
 * @param uuid the uuid to transform
 *
 * @return the string
*/
char *get_uuid_as_string(uuid_t uuid)
{
    char *str = my_malloc(37);

    uuid_unparse(uuid, str);
    return str;
}
