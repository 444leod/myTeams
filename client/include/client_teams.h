/*
** EPITECH PROJECT, 2024
** myTeams
** File description:
** teams
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "lib.h"
#include "debug.h"
#include "garbage_collector.h"
#include "macros.h"

typedef struct server_info_s {
    int port;
    char *path;
    char *ip;
} *server_info_t;

int client(int argc, char *argv[]);
void check_args(int argc, char *argv[]);
int get_socket(void);
void bind_socket(int socketFd, int port, char **ip);
void listen_socket(int socketFd, int maxClients);
void accept_socket(int socketFd, void (*func)(int));
void print_fd_set(fd_set *readfds, fd_set *writefds);
void get_port(int fd, int *port);
void connect_to_server(int sockfd, char *ip, int port);
