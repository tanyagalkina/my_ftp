/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"
#include "../include/commands.h"


static int		create_passive_socket(unsigned int ip)
{
    int			passive_socket;
    struct sockaddr_in	sps;

    if ((passive_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return (-1);
    sps.sin_family = AF_INET;
    sps.sin_addr.s_addr = ip;
    sps.sin_port = 0;
    if (bind(passive_socket, (struct sockaddr *)&sps, sizeof(sps)) == -1 ||
        listen(passive_socket, 10) == -1)
        return (-1);
    return (passive_socket);
}

void pasv(client_t *client, char **args, server_t *server)
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

    char			msg[1024];
    struct in_addr	ip_addr;


    if ((client->transfd = create_passive_socket(client->ip)) == -1) {
        write(client->userfd, "550 Unable to enter in passive mode.\r\n", 38);
    }
    ip_addr.s_addr = client->ip;
    sprintf(msg, "Entering passive mode (%s).", inet_ntoa(ip_addr));
    client->pasv = true;
    write(client->userfd, "227, msg\r\n", sizeof(msg + 7));

}

