/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** thread
*/

#include "packet.h"
#include "macros.h"
#include "reply_code.h"
#include "logging_client.h"
#include "lib.h"
#include <stdio.h>

/**
 * @brief Execute the given logging function using the thread structure
 * @details Execute the given logging function using the thread structure
 *
 * @param f the logging function
 * @param thread the thread
*/
static void log_thread(
    int (*f) (const char *, const char *, time_t, const char *, const char *),
    thread_t *thread)
{
    char *uuid = get_uuid_as_string(thread->uuid);
    char *creator_uuid = get_uuid_as_string(thread->creator_uuid);

    f(uuid, creator_uuid, thread->timestamp, thread->title, thread->body);
}

/**
 * @brief Print the thread structure with the given start
 * @details Print the thread structure with the given start
 *
 * @param start the start
 * @param thread the thread
*/
static void print_thread(char *start, thread_t *thread)
{
    char *uuid = get_uuid_as_string(thread->uuid);
    char *creator_uuid = get_uuid_as_string(thread->creator_uuid);

    printf(start);
    printf("\"%s\" (uuid: \"%s\") by %s: \"%s\"\n",
        thread->title,
        uuid,
        creator_uuid,
        thread->body);
}

/**
 * @brief Handle the thread type packets
 * @details Handle the thread type packets
 *
 * @param packet the packet
 */
void handle_thread_type_packet(packet_t *packet)
{
    thread_t *thread = get_thread_from_packet(packet);

    switch (packet->code) {
        case THREAD_CREATED:
            log_thread(client_event_thread_created, thread);
            if (!packet->is_global)
                log_thread(client_print_thread_created, thread);
            print_thread("Thread created: ", thread);
            break;
        case THREAD_INFO:
            log_thread(client_print_thread, thread);
            print_thread("Thread info: ", thread);
            break;
        case THREAD_LIST:
            log_thread(client_channel_print_threads, thread);
            print_thread("Thread list: ", thread);
            break;
    }
}

/**
 * @brief Handle the text packets
 * @details Handle the text packets
 *
 * @param packet the packet
 */
static void handle_text_packet(packet_t *packet)
{
    switch (packet->code) {
        case ALREADY_EXISTS:
            client_error_already_exist();
            printf("This thread already exist!\n");
            break;
        case EMPTY_THREAD_LIST:
            printf("Empty thread list.\n");
            break;
        case INEXISTANT_THREAD:
            client_error_unknown_thread(my_strdup(packet->packet_body));
            printf("Thread does not exist\n");
            break;
    }
}

/**
 * @brief Handle the thread packet
 * @details Handle the thread packet
 *
 * @param packet the packet
 */
void thread_packet_handler(packet_t *packet)
{
    switch (packet->code) {
        case THREAD_CREATED:
        case THREAD_INFO:
        case THREAD_LIST:
            handle_thread_type_packet(packet);
            break;
        case EMPTY_THREAD_LIST:
        case ALREADY_EXISTS:
            handle_text_packet(packet);
            break;
        default:
            printf("Thread packet handler: Unknown packet code.\n");
            break;
    }
}
