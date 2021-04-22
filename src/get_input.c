/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include <signal.h>
#include "../include/ftp.h"
#include "../include/commands.h"

static int is_quit(char *buffer)
{
    if (!strcmp("QUIT", buffer))
        return (1);
    else
        return (0);
}

int get_input(client_t *client, server_t *server, fd_set *master_socks, fd_set *writy_socks)
{
    char buffer[MAXLINE] = {0};

    if (FD_ISSET(client->userfd, writy_socks) && 0 == read(client->userfd, &buffer, MAXLINE)){
        fprintf(stderr, "socket %d is gone... bye!\n", client->userfd);
        FD_CLR(client->userfd, master_socks);
        close(client->userfd);
        remove_client(client->userfd, server);
    }
    else {
        if (is_quit(buffer)) {
            quit(client, NULL, server);
            remove_client(client->userfd, server);
            close(client->userfd);
            FD_CLR(client->userfd, master_socks);
        }
        else {
            handle_cmd(server, client->userfd, buffer);
        }
        return (0);
    }
}


