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
    void (*func)(client_t *, char **, server_t *);
}cmd_t;

void user(client_t *, char **, server_t *);
void pass(client_t *, char **, server_t *);
void cwd(client_t *, char **, server_t *);
void cdup(client_t *, char **, server_t *);
void quit(client_t *, char **, server_t *);
void dele(client_t *, char **, server_t *);
void pwd(client_t *, char **, server_t *);
void pasv(client_t *, char **, server_t *);
void port(client_t *, char **,server_t *);
void help(client_t *, char **, server_t *);
void noop(client_t *, char **, server_t *);
void retr(client_t *, char **, server_t *);
void stor(client_t *, char **, server_t *);
void list(client_t *, char **, server_t *);

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
        {NULL, NULL}
};

void handle_cmd(server_t *server, int sd, char *buffer);
char **my_str_to_word_array(char const *str);
int my_str_isprintable(char const *str);

#endif //FTP_COMMANDS_H
