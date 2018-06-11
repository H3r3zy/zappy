/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <server.h>
#include "socket.h"
#include "debug.h"
#include "server.h"

static void server_accept(server_t *server)
{
	client_t *client = server->clients;
	client_t *tmp = server->clients->next;
	client_t *new = malloc(sizeof(client_t));

	if (!new) {
		debug(ERROR "can't create user (malloc failed)\n");
		return;
	}
	client->next = new;
	new->prev = client;
	new->next = tmp;
	new->next->prev = new;
	new->user = (user_t){0};
	new->fd = i_socket_accept(server->fd);
	debug_if(new->fd != SOCKET_ERROR, INFO "new user on fd %i\n", new->fd);
	debug_if(new->fd == SOCKET_ERROR, ERROR "accept error\n");
}

static int server_loop(server_t *server, fd_set *fds)
{
	client_t *client = server->clients;
	bool stop = false;

	if (FD_ISSET(server->fd, fds))
		server_accept(server);
	do {
		/*
		if (FD_ISSET(client->fd, fds))
			stop = client_action(server, client);
		if (stop)
			break;*/
		client = client->next;
	} while (client != server->clients);
	return EXIT_SUCCESS;
}

static int server_select(fd_set *fds, server_t *server)
{
	int fd_max = init_select(fds, server);

	return select_read(fd_max, fds, 100);
}

int server(server_t *serv)
{
	int end = EXIT_SUCCESS;
	fd_set fds;

	serv->fd = i_socket((uint16_t) serv->port);
	if (serv->fd == SOCKET_ERROR) {
		fprintf(stderr, "Can't create server on port: %i\n", serv->port);
		return EXIT_FAILURE;
	}
	debug(GINFO "Server started on 127.0.0.1:" CYAN "%i" RESET"\n", serv->port);
	while (end == EXIT_SUCCESS) {
		if (server_select(&fds, serv) == EXIT_FAILURE)
			continue;
		end = server_loop(serv, &fds);
	}
	close(serv->fd);
	return 0;
}