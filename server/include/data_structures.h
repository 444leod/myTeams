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

typedef struct teams_s {
    struct teams_s *next;
    team_t *team;
} *teams_t;

threads_t *get_threads(void);
thread_t *get_thread_by_uuid(uuid_t thread_uuid);
thread_t *get_thread_by_title(char *title);
threads_t *get_threads_by_creator(uuid_t creator_uuid);
thread_t *create_thread(char *title, char *body, uuid_t creator_uuid);
void dump_threads(void);
void init_threads(void);

teams_t *get_teams(void);
team_t *get_team_by_uuid(uuid_t team_uuid);
team_t *get_team_by_name(char *name);
team_t *create_team(char *name, char *description);
void dump_teams(void);
void init_teams(void);
