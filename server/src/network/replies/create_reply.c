/*
** EPITECH PROJECT, 2024
** myreplys
** File description:
** create_reply
*/

#include "data_structures.h"
#include "garbage_collector.h"
#include "linked_lists.h"
#include <string.h>

/**
 * @brief Create a reply object
 * @details Create a reply object
 *
 * @param name the name of the reply
 * @param description the description of the reply
 *
 * @return reply_t* the reply
 */
reply_t *create_reply(char *body, uuid_t creator_uuid, uuid_t thread_uuid)
{
    reply_t *reply = my_malloc(sizeof(struct reply_s));
    team_t *team = get_team_by_uuid(thread_uuid);

    memcpy(reply->body, body, sizeof(char) * MAX_BODY_LENGTH);
    memcpy(reply->creator_uuid, creator_uuid, sizeof(uuid_t));
    memcpy(reply->thread_uuid, thread_uuid, sizeof(uuid_t));
    memcpy(reply->team_uuid, team->uuid, sizeof(uuid_t));
    uuid_generate(reply->uuid);
    add_to_list((void *)reply, (node_t *)get_replies());
    return reply;
}
