/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_team
*/

#include "data_structures.h"
#include "garbage_collector.h"
#include <string.h>

/**
 * @brief Create a team object
 * @details Create a team object
 *
 * @param name the name of the team
 * @param description the description of the team
 *
 * @return team_t* the team
 */
team_t *create_team(char *name, char *description)
{
    team_t *team = my_malloc(sizeof(struct team_s));

    memcpy(team->name, name, sizeof(char) * MAX_NAME_LENGTH);
    memcpy(team->description, description,
        sizeof(char) * MAX_DESCRIPTION_LENGTH);
    uuid_generate(team->uuid);
    return team;
}
