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

void create_teams_clients(server_t *server)
{
	for (teams_t *team = server->teams; team; team = team->next) {
		team->remaining_place = server->max_clients_per_teams;
		team->client_max = server->max_clients_per_teams;
		team->clients = calloc(server->max_clients_per_teams,
			sizeof(client_t *));
		debug(GINFO "Team '%s' created\n", team->name);
	}
}

static int init_server(server_t *server)
{
	init_map(&server->map);
	if (!server->map.map)
		return 1;
	create_teams_clients(server);
	server->gui.queue = calloc(GUI_QUEUE_SIZE, 1);
	server->gui.size = GUI_QUEUE_SIZE;
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