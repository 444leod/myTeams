/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_uuid_as_string
*/

#include "garbage_collector.h"
#include <stdlib.h>
#include <uuid/uuid.h>

char *get_uuid_as_string(uuid_t uuid)
{
    char *str = my_malloc(37);

    uuid_unparse(uuid, str);
    return str;
}
