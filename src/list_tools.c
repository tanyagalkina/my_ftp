/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"

void remove_from_list(client_t *tmp, server_t *server)
{
    if (tmp->prev == NULL && tmp->next == NULL) {
        server->conn_list = NULL;
        return;
    } else if (tmp->prev == NULL && tmp->next != NULL) {
        server->conn_list = tmp->next;
        server->conn_list->prev = NULL;
    } else if (tmp->prev && tmp->next) {
        tmp->next->prev = tmp->prev;
    }
    if (tmp->next == NULL) {
        tmp->prev->next = NULL;
        tmp = NULL;
    }
}

void add_to_list(server_t *server, client_t *new_cl)
{
    client_t *tmp;

    if (server->conn_list == NULL)
        server->conn_list = new_cl;
    else {
        tmp = server->conn_list;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        new_cl->prev = tmp;
        tmp->next = new_cl;
    }
}

void show_list(client_t *cl_list)
{
    client_t *tmp = cl_list;
    int count = 0;
    if (!tmp)
        fprintf(stderr, "We dont have any connected clients at the moment\n");
    while (tmp != NULL) {
        fprintf(stderr, "we have %d\n", tmp->userfd);
        tmp = tmp->next;
    }
    tmp = cl_list;
    while (tmp != NULL) {
        count++;
        tmp = tmp->next;
    }
    printf("We have %d connections now\n", count);
}