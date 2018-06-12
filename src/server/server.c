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

static void server_accept(server_t *server)
{
	client_t *new = malloc(sizeof(client_t));

	if (!new) {
		debug(ERROR "can't create user (malloc failed)\n");
		return;
	}
	new->prev = NULL;
	if (server->clients) {
		new->next = server->clients;
		new->next->prev = new;
	} else
		new->next = NULL;
	server->clients = new;
	new->user = (user_t){0};
	new->fd = i_socket_accept(server->fd);
	if (new->fd != SOCKET_ERROR) {
		debug(INFO "New client on fd %i\n", new->fd);
		server->client_nb++;
	}
	debug_if(new->fd == SOCKET_ERROR, ERROR "accept error\n");
}

struct pollfd *build_poll_fds(server_t *server)
{
	struct pollfd *fds = malloc(sizeof(struct pollfd) *
		(server->client_nb + 1));
	size_t i = 0;

	if (!fds) {
		debug(ERROR "can't create pollfd struct\n");
		return (NULL);
	}
	for (client_t *clt = server->clients; clt != NULL; clt = clt->next) {
		fds[i] = (struct pollfd){clt->fd, POLLIN | POLLOUT, 0};
		++i;
	}
	fds[i] = (struct pollfd){server->fd, POLLIN, 0};
	return fds;
}

static void handle_poll(struct pollfd *fds, server_t *server)
{
	client_t *next = NULL;
	int i = 0;

	for (client_t *clt = server->clients; clt != NULL;) {
		next = clt->next;
		if (fds[i].revents == POLLIN || fds[i].revents == POLLPRI)
			read_client(server, clt);
		++i;
		clt = next;
	}
}

static void server_loop(server_t *server)
{
	struct pollfd *fds = build_poll_fds(server);

	if (!fds || poll(fds, server->client_nb + 1, 5000) == -1)
		return;
	if (fds[server->client_nb].revents == POLLIN)
		server_accept(server);
	handle_poll(fds, server);
	free(fds);
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
	create_teams_clients(server);
	while (end == EXIT_SUCCESS) {
		server_loop(server);
	}
	close(server->fd);
	return 0;
}