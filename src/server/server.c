/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <poll.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <server.h>
#include "socket.h"
#include "debug.h"
#include "server.h"
#include "scheduler.h"

static int init_server(server_t *serv)
{
	init_map(&serv->map);
	if (!serv->map.map)
		return 1;
	create_teams_clients(serv);
	return 0;
}

int server(server_t *server)
{
	int end = EXIT_SUCCESS;

	server->fd = i_socket((uint16_t) server->port);
	if (server->fd == SOCKET_ERROR) {
		fprintf(stderr, "Can't create server on port: %i\n",
			server->port);
		return EXIT_FAILURE;
	}
	debug(GINFO "Server started on 127.0.0.1:" CYAN "%i" RESET"\n",
		server->port);
	if (init_server(server) != 0)
		return EXIT_FAILURE;
	while (end == EXIT_SUCCESS) {
		server_loop(server);
		scheduler(server);
	}
	close(server->fd);
	return 0;
}

void destroy_server(server_t *server)
{
	for (teams_t *team = server->teams; team;) {
		teams_t *tmp = team;
		team = team->next;
		free(tmp->name);
		free(tmp);
	}
}