/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"

void sig_handler(int sig)
{
    (void) sig;
    write(2, "\nGoodbye!\n", 10);
    exit(0);
}

void set_signals(void)
{
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, sig_handler);
    signal(SIGTERM, sig_handler);
}