/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"

void port(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
    if (!args[1])
        write(client->userfd, "500 Wrong PORT command\r\n", 24);
    else
        write(client->userfd, "200\r\n", 5);
}

