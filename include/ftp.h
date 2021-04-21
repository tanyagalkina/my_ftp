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
#define MAXLINE     (2048)
#define PATH_MAX    (256)

typedef struct client {
    struct client *next;
    struct client *prev;
    char *name;
    char curr_dir[PATH_MAX];
    char *home;
    int userfd;
    int transfd;
    bool auth;
    bool receiving;
    bool exit;
    FILE *inc_file;
    SS *claddr;
    socklen_t addr_len;

}client_t;

typedef struct server {
    int sd;
    SAIN addr;
    char *anon_home;
    int pid;
    client_t *conn_list;

}server_t;


void remove_from_list(client_t *tmp, server_t *server);
void add_client(server_t *server, int ns,  SS rem_addr, socklen_t adlen);
void remove_client(int sd, server_t *server);
void server_run(int port, char *path);