/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include <signal.h>
#include <bits/signum.h>
#include "../include/ftp.h"

void sig_handler(int sig)
{
    (void)sig;
    write(2, "\nGoodbye!\n", 10);
    exit (0);
}

void server_run(int port, char *path)
{
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, sig_handler);
    signal(SIGTERM, sig_handler);
    (void)path;
    int server_fd;
    int new_socket;
    SA address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "220 SSL/TLS Welcome\r\n";

// Creating socket file descriptor
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
{
perror("socket failed");
exit(EXIT_FAILURE);
}

// Forcefully attaching socket to the port 8080
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
&opt, sizeof(opt)))
{
perror("setsockopt");
exit(EXIT_FAILURE);
}

address.sin_family = AF_INET;
address.sin_addr.s_addr = htonl(INADDR_ANY);
address.sin_port = htons(port);
    if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        exit (-1);
    }

// Forcefully attaching socket to the port 8080
if (bind(server_fd, (struct sockaddr *)&address,
sizeof(address))<0)
{
perror("bind failed");
exit(EXIT_FAILURE);
}
if (listen(server_fd, 3) < 0)
{
perror("listen");
exit(EXIT_FAILURE);
}
if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                         (socklen_t*)&addrlen))<0)
{
perror("accept");
exit(EXIT_FAILURE);
}
else
    send(new_socket, hello, strlen(hello), 0);
while (1) {
read(new_socket, buffer, 1024);
printf("%s\n", buffer);
send(new_socket, hello, strlen(hello), 0);
printf("Hello message sent\n");
}
}

