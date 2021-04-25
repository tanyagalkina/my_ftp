/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/commands.h"

void list(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        return ((void)write(client->userfd, "530 Not logged in.\r\n", 20));
    }
    if (client->transfd < 0) {
        write(client->userfd, "425 No data connection.\r\n", 25);
    }
}