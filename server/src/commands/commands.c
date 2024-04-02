/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** commands
*/

#include "commands.h"

/**
 * @brief Commands array
 * @details Array of commands, with their name and function
*/
const command_t commands[] = {
    {"USER", &user},
    {"CWD", &cwd},
    {"QUIT", &quit},
    {"DELE", &dele},
    {"PWD", &pwd},
    {"HELP", &help},
    {"NOOP", &noop},
    {"TYPE", &type},
    {NULL, &unknown_command}
};
