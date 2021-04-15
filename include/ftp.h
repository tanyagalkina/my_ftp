/*
** EPITECH PROJECT, 2020
** NWP, myftp
** File description:
** src
*/

#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

void server_run(int port, char *path);