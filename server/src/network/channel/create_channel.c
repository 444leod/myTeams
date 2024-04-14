/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** create_channel
*/

#include "data_structures.h"
#include "garbage_collector.h"
#include <string.h>

/**
 * @brief Create a channel object
 * @details Create a channel object
 *
 * @param title the title of the channel
 * @param description the description of the channel
 * @param team_uuid the team uuid
 *
 * @return channel_t* the channel
 */
channel_t *create_channel(title_t title, description_t description,
    uuid_t team_uuid)
{
    channel_t *channel = my_malloc(sizeof(channel_t));

    memcpy(channel->channel_name, title, sizeof(char) * MAX_NAME_LENGTH);
    memcpy(channel->description, description,
        sizeof(char) * MAX_DESCRIPTION_LENGTH);
    memcpy(channel->team_uuid, team_uuid, sizeof(uuid_t));
    uuid_generate(channel->channel_uuid);
    return channel;
}
