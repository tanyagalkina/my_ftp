/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"
#include "../include/commands.h"

void remove_from_list(client_t *tmp, server_t *server)
{
    printf("REMOVE %d\n", tmp->userfd);
    if (tmp->prev == NULL && tmp->next == NULL) {
        server->conn_list = NULL;
        return;
    }
    else if (tmp->prev == NULL && tmp->next != NULL)
    {
        server->conn_list = tmp->next;
       // server->conn_list->prev = NULL;

    }

    else if (tmp->prev && tmp->next)
    {
        tmp->next->prev = tmp->prev;
    }
    ///if it is the last node
    if (tmp->next == NULL) {
        tmp = NULL;
    }

}

static void show_list(client_t *cl_list)
{
    client_t *tmp = cl_list;
    if (!tmp)
        fprintf(stderr, "We dont have any connected clients at the moment\n");
    while(tmp != NULL)
    {
        fprintf(stderr, "we have %d\n", tmp->userfd);
        tmp = tmp->next;

    }

}

static void *get_in_addr(SA *sa)
{
    return &(((struct sockaddr_in*)sa)->sin_addr);
}

void add_client(server_t *server, int ns, SS rem_addr, socklen_t adlen)
{

    //char remoteIP[INET_ADDRSTRLEN];

    client_t *new_cl = malloc(sizeof(client_t));
    client_t *tmp = malloc(sizeof(client_t));
    new_cl->name = NULL;
    new_cl->auth = 0;
    new_cl->claddr = &rem_addr;
    new_cl->inc_file = NULL;
    new_cl->userfd = ns;
    new_cl->home = strdup(server->anon_home);
    int i = 0;
    while(server->anon_home[i]) {
        new_cl->curr_dir[i] = server->anon_home[i];
                ++i;
    }
    new_cl->curr_dir[i] = '\0';
    new_cl->next = NULL;
    new_cl->prev = NULL;
    new_cl->exit = false;
    new_cl->transfd = -1;
    new_cl->receiving = false;
    new_cl->pasv = false;

    fprintf(stderr, "selectserver: new connection from %s on socket %d\n", inet_ntop(rem_addr.ss_family,
                                                                            get_in_addr((struct sockaddr*)&rem_addr),
                                                                            new_cl->ip, INET_ADDRSTRLEN),
           ns);
    if (server->conn_list == NULL) {
        server->conn_list = new_cl;
        fprintf(stderr, "THIS IS OUR FIRST CLIENT %d\n", server->conn_list->userfd);
    }
    else {
        tmp = server->conn_list;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        new_cl->prev = tmp;
        tmp->next = new_cl;
    }
    show_list(server->conn_list);
}

void remove_client(int cd, server_t *server)
{
    struct client *tmp = server->conn_list;
    while (tmp != NULL)
    {
        if (tmp->userfd == cd)
            break;
        tmp = tmp->next;
    }
    remove_from_list(tmp, server);
    show_list(server->conn_list);
}
