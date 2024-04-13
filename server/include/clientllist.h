/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** clientllist
*/

#pragma once

#include <stdlib.h>
#include <uuid/uuid.h>
#include "packet.h"

#define USER_SAVE_PATH ".save/.users"

typedef struct user_s {
    username_t username;
    uuid_t uuid;
    struct user_s *next;
    enum {
        STATUS_NOT_LOGGED_IN,
        STATUS_LOGGED_IN,
    } status;
} *user_t;

void init_users(void);
user_t *get_users(void);
void add_user_by_username(char *username);
void add_user(user_t new_user);
void dump_users(void);
user_t get_user_by_uuid(uuid_t uuid);
user_t get_user_by_username(char *username);


typedef struct client_s {
    int fd;
    struct user_s *user;
    packet_queue_t packet_queue;
    char *command;
    char *next_commands;
    char *buffer;
    char **args;
    unsigned int data_len;
    enum {
        READING,
        WRITING,
        PROCESSING,
    } data_status;
    struct client_s *next;
} *client_t;

void add_client(client_t new_client);
void remove_client(int fd);
client_t create_client(int fd);
client_t *get_clients(void);
client_t get_client_by_fd(int fd);
client_t get_client_by_username(char *username);
client_t get_client_by_uuid(uuid_t uuid);
void clear_clients(void);
