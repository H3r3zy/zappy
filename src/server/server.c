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

static void server_loop(server_t *server)
{
	client_t *client = server->clients;
	bool stop = false;
	struct pollfd fds = {server->fd, POLLIN, 0};

	poll(&fds, 1, 10);
	if (fds.revents == POLLIN)
		server_accept(server);
	if (!client)
		return;
	do {
		fds.fd = client->fd;
		fds.revents = 0;
		poll(&fds, 1, 10);
		/*if (fds.revents == POLLIN || fds.revents == POLLPRI)
			client_action(server, client);*/
		if (fds.revents == POLLHUP || fds.revents == POLLNVAL
			|| fds.revents == POLLERR)
			disconnect(server, client);
		client = client->next;
	} while (client != server->clients);
}

int server(server_t *serv)
{
	int end = EXIT_SUCCESS;

	serv->fd = i_socket((uint16_t) serv->port);
	if (serv->fd == SOCKET_ERROR) {
		fprintf(stderr, "Can't create server on port: %i\n", serv->port);
		return EXIT_FAILURE;
	}
	debug(GINFO "Server started on 127.0.0.1:" CYAN "%i" RESET"\n", serv->port);
	while (end == EXIT_SUCCESS) {
		server_loop(serv);
	}
	close(serv->fd);
	return 0;
}