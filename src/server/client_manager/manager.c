/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "server.h"
#include "debug.h"

void read_client(server_t *server, client_t *client)
{
	char buf[1025] = {0};
	ssize_t len = read(client->fd, buf, 1024);

	if (len < 1)
		disconnect(server, client);
	else
		debug(INFO "Client action\n");
}