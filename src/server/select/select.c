/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <server.h>
#include "debug.h"
#include "server.h"

int init_select(fd_set *fds, server_t *server)
{
	client_t *client = server->clients;
	int fd_max = server->fd;
	int fd_tmp;

	if (!client)
		return 0;
	FD_ZERO(fds);
	FD_SET(server->fd, fds);
	do {
		fd_tmp = client->fd;
		if (fd_tmp > fd_max)
			fd_max = fd_tmp;
		FD_SET(fd_tmp, fds);
		client = client->next;
	}
	while (client != server->clients);
	return fd_max;
}

int select_read(int fd_max, fd_set *fds, int usec)
{
	struct timeval tv = {0, usec};

	if (select(fd_max + 1, fds, NULL, NULL, &tv) == SOCKET_ERROR) {
		debug(ERROR "select error\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}