/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/commands.h"

void user(client_t *client, char **args, server_t *server)
{
    if (client->auth) {
        write(client->userfd, "230 User logged in, proceed.\r\n", 30);
        return;
    }
    if (args[1])
        client->name = strdup(args[1]);
    write(client->userfd, "331 Username OK, need password\r\n", 32);
}

void pass(client_t *client, char **args, server_t *server)
{
    if (!args[1] && client->name && !strcmp("Anonymous", client->name)) {
        write(client->userfd, "230 User logged in.\r\n", 21);
        client->auth = TRUE;
        return;
    }
    write(client->userfd, "530 (430)? Invalid username or password\r\n", 41);
}

void cwd(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    if (args[1] && !chdir(client->curr_dir) && !chdir(args[1])) {
        write(client->userfd, "250 Requested file action okay.\r\n", 33);
        getcwd(client->curr_dir, PATH_MAX);
        printf("this is clients curdir %s\n", client->curr_dir);
    } else write(client->userfd, "550\r\n", 5);
}

void cdup(client_t *client, char **args, server_t *server)
{
    int i = strlen(client->curr_dir);
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    while (client->curr_dir[i] != '/')
        --i;
    client->curr_dir[i] = '\0';
    if (!chdir(client->curr_dir)) {
        write(client->userfd, "200 Requested file action okay.\r\n", 33);
        getcwd(client->curr_dir, PATH_MAX);
    } else
        write(client->userfd, "550\r\n", 5);
}

void quit(client_t *client, char **args, server_t *server)
{
    write(client->userfd, "221 See you later!\r\n", 20);
    client->auth = false;
    remove_client(client->userfd, server);
}