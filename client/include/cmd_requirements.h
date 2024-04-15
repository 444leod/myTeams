/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** cmd_requirements
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct cmd_requirements_s {
    char *command;
    int min_args;
    int max_args;
    bool need_logged;
    void (*function)(void);
} cmd_requirements_t;

void help_command(void);

static cmd_requirements_t cmd_requirements[] = {
    {"/login", 2, 2, false, NULL},
    {"/logout", 1, 1, true, NULL},
    {"/users", 1, 1, true, NULL},
    {"/user", 2, 2, true, NULL},
    {"/send", 2, 2, true, NULL},
    {"/messages", 2, 2, true, NULL},
    {"/subscribe", 2, 2, true, NULL},
    {"/subscribed", 1, 2, true, NULL},
    {"/unsubscribe", 2, 2, true, NULL},
    {"/use", 1, 4, true, NULL},
    {"/create", 2, 3, true, NULL},
    {"/list", 1, 1, true, NULL},
    {"/info", 2, 2, true, NULL},
    {"/help", 1, 1, false, &help_command},
    {NULL, 0, 0, false, NULL}
};
