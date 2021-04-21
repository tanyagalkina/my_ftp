/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include <curses.h>
#include "../include/commands.h"

void user(client_t *client, char **args, server_t *server)
{
    if (client->auth) {
        write(client->userfd, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    if (args[1] && !strcmp("Anonymous", args[1])) {
        client->name = strdup(args[1]);
        write(client->userfd, "331 Username OK, need password\r\n", 32);
    } else {
        write(client->userfd, "430 Invalid username or password\r\n", 34);
    }
}

void pass(client_t *client, char **args, server_t *server)
{
    if (!args[1]) {
        write(client->userfd, "230 User logged in.\r\n", 21);
        client->auth = TRUE;
        return;
    }
    write(client->userfd, "430 Invalid username or password\r\n", 34);
}

void cwd(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    if (args[1] && !chdir(args[1])) {
        write(client->userfd, "250 Requested file action okay, completed\r\n", 43);
        getcwd(client->curr_dir, PATH_MAX);
    }
    else
        write(client->userfd, NOT_TAKEN, sizeof(NOT_TAKEN));
}

void cdup(client_t *client, char **args, server_t *server)
{
    if (client->auth == false)
        write(client->userfd, "530 Not logged in.\r\n", 20);
    if (!chdir(client->curr_dir) && !chdir("..")) {
        write(client->userfd, "250 Requested file action okay, completed\r\n", 43);
        getcwd(client->curr_dir, PATH_MAX);
    } else
        write(client->userfd, NOT_TAKEN, sizeof(NOT_TAKEN));
}

void quit(client_t *client, char **args, server_t *server)
{
    if (client->receiving)
    {
        write(client->userfd, "232 Logout command noted, will complete when transfer done.\r\n", 61);
        client->exit = true;
        return;
    }
    write(client->userfd, "231 User logged out; service terminated\r\n", 41);
    close(client->userfd);
    remove_from_list(client, server);
}

void dele(client_t *client, char **args, server_t *server)
{
    if (client->auth == false)
        write(client->userfd, "530 Not logged in.\r\n", 20);
}

void pwd(client_t *client, char **args, server_t *server)
{
    if (client->auth == false)
        write(client->userfd, "530 Not logged in.\r\n", 20);
}

void pasv(client_t *client, char **args, server_t *server)
{
    if (client->auth == false)
        write(client->userfd, "530 Not logged in.\r\n", 20);
}

void port(client_t *client, char **args, server_t *server)
{
    if (client->auth == false)
        write(client->userfd, "530 Not logged in.\r\n", 20);
}

void help(client_t *client, char **args, server_t *server)
{
    write(client->userfd, HELP, sizeof(HELP));
}

void noop(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
    }
}

void retr(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
}

void stor(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
}

void list(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
}


