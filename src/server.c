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

void serv_init(server_t *server, int port)
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
    server->addr.sin_family = AF_INET;
    server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->addr.sin_port = htons(port);
    if (bind(server->sd, (SA *)&server->addr, (int)sizeof(SAIN)) < 0) {
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

static void handle_connection(int fd)
{
    write(fd, "Hello\n", 6);
    close(fd);
}

void *get_in_addr(SA *sa)
{
    return &(((struct sockaddr_in*)sa)->sin_addr);
}

void server_run(int port, char *path)
{
    server_t *server = malloc(sizeof(server_t));
    serv_init(server, port);
    SS rem_addr;
    char remoteIP[INET_ADDRSTRLEN];
    int ns = -1;
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, sig_handler);
    signal(SIGTERM, sig_handler);
    char buffer[2048] = {0};
    server->anon_home = path;
    //int adlen = sizeof(SA);
    socklen_t  adlen;
    fd_set master_socks;
    fd_set ready_socks;
    fd_set writy_socks;
    FD_ZERO(&master_socks);
    FD_ZERO(&ready_socks);
    FD_ZERO(&writy_socks);
    FD_SET(server->sd, &master_socks);
    //FD_SET(0, &master_socks);
    int sel = 0;
    int fd_max = server->sd;

    int conn_fds[100] = {0};

    while (TRUE) {
        ready_socks = master_socks;
        writy_socks = master_socks;
        if (select(fd_max + 1, &ready_socks, &writy_socks, NULL, NULL) < 0) {
            perror ("select error");
            exit (84);
        }
        for (int i = 0; i < (fd_max + 1); i++) {
            if (FD_ISSET(i, &ready_socks)) {
                ///if the listener has something to read...
                if (i == server->sd) {
                    ns = accept(server->sd, (SA *)&rem_addr, &adlen);
                    FD_SET(ns, &master_socks);
                    if (ns > fd_max)
                        fd_max = ns;
                    printf("selectserver: new connection from %s on socket %d\n", inet_ntop(rem_addr.ss_family,
                              get_in_addr((struct sockaddr*)&rem_addr),
                              remoteIP, INET_ADDRSTRLEN),
                            ns);
                    write(ns, "220 Service ready\r\n", 19);
                } else {
                    if (0 == read(i, buffer, MAXLINE) && FD_ISSET(i, &writy_socks)) {
                        printf("socket %d is gone... bye!\n", i);
                        close(i);
                        FD_CLR(i, &master_socks);
                    }
                    else {
                        printf("command got is: %s\n", buffer);
                        //if (strstr("USER", buffer))
                        write(i, "331 \r\n", 6);

                        //else
                        //    write(ns, "230 \r\n", 6);

                    }
                }
            }
            memset(buffer, 0, MAXLINE);
        }
    }
}

