/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** packet
*/

#pragma once

    #include <uuid/uuid.h>

#define MAX_NAME_LENGTH 32
typedef char username_t[MAX_NAME_LENGTH + 1];

enum PACKET_TYPE {
    NONE,
    USER_INFORMATION
};

typedef struct packet_s {
    int code;
    int packet_type;
    char packet_body[4096];
} packet_t;

typedef struct user_information_s {
    username_t username;
    uuid_t user_uuid;
} user_information_t;

    #define PACKET_SIZE sizeof(struct packet_s)
    #define USER_INFORMATION_SIZE sizeof(struct user_information_s)

void send_packet(int fd, packet_t *packet);

packet_t *build_packet(int code, char *buffer);
packet_t *build_userinfo_packet(int code, username_t username, uuid_t uuid);

packet_t *read_packet(int fd);
user_information_t *get_userinfo_from_packet(packet_t *packet);
