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
 * @brief Print the thread structure following the given format
 * @details Print the thread structure following the given format
 *
 * @param format the format
 * @param thread the thread
*/
static void print_thread(char *format, thread_t *thread)
{
    char *uuid = get_uuid_as_string(thread->uuid);
    char *creator_uuid = get_uuid_as_string(thread->creator_uuid);

    printf(format, thread->title, uuid, creator_uuid, thread->body);
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
            print_thread(
                "Thread created: \"%s\" (uuid: \"%s\") by %s: \"%s\"\n",
                thread);
            log_thread(client_event_thread_created, thread);
            break;
        case THREAD_INFO:
            print_thread("Thread info: \"%s\" (uuid: \"%s\") by %s: \"%s\"\n",
                thread);
            log_thread(client_print_thread, thread);
            break;
        case THREAD_LIST:
            print_thread("Thread list: \"%s\" (uuid: \"%s\") by %s: \"%s\"\n",
                thread);
            log_thread(client_channel_print_threads, thread);
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
        case ALREADY_EXISTS:
            printf("This thread already exist!\n");
            client_error_already_exist();
            break;
        default:
            printf("Unknown packet code\n");
            break;
    }
}
