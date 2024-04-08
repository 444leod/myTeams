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
} server_message_s;

/**
 * @enum REPLY_CODES
 * @brief Enum of reply codes
 * @details Enum of reply codes with their corresponding code
*/
enum REPLY_CODES {
    SERVICE_READY = 120,
    DATA_CONNECTION_ALREADY_OPEN = 125,
    FILE_STATUS_OK = 150,
    COMMAND_OK = 200,
    HELP_MESSAGE = 214,
    SERVICE_READY_NEW_USER = 220,
    SERVICE_CLOSING_CONTROL_CONNECTION = 221,
    CLOSING_DATA_CONNECTION = 226,
    ENTERING_PASSIVE_MODE = 227,
    USER_LOGGED_IN = 230,
    REQUESTED_FILE_ACTION_COMPLETED = 250,
    PATHNAME_CREATED = 257,
    USERNAME_OK_NEED_PASSWORD = 331,
    NEED_ACCOUNT_FOR_LOGIN = 332,
};

/**
 * @enum ERROR_CODES
 * @brief Enum of error codes
 * @details Enum of error codes with their corresponding code
*/
enum ERROR_CODES {
    CANT_OPEN_DATA_CONNECTION = 425,
    SYNTAX_ERROR = 500,
    SYNTAX_ERROR_IN_PARAMETERS = 501,
    COMMAND_NOT_IMPLEMENTED = 502,
    BAD_COMMAND_SEQUENCE = 503,
    COMMAND_NOT_IMPLEMENTED_FOR_PARAMETER = 504,
    NOT_LOGGED_IN = 530,
    NEED_ACCOUNT_FOR_STORING_FILES = 532,
    FILE_UNAVAILABLE = 550,
    PAGE_TYPE_UNKNOWN = 551,
    EXCEEDED_STORAGE_ALLOCATION = 552,
    BAD_FILENAME = 553,
};
