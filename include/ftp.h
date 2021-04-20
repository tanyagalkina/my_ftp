/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <assert.h>

#define SAIN struct sockaddr_in
#define SA struct sockaddr
#define SS struct sockaddr_storage
#define MAXLINE     2048

typedef struct server {
    int sd;
    SAIN addr;
    char *anon_home;
    int pid;
}server_t;

typedef struct client {
    char *name;
    char *pwd;
    char *home;
    int userfd;
    int transfd;
    int auth;
    bool connected;
    bool receiving;
    FILE *inc_file;
    SAIN *clsock;
}client_t;

void server_run(int port, char *path);