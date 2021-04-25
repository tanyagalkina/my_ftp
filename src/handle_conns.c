/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"

static void *get_in_addr(SA *sa)
{
    return &(((struct sockaddr_in *)sa)->sin_addr);
}

static void print_welcome(SS rem_addr, client_t *new_cl, int ns)
{
    char *adr = inet_ntop(rem_addr.ss_family, \
get_in_addr((struct sockaddr *)&rem_addr), \
new_cl->ip, INET_ADDRSTRLEN);
    fprintf(stderr, "new conn from %s on socket %d\n", adr, ns);
    new_cl->strip = strdup(adr);
}

client_init_aid(client_t *new_cl, server_t *s)
{
    int i = 0;

    new_cl->name = NULL;
    new_cl->auth = false;
    new_cl->inc_file = NULL;
    new_cl->next = NULL;
    new_cl->prev = NULL;
    new_cl->exit = false;
    new_cl->transfd = -1;
    new_cl->receiving = false;
    new_cl->pasv = false;
    new_cl->home = strdup(s->anon_home);
    while (s->anon_home[i]) {
        new_cl->curr_dir[i] = s->anon_home[i];
        ++i;
    }
    new_cl->curr_dir[i] = '\0';
}

void add_client(server_t *server, int ns, SS rem_addr, socklen_t adlen)
{
    client_t *new_cl = malloc(sizeof(client_t));
    client_init_aid(new_cl, server);
    new_cl->userfd = ns;
    new_cl->in_adr = &rem_addr;
    new_cl->addr = (SA *)&rem_addr;
    print_welcome(rem_addr, new_cl, ns);
    add_to_list(server, new_cl);
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