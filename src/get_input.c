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
    char **params = my_str_to_word_array(buffer);
    if (!params[0]) {
        printf("I dont have any command\n");
        for (int i = 0; i < MAXLINE; ++i)
            buffer[i] = '\0';
        return 2;
    }
    if (!strcmp("QUIT", params[0])) {
        for (int i = 0; i < MAXLINE; ++i)
            buffer[i] = '\0';
        return (1);
    } else
        return (0);
}

int get_input(client_t *client, server_t *server, fd_set *master_socks, fd_set *writy_socks)
{
    char buffer[MAXLINE] = {0};
    size_t r = 0;
    if (FD_ISSET(client->userfd, writy_socks))
        r = read(client->userfd, &buffer, MAXLINE);
    if (
            r == 0)

            //FD_ISSET(client->userfd, writy_socks) && 0 == read(client->userfd, &buffer, MAXLINE))
            {
        remove_client(client->userfd, server);
        fprintf(stderr, "socket %d is gone... bye!\n", client->userfd);
        FD_CLR(client->userfd, master_socks);
        close(client->userfd);
    }
    else if (is_quit(buffer) == 1) {
            for (int i = 0; i < MAXLINE; ++i)
            {
                buffer[i] = '\0';
            }
            FD_CLR(client->userfd, master_socks);
            quit(client, NULL, server);
        }
    else if (is_quit(buffer) == 2) {
        write(client->userfd, "500 No command given\r\n", 22);
    }



        else {
        printf ("I have read %zu bytes cmd\n", r);
            handle_cmd(server, client->userfd, buffer);
        }
        return (0);
}


