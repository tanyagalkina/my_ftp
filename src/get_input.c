/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"
#include "../include/commands.h"

static int is_quit(char *buffer)
{
    char **params = my_str_to_word_array(buffer);
    if (!params[0]) {
        return 2;
    }
    if (!strcmp("QUIT", params[0])) {
        return (1);
    } else
        return (0);
}

int get_input(client_t *cl, server_t *s)
{
    char buffer[MAXLINE] = {0};
    size_t r = 0;
    if (FD_ISSET(cl->userfd, &s->write) && 0 == \
read(cl->userfd, &buffer, MAXLINE)) {
        remove_client(cl->userfd, s);
        FD_CLR(cl->userfd, &s->master);
        close(cl->userfd);
        return (0);
    }
    else if (is_quit(buffer) == 1) {
        printf("I am quit\n");
        FD_CLR(cl->userfd, &s->master);
        quit(cl, NULL, s);
        return (0);
    }
    if (is_quit(buffer) == 2) {
        write(cl->userfd, "500 No command given\r\n", 22);
    } else
        handle_cmd(s, cl->userfd, buffer);
        return (0);
}