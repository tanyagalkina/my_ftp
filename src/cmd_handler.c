/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"
#include "../include/commands.h"

static client_t *get_client_by_sd(int sd, client_t *list)
{
    client_t *tmp = list;
    while(tmp != NULL)
    {
        if (tmp->userfd == sd)
            return tmp;
        tmp = tmp->next;
    }
}

void handle_cmd(server_t *server, int sd, char *buffer)
{
    char *cmd;
    client_t *client = get_client_by_sd(sd, server->conn_list);
    int i = 0;
    char *command = strsep(&buffer, "\r\n");
    char **params = my_str_to_word_array(command);
    if (!my_str_isprintable(params[0])) {
        write(sd, "501 Syntax error in parameters or arguments.\r\n", 46);
        return;
    }
    fprintf(stderr, "command got is: %s\n", command);
    fprintf(stderr, "user with sd %d says %s with arg %s\n", sd, params[0], params[1]);

    while (cmd_table[i].cmd != NULL)
    {
        if (!strcmp(cmd_table[i].cmd, params[0]))
            cmd_table[i].func(client, params, server);
        ++i;
    }

}
