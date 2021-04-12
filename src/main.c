/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"

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
    (void)envp;
    if (ac == 2 && !strcmp("-help", av[1])) {
        display_help();
        return (84);
    }
    if (ac != 3) {
        display_help();
        return (84);
    }

    return (0);
}
