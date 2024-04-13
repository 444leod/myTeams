/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** input_process
*/

#include "cmd_requirements.h"
#include "lib.h"
#include "client_teams.h"

/**
 * @brief Verify if the command given and the login status are compatible
 * @details Verify if the command given and the login status are compatible
 *  if not, print an error message.
 *
 * @param need_logged if the command need to the user to be logged in
 *
 * @return true if the command and the login status are compatible
 * @return false if the command and the login status are not compatible
*/
bool verify_logged(bool need_logged)
{
    bool is_client_logged = is_logged(0);

    if (need_logged == false && is_client_logged == true) {
        printf("You are already logged in\n");
        return 0;
    }
    if (is_client_logged == false && need_logged == true) {
        printf("You must be logged in to use this command\n");
        return 0;
    }
    return 1;
}

/**
 * @brief Check if the command given is coherent with the command requirements
 * @details Check if the command given is coherent with the command
 *  requirements
 *  if not, print an error message and free the message.
 *
 * @param cmd_requirements the command requirements
 * @param args_nbr the number of arguments
 * @param message the message
*/
void check_requirements(cmd_requirements_t cmd_requirements, int args_nbr,
    char **message)
{
    if (verify_logged(cmd_requirements.need_logged) == 0) {
        my_free(*message);
        *message = NULL;
        return;
    }
    if (cmd_requirements.min_args > args_nbr ||
        cmd_requirements.max_args < args_nbr) {
        printf("Invalid number of arguments\n");
        my_free(*message);
        *message = NULL;
        return;
    }
}

/**
 * @brief Verify if the command given is valid
 * @details Verify if the command given is valid
 *
 * @param message the message
 * @param args the arguments
 * @param args_nbr the number of arguments
*/
void verify_command(char **message, char **args, int args_nbr)
{
    for (int i = 0; cmd_requirements[i].command; i++) {
        if (strcmp(cmd_requirements[i].command, args[0]) == 0) {
            check_requirements(cmd_requirements[i], args_nbr, message);
            return;
        }
    }
    printf("Unkown command: %s\n", get_escaped_string(args[0]));
    my_free(*message);
    *message = NULL;
}

//must replace str to word array with quote_split
/**
 * @brief Process the input of the user
 * @details Process the input of the user
 *
 * @param message the message
*/
void process_input(char **message)
{
    char **args = str_to_word_array(*message, " \t\n");

    for (uint16_t i = tablen((void **)args) - 1; i > 0; i--) {
        if (args[i][0] == '\0')
            args[i] = NULL;
        else
            break;
    }
    if (args == NULL) {
        printf("Invalid command (unmatching quote)\n");
        my_free(*message);
        *message = NULL;
        return;
    }
    if (args[0] == NULL || args[0][0] == '\0') {
        my_free(*message);
        *message = NULL;
        return;
    }
    verify_command(message, args, tablen((void **)args));
}
