/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** help
*/

#pragma once

#include <stddef.h>

typedef struct help_s {
    char *command;
    char *usage;
    char *description;
} help_t;

/**
 * @brief help message list
 * @details list of help messages for each command
*/
static const help_t help_list[] = {
    {"/login", "/login [\"username\"]", "Log in to the server"},
    {"/logout", "/logout", "Log out from the server"},
    {"/users", "/users", "List all users"},
    {"/user", "/user [\"user_uuid\"]", "Get user information"},
    {"/send", "/send [\"user_uuid\"] [\"message\"]",
        "Send a message to a user"},
    {"/messages", "/messages [\"user_uuid\"]",
        "List all messages from a user"},
    {"/subscribe", "/subscribe [\"team_uuid\"]", "Subscribe to a team"},
    {"/subscribed", "/subscribed ?[\"team_uuid\"]",
        "List all subscribed users to a team or all teams subscribed to"},
    {"/unsubscribe", "/unsubscribe [\"team_uuid\"]",
        "Unsubscribe from a team"},
    {"/use", "/use ?[\"team_uuid\"] ?[\"channel_uuid\"] ?[\"thread_uuid\"]",
        "Set the commands context to a team, channel, thread or global"},
    {"/create", "/create [\"name\"] ?[\"description\"]",
        "Depending on the context, create a team, channel, thread or reply"},
    {"/list", "/list", "Depending on the context, list all teams, channels, "
        "threads or replies"},
    {"/info", "/info", "Depending on the context, display information about "
        "a team, channel, thread or reply"},
    {"/help", "/help", "Display this help message"},
    {NULL, NULL, NULL}
};
