/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include <signal.h>
#include "../include/ftp.h"
#include "../include/commands.h"


static char	**get_splitted_command(const char *command)
{
    int		n;
    char		*splitter;
    char		**splitted_command;

    n = 0;
    splitter = strtok((char *)command, " ");
    splitted_command = NULL;
    while (splitter)
    {
        if ((splitted_command = \
	   realloc(splitted_command, sizeof(char *) * ++n)) == NULL)
            return (NULL);
        splitted_command[n - 1] = splitter;
        splitter = strtok(NULL, " ");
    }
    splitted_command = realloc(splitted_command, sizeof(char *) * (n + 1));
    splitted_command[n] = 0;
    return (splitted_command);
}

const char	*get_input_command(int fd)
{
    char		*command;

    if ((command = get_next_line(fd)) == NULL)
        return (NULL);
    if (command[strlen(command) - 1] == '\r')
        command[strlen(command) - 1] = 0;
    return ((const char *)command);
}

static int is_quit(char *buffer)
{
    if (!strcmp("QUIT", buffer))
        return (1);
    else
        return (0);
}

int get_input(client_t *client, server_t *server, fd_set *master_socks, fd_set *writy_socks)
{
    char buffer[MAXLINE] = {0};

    //char	*command;
    //char	**splitted_command;
    if (FD_ISSET(client->userfd, writy_socks) && 0 == read(client->userfd, &buffer, MAXLINE)){
        fprintf(stderr, "socket %d is gone... bye!\n", client->userfd);
        FD_CLR(client->userfd, master_socks);
        close(client->userfd);
        remove_client(client->userfd, server);
    //while ((command = (char *)get_input_command(client->userfd)) != NULL \
	 //&& strcmp("QUIT", command)
        //   && (splitted_command = get_splitted_command(command)) != NULL) {
        //if (!strcmp("", command)) =
          //  continue;
        //splitted_command = get_splitted_command(buffer);
        //printf("Client %s send: \"%s\"\n", client->name, command);
        //free(splitted_command);
        //free(command);
    }
    else {
        //printf("this is buffer: %s\n", buffer);
        if (is_quit(buffer)) {
            //printf("command got is: %s\n", buffer);
            //write(client->userfd, "221 \r\n", 6);
            quit(client, NULL, server);
            remove_client(client->userfd, server);
            close(client->userfd);
            FD_CLR(client->userfd, master_socks);

            //printf("I am here1");
        }
        else {
            handle_cmd(server, client->userfd, buffer);
            //handle_cmd(server, client->userfd, buffer);
        }
        return (0);
    }


    /*printf("I am get input\n");
    char buffer[MAXLINE];
    int sd = client->userfd;

    if (FD_ISSET(sd, writy_socks) && 0 == read(sd, &buffer, MAXLINE)) {
        //!strcmp("EXIT\n", buffer) && FD_ISSET(i, &writy_socks))
        fprintf(stderr, "socket %d is gone... bye!\n", sd);
        FD_CLR(sd, master_socks);
        close(sd);
        remove_client(sd, server);
    } else {
        if (is_quit(buffer)) {
            handle_cmd(server, sd, buffer);

            printf("I am here1");
            FD_CLR(sd, master_socks);
        } else
            printf("command got is: %s\n", buffer);
            handle_cmd(server, sd, buffer);
        return (0);
    }*/
}


