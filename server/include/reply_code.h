/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** reply_code
*/

#pragma once

typedef struct server_message_s {
    int code;
    char *message;
} server_message_t;

/**
 * @enum REPLY_CODES
 * @brief Enum of reply codes
 * @details Enum of reply codes with their corresponding code
*/
enum REPLY_CODES {
    COMMAND_OK = 200,
    HELP_MESSAGE = 201,
    GLOBAL_CONTEXT_SET = 202,
    TEAM_CONTEXT_SET = 203,
    CHANNEL_CONTEXT_SET = 204,
    THREAD_CONTEXT_SET = 205,

    USERS_LIST = 211,
    USER_INFO = 212,
    USER_CREATED = 213,
    USER_LOGGED_IN = 214,
    USER_LOGGED_OUT = 215,

    SERVICE_READY_NEW_USER = 220,

    MESSAGE_SENT = 230,

    TEAM_SUBSCRIBED = 240,
    TEAM_UNSUBSCRIBED = 241,
    TEAM_IS_SUBSCRIBED = 242,
    TEAM_IS_NOT_SUBSCRIBED = 243,

    TEAM_CREATED = 250,
    CHANNEL_CREATED = 251,
    THREAD_CREATED = 252,
    REPLY_CREATED = 253,

    TEAM_LIST = 260,
    CHANNEL_LIST = 261,
    THREAD_LIST = 262,
    REPLY_LIST = 263,

    CURRENT_USER_INFO = 270,
    TEAM_INFO = 271,
    CHANNEL_INFO = 272,
    THREAD_INFO = 273,
};

/**
 * @enum ERROR_CODES
 * @brief Enum of error codes
 * @details Enum of error codes with their corresponding code
*/
enum ERROR_CODES {
    SYNTAX_ERROR = 500,
    SYNTAX_ERROR_IN_PARAMETERS = 501,
    COMMAND_NOT_IMPLEMENTED = 502,
    BAD_COMMAND_SEQUENCE = 503,
    COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER = 504,
    NAME_TOO_LONG = 505,
    DESCRIPTION_TOO_LONG = 506,
    BODY_TOO_LONG = 507,
    INEXISTANT_TEAM = 508,
    INEXISTANT_CHANNEL = 509,
    INEXISTANT_THREAD = 510,
    INEXISTANT_USER = 511,
    ALREADY_SUBSCRIBED = 512,
    NOT_SUBSCRIBED = 513,
    ALREADY_LOGGED_IN = 514,
    ALREADY_LOGGED_OUT = 515,
    ALREADY_EXISTS = 516,
    UNSUFFICIENT_PERMISSIONS = 517,
    FORBIDDEN_CHARACTERS = 518,
    NOT_LOGGED_IN = 530
};
