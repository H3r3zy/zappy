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

static void fill_poll_fds(server_t *server, struct pollfd *fds)
{
	struct pollfd poll_struct = (struct pollfd){0, POLLIN, 0};
	size_t i = 0;

	for (client_t *clt = server->clients; clt; clt = clt->next) {
		poll_struct.fd = clt->fd;
		fds[i] = poll_struct;
		if (*clt->queue)
			fds[i].events |= POLLOUT;
		++i;
	}
	if (server->gui.logged) {
		fds[i] = (struct pollfd){server->gui.fd, POLLIN, 0};
		if (*server->gui.queue)
			fds[i].events |= POLLOUT;
		++i;
	}
	fds[i] = (struct pollfd){server->fd, POLLIN, 0};
}

static struct pollfd *build_poll_fds(server_t *server)
{
	static struct pollfd *fds = NULL;
	static size_t plt = 0;

	if (!fds || server->client_nb + server->gui.logged >= plt) {
		plt += 8;
		fds = realloc(fds, sizeof(struct pollfd) * plt);
	} else if (plt - 8 > server->client_nb + server->gui.logged) {
		plt -= 8;
		fds = realloc(fds, sizeof(struct pollfd) * plt);
	}
	fill_poll_fds(server, fds);
	return fds;
}

static void handle_poll(struct pollfd *fds, server_t *server)
{
	client_t *next = NULL;
	int status;
	int i = 0;

	for (client_t *clt = server->clients; clt;) {
		status = 0;
		next = clt->next;
		if (*clt->queue && (fds[i].revents & POLLOUT))
			status = send_responses(clt);
		if ((fds[i].revents & POLLIN))
			status += read_client(server, clt);
		if (status)
			disconnect(server, clt);
		++i;
		clt = next;
	}
}

static void handle_gui_poll(server_t *server, struct pollfd *fd)
{
	int status = 0;

	if ((fd->revents & POLLOUT)) {
		if (*server->gui.queue) {
			debug(ERROR "%i\n", server->gui.len);
			status = try_write_gui(server->gui.fd, server->gui.queue, (uint32_t) server->gui.len + 1);
			*server->gui.queue = 0;
			server->gui.len = 0;
		}
		gui_continue_commands(server);
	}
	if ((fd->revents & POLLIN))
		status += read_gui(server);
	if (status) {
		server->gui.logged = 0;
		server->gui.fd = -1;
		*server->gui.queue = 0;
		server->gui.len = 0;
		debug(GINFO "GUI Client disconnected\n");
	}
}

void server_loop(server_t *server)
{
	struct pollfd *fds = build_poll_fds(server);
	size_t clients_nb = server->client_nb;
	char gui_logged = server->gui.logged;

	if (!fds || poll(fds, clients_nb + 1 + server->gui.logged,
		(server->client_nb) ? 100 : 5000) == -1)
		return;
	handle_poll(fds, server);
	if (gui_logged)
		handle_gui_poll(server, &fds[clients_nb]);
	if ((fds[clients_nb + gui_logged].revents & POLLIN))
		handle_new_client(server);
}