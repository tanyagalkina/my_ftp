/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"
#include "../include/commands.h"

static int do_pasv(server_t *server, client_t *client)
{
    SAIN dataddr;
    socklen_t size = sizeof(dataddr);

    if ((client->transfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (-1);
    dataddr.sin_family = AF_INET;
    dataddr.sin_addr.s_addr = htonl(INADDR_ANY);
    dataddr.sin_port = htons(0);
    if (bind(client->transfd, (SA *)&dataddr, sizeof(dataddr)) == -1 ||
        listen(client->transfd, 10) == -1)
        return (-1);
    if (getsockname(client->transfd, (SA *)&dataddr, &size) == -1)
        return (-1);
    client->pasv = true;
    client->p_port = ntohs(dataddr.sin_port);
    return (0);
}

void pasv(client_t *client, char **args, server_t *server)
{
    int i = 0;
    if (client->auth = false)
        return ((void)write(client->userfd, "530 Not logged in.\r\n", 20));
    if (do_pasv(server, client) == -1)
        write(client->userfd, "550 Unable to enter in passive mode.\r\n", 38);
    else {
        write(client->userfd, "227 Entering Passive Mode (", 27);
        char **my_ip = my_str_to_word_array(client->ip);
        while (my_ip[i]) {
            dprintf(client->userfd, "%s,", my_ip[i]);
            ++i;
        }
        dprintf(client->userfd, "%d,%d).\r\n", client->p_port / 256, \
client->p_port % 256);
    }
}