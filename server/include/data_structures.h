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

typedef struct replies_s {
    struct replies_s *next;
    reply_t *reply;
} *replies_t;

typedef struct channels_s {
    struct channels_s *next;
    channel_t *channel;
} *channels_t;

typedef struct users_s {
    struct users_s *next;
    user_information_t *user;
} *users_t;

threads_t *get_threads(void);
thread_t *get_thread_by_uuid(uuid_t thread_uuid);
thread_t *get_thread_by_title(char *title);
threads_t *get_threads_by_creator(uuid_t creator_uuid);
thread_t *create_thread(title_t title, body_t body, uuid_t creator_uuid,
    uuid_t channel_uuid);
void dump_threads(void);
void init_threads(void);

teams_t *get_teams(void);
team_t *get_team_by_uuid(uuid_t team_uuid);
team_t *get_team_by_name(char *name);
users_t get_team_subscribers(team_t *team);
team_t *create_team(char *name, char *description);
void dump_teams(void);
void init_teams(void);

replies_t *get_replies(void);
reply_t *get_reply_by_uuid(uuid_t reply_uuid);
replies_t *get_replies_by_creator(uuid_t reply_creator);
replies_t *get_replies_by_thread(uuid_t thread_uuid);
reply_t *create_reply(char *body, uuid_t creator_uuid, uuid_t thread_uuid);
void dump_replies(void);
void init_replies(void);

channels_t *get_channels(void);
channel_t *get_channel_by_uuid(uuid_t channel_uuid);
channel_t *get_channel_by_name(char *name);
channels_t *get_channels_by_team(uuid_t team_uuid);
channel_t *create_channel(title_t title, description_t description,
    uuid_t team_uuid);
void dump_channels(void);
void init_channels(void);
