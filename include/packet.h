/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** packet
*/

#pragma once

    #include <uuid/uuid.h>
    #include <stdbool.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512
typedef char username_t[MAX_NAME_LENGTH + 1];

enum PACKET_TYPE {
    NONE,
    USER_INFORMATION,
    THREAD
};

typedef struct packet_s {
    int code;
    bool is_global;
    int packet_type;
    char packet_body[4096];
} packet_t;

typedef struct packet_queue_s {
    packet_t *packet;
    struct packet_queue_s *next;
} *packet_queue_t;

typedef struct user_information_s {
    username_t username;
    uuid_t user_uuid;
    bool is_logged;
} user_information_t;

typedef struct thread_s {
    uuid_t thread_uuid;
    uuid_t creator_uuid;
    time_t timestamp;
    char title[32];
    char body[512];
} thread_t;

    #define PACKET_SIZE sizeof(struct packet_s)
    #define USER_INFORMATION_SIZE sizeof(struct user_information_s)
    #define THREAD_SIZE sizeof(struct thread_s)

void add_packet_to_queue(packet_queue_t *queue, packet_t *packet);
packet_t *pop_packet_from_queue(packet_queue_t *queue);
void free_packet_queue(packet_queue_t *queue);

void send_packet(int fd, packet_t *packet);

packet_t *build_packet(int code, char *buffer);
packet_t *build_custom_packet(int code, char *buffer, int packet_type);
packet_t *build_userinfo_packet(int code, username_t username, uuid_t uuid,
    bool is_logged);
packet_t *build_thread_packet(int code, thread_t *thread);

packet_t *read_packet(int fd);
user_information_t *get_userinfo_from_packet(packet_t *packet);
thread_t *get_thread_from_packet(packet_t *packet);
