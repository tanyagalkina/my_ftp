/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/commands.h"

void user(client_t *client, char **args)
{
    write (1, "I am user_cmd\n", 14);

}
void pass(client_t *client, char **args)
{
    write (1, "I am pass_cmd\n", 14);

}
void cwd(client_t *client, char **args)
{
    write (1, "I am cwd_cmd\n", 14);

}

void cdup(client_t *client, char **args)
{
    write (1, "I am cdup_cmd\n", 14);

}
void quit(client_t *client, char **args){}
void dele(client_t *client, char **args){}
void pwd(client_t *client, char **args){}
void pasv(client_t *client, char **args){}
void port(client_t *client, char **args){}
void help(client_t *client, char **args)
{}
void noop(client_t *client, char **args){}
void retr(client_t *client, char **args){}
void stor(client_t *client, char **args){}
void list(client_t *client, char **args){}


