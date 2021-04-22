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
    fprintf(stderr, "I am user cmd\n");
    if (client->auth) {
        write(client->userfd, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    client->name = strdup(args[1]);
    write(client->userfd, "331 Username OK, need password\r\n", 32);

    /*if (!args[1])
        write(client->userfd, "430 Invalid username or password\r\n", 34);

    if (args[1] && !strcmp("Anonymous", args[1])) {
        client->name = strdup(args[1]);
        write(client->userfd, "331 Username OK, need password\r\n", 32);
    } else {
        write(client->userfd, "430 Invalid username or password\r\n", 34);
    }*/
}

void pass(client_t *client, char **args, server_t *server)
{
    printf("PASS\n");
    if (!args[1] && client->name && !strcmp("Anonymous", client->name)) {
        write(client->userfd, "230 User logged in.\r\n", 21);
        client->auth = TRUE;
        return;
    }
    write(client->userfd, "430 Invalid username or password\r\n", 34);
}

void cwd(client_t *client, char **args, server_t *server)
{
    printf("this is requested dir %s\n", args[1]);
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
        if (args[1] && !chdir(client->curr_dir) && !chdir(args[1])) {
            write(client->userfd, "250 Requested file action okay, completed\r\n", 43);
            getcwd(client->curr_dir, PATH_MAX);
            printf("this is clients curdir %s\n", client->curr_dir);

        } else write(client->userfd, NOT_TAKEN, sizeof(NOT_TAKEN));
}

void cdup(client_t *client, char **args, server_t *server)
{

    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }

    int i = strlen(client->curr_dir);
    while (client->curr_dir[i] != '/') {
        --i;
    }
    client->curr_dir[i] = '\0';
    args[1] = strdup(client->curr_dir);
    cwd(client, args, server);

    if (!chdir(client->curr_dir) && !chdir("..")) {
        write(client->userfd, "250 Requested file action okay, completed\r\n", 43);
        getcwd(client->curr_dir, PATH_MAX);
    } else
        write(client->userfd, NOT_TAKEN, sizeof(NOT_TAKEN));
}

void quit(client_t *client, char **args, server_t *server)
{
    printf(" I am quit\n");
    printf("The file descriptor is %d", client->userfd);
    if (client->receiving)
    {
        write(client->userfd, "232 Logout command noted, will complete when transfer done.\r\n", 61);
        client->exit = true;
        return;
    }
    write(client->userfd, "231 User logged out; service terminated\r\n", 47);
    //close(client->userfd);
    //remove_from_list(client, server);
}

void dele(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
}

void pwd(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }

}

/*void pasv(client_t *client, char **args, server_t *server)
{
    if (client->transfd)
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    if (client->transfd != -1) {
        write(client->userfd, "225 Data connection open; no transfer in progress.\r\n", 52);
        return;
    }
}*/

void port(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    if (client->transfd != -1) {
        write(client->userfd, "225 Data connection open; no transfer in progress.\r\n", 52);
        return;
    }
}

void help(client_t *client, char **args, server_t *server)
{
    write(client->userfd, HELP, sizeof(HELP));
}

void noop(client_t *client, char **args, server_t *server)
{
    write(client->userfd, "200 I am chilling, everything is fine!\r\n", 40);
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