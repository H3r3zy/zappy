/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <server.h>
#include <string.h>
#include "server.h"
#include "debug.h"

void init_client(server_t *server, client_t *client)
{
	srand(time(NULL));
	client->fd = i_socket_accept(server->fd);
	if (client->fd != SOCKET_ERROR) {
		client->user.x = rand() % server->map.size.x;
		client->user.y = rand() % server->map.size.y;
		client->user.level = 1;
		client->user.vision = 1;
		memset(client->queue, 0,
			sizeof(char *) * (LIMIT_TASK_NUMBER + 1));
		client->queue_index = 0;
		memset(client->user.bag, 0, sizeof(uint) * 7);
		memset(client->task, 0,
			sizeof(scheduler_t *) * LIMIT_TASK_NUMBER);
		debug(INFO "New client on fd %i\n", client->fd);
		server->client_nb++;
	}
	debug_if(client->fd == SOCKET_ERROR, ERROR "Accept error\n");
}

void read_client(server_t *server, client_t *client)
{
	char *request = gnl(client->fd, "\n");

	if (!request)
		disconnect(server, client);
	else {
		debug(INFO "'%i' Client request : %s\n", client->fd, request);
		free(request);
	}
}

void add_to_queue(client_t *client, char *msg)
{
	if (client->queue_index < LIMIT_TASK_NUMBER)
		client->queue[client->queue_index++] = msg;
	else
		debug(ERROR "Response queue of client %d is full.\n",
			client->fd);
}

static int try_write(const int fd, char *msg)
{
	size_t len = strlen(msg);
	size_t wrote = 0;
	ssize_t status = 0;

	while (wrote < len) {
		status = write(fd, msg + wrote, len - wrote);
		if (status < 1) {
			debug(ERROR "Failed to wrote response to client %d\n",
			fd);
			return 1;
		}
		wrote += status;
	}
	return 0;
}

void send_responses(client_t *client)
{
	while (client->queue_index) {
		if (try_write(client->fd, *client->queue) != 0)
			break;
		free(*client->queue);
		for (uint i = 1; client->queue[i]; i++)
			client->queue[i - 1] = client->queue[i];
		client->queue[client->queue_index - 1] = NULL;
		--client->queue_index;
	}
}