/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** get_channel
*/

#include "data_structures.h"
#include <string.h>

/**
 * @brief Get the channel by uuid
 * @details Get the channel by uuid
 *
 * @param channel_uuid the channel uuid
 *
 * @return channel_t* the channel
 */
channel_t *get_channel_by_uuid(uuid_t channel_uuid)
{
    channels_t *channels = get_channels();
    channels_t tmp = *channels;

    while (tmp) {
        if (uuid_compare(tmp->channel->uuid, channel_uuid) == 0)
            return tmp->channel;
        tmp = tmp->next;
    }
    return NULL;
}

/**
 * @brief Get the channel by name
 * @details Get the channel by name
 *
 * @param name the name
 *
 * @return channel_t* the channel
 */
channel_t *get_channel_by_name(char *name)
{
    channels_t *channels = get_channels();
    channels_t tmp = *channels;

    while (tmp) {
        if (strcmp(tmp->channel->channel_name, name) == 0)
            return tmp->channel;
        tmp = tmp->next;
    }
    return NULL;
}
