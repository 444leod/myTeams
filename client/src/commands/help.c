/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** help
*/

#include "help.h"
#include <stdio.h>

void help_command(void)
{
    printf("%-45s %-30s %s\n\n", "Command", "Usage", "Description");
    for (int i = 0; help_list[i].command != NULL; i++) {
        printf("%-15s %-60s %s\n", help_list[i].command, help_list[i].usage,
            help_list[i].description);
    }
}
