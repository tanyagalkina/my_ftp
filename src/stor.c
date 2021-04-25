/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/commands.h"

void stor(client_t *client, char **args, server_t *server)
{
    if (client->auth == false) {
        write(client->userfd, "530 Not logged in.\r\n", 20);
        return;
    }
}