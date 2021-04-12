/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"

int correct_args(char **av)
{
    if (atoi(av[1]) > 65353) {
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
    if (correct_args(av))
        //ret = server_run(av);
        printf("Is not implemented yes, give me some time\n");
    else
        ret = 84;
    return (ret);
}
