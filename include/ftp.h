/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** header
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
#include <signal.h>
#include <bits/signum.h>
#include <curses.h>

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
    unsigned short p_port;
    bool auth;
    bool receiving;
    bool exit;
    bool pasv;
    char *strip;
    FILE *inc_file;
    SAIN *in_adr;
    SS *claddr;
    SA *addr;
    socklen_t addr_len;
    char ip[INET_ADDRSTRLEN];
}client_t;

typedef struct server {
    int sd;
    SAIN conn_addr;
    SAIN data_addr;
    char *anon_home;
    int pid;
    client_t *conn_list;
    fd_set master;
    fd_set read;
    fd_set write;
}server_t;

void remove_from_list(client_t *tmp, server_t *server);
void add_to_list(server_t *server, client_t *new_cl);
void show_list(client_t *cl_list);
void set_signals(void);
void sig_handler(int sig);
void show_list(client_t *cl_list);
client_t *get_client_by_sd(int sd, client_t *list);
void sig_handler(int sig);
int get_input(client_t *, server_t *server);
void remove_from_list(client_t *tmp, server_t *server);
void add_client(server_t *server, int ns, SS rem_addr, socklen_t adlen);
void remove_client(int sd, server_t *server);
void server_run(int port, char *path, socklen_t adlen);