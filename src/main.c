/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"

static int is_valid_port(char *av)
{
    int pid = atoi(av);
    int num_length = 0;

    while (pid) {
        num_length++;
        pid /= 10;
    }
    if (atoi(av) < 0 || atoi(av) > 65353 || strlen(av) != (size_t)num_length) {
        fprintf(stderr, "port number is invalid\n");
        return (0);
    }
    return (1);
}

static void display_help()
{
    printf("USAGE: ./myftp port path\n");
    printf("      port  is the port number on which the server socket "
"listens\n");
    printf("      path  is the path to the home directory for "
"the Anonymous user\n");
}

int main(int ac, char **av,char **envp)
{
    int ret = 0;
    (void)envp;
    if (ac == 2 && !strcmp("-help", av[1])) {
        display_help();
        return (84);
    }
    if (ac != 3) {
        display_help();
        return (84);
    }
    if (is_valid_port(av[1]))
        server_run(atoi(av[1]), av[2]);
    else
        ret = 84;
    return (ret);
}