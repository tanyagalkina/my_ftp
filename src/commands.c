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
        write(client->userfd, "250 Requested file action okay, completed\r\n", 43);
        getcwd(client->curr_dir, PATH_MAX);
        printf("this is clients curdir %s\n", client->curr_dir);
    } else write(client->userfd, "550\r\n", 5);
}

void cdup(client_t *client, char **args, server_t *server)
{
    printf("The currend dir is: %s", client->curr_dir);
    int i = strlen(client->curr_dir);
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    while (client->curr_dir[i] != '/') {
        --i;
    }
    client->curr_dir[i] = '\0';

    if (!chdir(client->curr_dir)) {
        write(client->userfd, "200 Requested file action okay, completed\r\n", 43);
        getcwd(client->curr_dir, PATH_MAX);
        //printf("curr_dir len: %d\n", strlen(client->curr_dir));
        //printf("The dir after CDUP is %s\n", client->curr_dir);
    } else
        write(client->userfd, "550\r\n", 5);
}

void quit(client_t *client, char **args, server_t *server)
{
    write(client->userfd, "221 See you later!\r\n", 20);
    close(client->userfd);
    remove_client(client->userfd, server);
}

void dele(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        return ((void)(write(client->userfd, "530 Not logged in.\r\n", 20)));
        return;
    }
    else if (args[1] && remove(args[1]) == 0)
        write(client->userfd, "250 file deleted\r\n", 18);
    else
        write(client->userfd, "550\r\n", 5);
}

void pwd(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    write(client->userfd, "257 ", 4);
    write(client->userfd, &client->curr_dir, sizeof(client->curr_dir));
    write(client->userfd, "\r\n", 2);
}

/*void port(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    if (!args[1])
        write(client->userfd, "500 Wrong PORT command\r\n", 24);
    else
        write(client->userfd, "200\r\n", 5);
}*/

void help(client_t *client, char **args, server_t *server)
{
    write(client->userfd, "214 The following commands are implemented:\r\n", 45);
    write(client->userfd, "USER PASS CWD CDUP QUIT\r\n", 25);
    write(client->userfd, "DELE PWD PASV PORT HELP NOOP RETR STOR LIST\r\n", 45);
    write(client->userfd, "214 Help.\r\n", 11);
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
        return ((void)write(client->userfd, "530 Not logged in.\r\n", 20));
    }
    if (client->transfd < 0) {
        write(client->userfd, "425 No data connection.\r\n", 25);
    }
}