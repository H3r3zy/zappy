/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** loop.c
*/

#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <server.h>
#include "server.h"
#include "debug.h"

static void handle_new_client(server_t *server)
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
	init_client(server, new);
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
//	debug(GINFO "Build poll fd for %d clients\n", server->client_nb);
	for (client_t *clt = server->clients; clt; clt = clt->next) {
		fds[i] = (struct pollfd){clt->fd, POLLIN, 0};
		++i;
	}
	fds[i] = (struct pollfd){server->fd, POLLIN, 0};
	return fds;
}

static void handle_poll(struct pollfd *fds, server_t *server)
{
	client_t *next = NULL;
	int i = 0;

	for (client_t *clt = server->clients; clt;) {
		next = clt->next;
		if ((fds[i].revents & POLLIN)) {
//			debug(GINFO "Revents & POLLIN on user %d\n", i);
			read_client(server, clt);
//			debug(GINFO "End of Revents & POLLIN ---\n");
		}
		++i;
		clt = next;
	}
//	debug(GINFO "End of Handle Poll\n");
}

void server_loop(server_t *server)
{
	struct pollfd *fds = build_poll_fds(server);
	size_t clients_nb = server->client_nb;

	if (!fds || poll(fds, clients_nb + 1, 5000) == -1)
		return;
	handle_poll(fds, server);
	if ((fds[clients_nb].revents & POLLIN))
		handle_new_client(server);
	free(fds);
}