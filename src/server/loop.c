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
	static size_t prev_clients_nb = 0;

	if (!fds)
		fds = malloc(sizeof(struct pollfd) * (server->client_nb + 1));
	else if (server->client_nb != prev_clients_nb)
		fds = realloc(fds, sizeof(struct pollfd) *
			(server->client_nb + 1));
	size_t i = 0;
	for (client_t *clt = server->clients; clt; clt = clt->next) {
		fds[i] = (struct pollfd){clt->fd, POLLIN, 0};
		if (*clt->queue)
			fds[i].events |= POLLOUT;
		++i;
	}
	fds[i] = (struct pollfd){server->fd, POLLIN, 0};
	prev_clients_nb = server->client_nb;
	return fds;
}

static void handle_poll(struct pollfd *fds, server_t *server)
{
	client_t *next = NULL;
	int i = 0;

	for (client_t *clt = server->clients; clt;) {
		next = clt->next;
		if (*clt->queue && (fds[i].revents & POLLOUT))
			send_responses(clt);
		if ((fds[i].revents & POLLIN))
			read_client(server, clt);
		++i;
		clt = next;
	}
}

void server_loop(server_t *server)
{
	struct pollfd *fds = build_poll_fds(server);
	size_t clients_nb = server->client_nb;

	if (!fds || poll(fds, clients_nb + 1, 100) == -1)
		return;
	handle_poll(fds, server);
	if ((fds[clients_nb].revents & POLLIN))
		handle_new_client(server);
}