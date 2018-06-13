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

int init_server(server_t *serv)
{
	serv->map.map = malloc(sizeof(entity_t *) * serv->map.size.y);
	if (!serv->map.map) {
		debug(ERROR "Map allocation failed\n");
		return 1;
	}
	for (size_t y = 0; y < serv->map.size.y; y++) {
		serv->map.map[y] = calloc(serv->map.size.x, sizeof(entity_t));
		if (!serv->map.map[y]) {
			debug(ERROR "Cannot allocate row %d in map\n", y);
			return 1;
		}
	}
	serv->map.max_id = 0;
	generate_map(&serv->map);
	print_map(&serv->map);
	create_teams_clients(serv);
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