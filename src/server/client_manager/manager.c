/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <server.h>
#include <string.h>
#include "server.h"
#include "debug.h"

void init_client(server_t *server, client_t *client)
{
	srand(time(NULL));
	client->fd = i_socket_accept(server->fd);
	if (client->fd != SOCKET_ERROR) {
		client->user.x = rand() % server->map.size.x;
		client->user.y = rand() % server->map.size.y;
		client->user.level = 1;
		client->user.vision = 1;
		memset(client->user.bag, 0, sizeof(uint) * 7);
		debug(INFO "New client on fd %i\n", client->fd);
		server->client_nb++;
	}
	debug_if(client->fd == SOCKET_ERROR, ERROR "Accept error\n");
}

void read_client(server_t *server, client_t *client)
{
	char *request = gnl(client->fd, "\n");

	if (!request)
		disconnect(server, client);
	else {
		debug(INFO "Client request : %s\n", request);
		free(request);
	}
}