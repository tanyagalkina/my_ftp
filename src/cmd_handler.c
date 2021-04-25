/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#include "../include/ftp.h"
#include "../include/commands.h"

client_t *get_client_by_sd(int sd, client_t *list)
{
    client_t *tmp = list;
    while (tmp != NULL) {
        if (tmp->userfd == sd)
            return tmp;
        tmp = tmp->next;
    }
}

void handle_cmd(server_t *server, int sd, char *buffer)
{
    client_t *client = get_client_by_sd(sd, server->conn_list);
    int i = 0;
    char **params = my_str_to_word_array(buffer);
    if (!my_str_isprintable(params[0])) {
        write(sd, "500 Syntax error in parameters or arguments.\r\n", 46);
        return;
    }
    while (cmd_table[i].cmd != NULL) {
        if (!strcmp(cmd_table[i].cmd, params[0])) {
            cmd_table[i].func(client, params, server);
            break;
        }
        ++i;
    }
    if (i == 14)
        write(client->userfd, "500 Bad command.\r\n", 18);
}