/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** data_structures
*/

#pragma once

#define SAVE_FOLDER ".save/"
#include "packet.h"

typedef struct threads_s {
    struct threads_s *next;
    thread_t *thread;
} *threads_t;

threads_t *get_threads(void);
thread_t *create_thread(char *title, char *body, uuid_t creator_uuid);
void dump_threads(void);
void init_threads(void);
