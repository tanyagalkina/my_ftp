/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/commands.h"

void dele(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        return ((void)(write(client->userfd, "530 Not logged in.\r\n", 20)));
    }
    if (args[1] && !chdir(client->curr_dir) && remove(args[1]) == 0)
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

void help(client_t *cl, char **args, server_t *server)
{
    write(cl->userfd, "214 Commands implemented:\r\n", 27);
    write(cl->userfd, "USER PASS CWD CDUP QUIT\r\n", 25);
    write(cl->userfd, "DELE PWD PASV PORT HELP NOOP RETR STOR LIST\r\n", 45);
    write(cl->userfd, "214 Help.\r\n", 11);
}

void noop(client_t *client, char **args, server_t *server)
{
    write(client->userfd, "200 I am chilling, everything is fine!\r\n", 40);
}