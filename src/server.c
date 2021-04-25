/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"
#include "../include/commands.h"

int get_socket(void)
{
    int opt = 1;
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(84);
    }
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, \
&opt, sizeof(opt))) {
        perror("setsockopt");
        exit(84);
    }
    return (sock);
}
void set_up_select(server_t *s)
{
    FD_ZERO(&s->master);
    FD_ZERO(&s->read);
    FD_ZERO(&s->write);
    FD_SET(s->sd, &s->master);
}

server_t *serv_init(int port, char *path)
{
    server_t *server = malloc(sizeof(server_t));
    server->sd = get_socket();
    server->anon_home = strdup(path);
    server->conn_list = NULL;
    server->conn_addr.sin_family = AF_INET;
    server->conn_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server->conn_addr.sin_port = htons(port);
    if (bind(server->sd, (SA *)&server->conn_addr, (int)sizeof(SAIN)) < 0) {
        perror("bind failed");
        exit(84);
    }
    if (listen(server->sd, 10) < 0) {
        perror("listen");
        exit(84);
    }
    set_signals();
    set_up_select(server);
    return server;
}

void server_run(int port, char *path, socklen_t adlen)
{
    server_t *s = serv_init(port, path);
    int fd_max = s->sd;
    SS rem_addr;
    int ns = -1;
    while (TRUE) {
        s->read = s->master;
        s->write = s->master;
        if (select(fd_max + 1, &s->read, &s->write, NULL, NULL) < 0)
            exit (84);
        for (int i = 3; i < (fd_max + 1); i++) {
            if (FD_ISSET(i, &s->read)) {
                if (i == s->sd) {
                    ns = accept(s->sd, (SA *)&rem_addr, &adlen);
                    add_client(s, ns, rem_addr, adlen);
                    FD_SET(ns, &s->master);
                    if (ns > fd_max)
                        fd_max = ns;
                    write(ns, "220 Welcome! Service ready\r\n", 28);
                } else {get_input(get_client_by_sd(i, s->conn_list), s);}}}}
}