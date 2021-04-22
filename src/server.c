/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include <signal.h>
#include <bits/signum.h>
#include <curses.h>
#include "../include/ftp.h"
#include "../include/commands.h"

void serv_init(server_t *server, int port, char *path)
{
    int opt = 1;
    if ((server->sd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(84);
    }
    if (setsockopt(server->sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, \
&opt, sizeof(opt))) {
        perror("setsockopt");
        exit(84);
    }
    server->anon_home = strdup(path);
    server->conn_list = NULL;
    server->conn_addr.sin_family = AF_INET;
    server->conn_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->conn_addr.sin_port = htons(port);
    if (bind(server->sd, (SA *)&server->conn_addr, (int)sizeof(SAIN)) < 0) {
        perror("bind failed");
        exit(84);
    }
    if (listen(server->sd, 3) < 0) {
        perror("listen");
        exit(84);
    }
}

void sig_handler(int sig)
{
    (void)sig;
    fprintf(stderr, "the signal number was %d", sig);
    write(2, "\nGoodbye!\n", 10);
    exit (0);
}

static int is_quit(char *buffer)
{
    char *command = strsep(&buffer, "\r\n");
    char **params = my_str_to_word_array(command);
    if (!strcmp("QUIT", params[0]) && params[1] == NULL)
        return (1);
    return (0);
}

void server_run(int port, char *path)
{
    server_t *server = malloc(sizeof(server_t));
    serv_init(server, port, path);
    SS rem_addr;
    int ns = -1;
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, sig_handler);
    signal(SIGTERM, sig_handler);
    char buffer[MAXLINE];
    //int adlen = sizeof(SA);
    socklen_t  adlen;
    fd_set master_socks;
    fd_set ready_socks;
    fd_set writy_socks;
    FD_ZERO(&master_socks);
    FD_ZERO(&ready_socks);
    FD_ZERO(&writy_socks);
    FD_SET(server->sd, &master_socks);
    int sel = 0;
    int fd_max = server->sd;
    //memset(buffer, 0, MAXLINE);

    while (TRUE) {
        ready_socks = master_socks;
        writy_socks = master_socks;
        if (select(fd_max + 1, &ready_socks, &writy_socks, NULL, NULL) < 0) {
            perror ("select error");
            exit (84);
        }
        for (int i = 3; i < (fd_max + 1); i++) {
            if (FD_ISSET(i, &ready_socks)) {
                if (i == server->sd) {
                    ns = accept(server->sd, (SA *)&rem_addr, &adlen);
                    add_client(server, ns, rem_addr, adlen);
                    FD_SET(ns, &master_socks);
                    if (ns > fd_max)
                        fd_max = ns;
                    write(ns, "220 Welcome! Service ready\r\n", 28);
                } else {
                    get_input(get_client_by_sd(i, server->conn_list), server, &master_socks, &writy_socks);
                }
            }
        }
    }
}

