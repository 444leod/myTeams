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
} cmd_requirements_t;

static cmd_requirements_t cmd_requirements[] = {
    {"/login", 2, 2, false},
    {"/logout", 1, 1, true},
    {"/users", 1, 1, true},
    {"/user", 2, 2, true},
    {"/send", 2, 2, true},
    {"/messages", 2, 2, true},
    {"/subscribe", 2, 2, true},
    {"/subscribed", 1, 2, true},
    {"/unsubscribe", 2, 2, true},
    {"/use", 2, 4, true},
    {"/create", 2, 3, true},
    {"/list", 1, 1, true},
    {"/info", 2, 2, true},
    {"/help", 1, 1, false},
    {NULL, 0, 0, false}
};
