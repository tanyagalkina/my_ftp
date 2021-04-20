/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** header
*/

#ifndef FTP_COMMANDS_H
#define FTP_COMMANDS_H

#include "ftp.h"

typedef struct cmd
{
    char *cmd;
    void (*func)(client_t *, char **);
}cmd_t;
void user(client_t *, char **);
void pass(client_t *, char **);
void cwd(client_t *, char **);
void cdup(client_t *, char **);
void quit(client_t *, char **);
void dele(client_t *, char **);
void pwd(client_t *, char **);
void pasv(client_t *, char **);
void port(client_t *, char **);
void help(client_t *, char **);
void noop(client_t *, char **);
void retr(client_t *, char **);
void stor(client_t *, char **);
void list(client_t *, char **);

static const cmd_t cmd_table[] = {
        {"USER", &user},
        {"PASS",&pass},
        {"CWD", &cwd},
        {"CDUP", &cdup},
        {"QUIT", &quit},
        {"DELE", &dele},
        {"PWD", &pwd},
        {"PASV", &pasv},
        {"PORT", &port},
        {"HELP", &help},
        {"NOOP", &noop},
        {"RETR", &retr},
        {"STOR", &stor},
        {"LIST", &list},
        NULL
};




#endif //FTP_COMMANDS_H
