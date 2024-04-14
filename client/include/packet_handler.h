/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** reply_code
*/

#pragma once

#include "packet.h"

typedef struct packet_handler_s {
    int type;
    void (*func)(packet_t *packet);
} packet_handler_t;

extern const packet_handler_t packet_handlers[];

void buffer_packet_handler(packet_t *packet);
void userinfo_packet_handler(packet_t *packet);
void thread_packet_handler(packet_t *packet);
void error_packet_handler(packet_t *packet);
void user_command_packet_handler(packet_t *packet);
void log_command_packet_handler(packet_t *packet);
void handle_inexistant_user_packet(packet_t *packet);
void team_packet_handler(packet_t *packet);
void reply_packet_handler(packet_t *packet);
void channel_packet_handler(packet_t *packet);
