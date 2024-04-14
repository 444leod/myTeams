/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_teams
*/

#include "data_structures.h"
#include <string.h>

/**
 * @brief Get the team by uuid
 * @details Get the team by uuid
 *
 * @param team_uuid the team uuid
 *
 * @return team_t* the team
 */
team_t *get_team_by_uuid(uuid_t team_uuid)
{
    teams_t *teams = get_teams();
    teams_t tmp = *teams;

    while (tmp) {
        if (uuid_compare(tmp->team->team_uuid, team_uuid) == 0)
            return tmp->team;
        tmp = tmp->next;
    }
    return NULL;
}
