/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** loop.c
*/

#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "server.h"
#include "debug.h"


struct pollfd *build_poll_fds(server_t *server)
{
	static struct pollfd *fds = NULL;
	static size_t plt = 0;
	struct pollfd poll_struct = (struct pollfd){0, POLLIN, 0};

	if (!fds || server->client_nb >= plt) {
		plt += 8;
		fds = realloc(fds, sizeof(struct pollfd) * plt);
	} else if (plt - 8 > server->client_nb) {
		plt -= 8;
		fds = realloc(fds, sizeof(struct pollfd) * plt);
	}
	size_t i = 0;
	for (client_t *clt = server->clients; clt; clt = clt->next) {
		poll_struct.fd = clt->fd;
		fds[i] = poll_struct;
		if (*clt->queue)
			fds[i].events |= POLLOUT;
		++i;
	}
	fds[i] = (struct pollfd){server->fd, POLLIN, 0};
	return fds;
}

static void handle_poll(struct pollfd *fds, server_t *server)
{
	client_t *next = NULL;
	int i = 0;
	int status;

	for (client_t *clt = server->clients; clt;) {
		status = 0;
		next = clt->next;
		if (*clt->queue && (fds[i].revents & POLLOUT))
			status = send_responses(clt);
		if ((fds[i].revents & POLLIN))
			status += read_client(server, clt);
		if (status) {
			disconnect(server, clt);
		}
		++i;
		clt = next;
	}
}

void server_loop(server_t *server)
{
	struct pollfd *fds = build_poll_fds(server);
	size_t clients_nb = server->client_nb;

	if (!fds || poll(fds, clients_nb + 1, (clients_nb) ? 100 : 5000) == -1)
		return;
	handle_poll(fds, server);
	if ((fds[clients_nb].revents & POLLIN))
		handle_new_client(server);
}