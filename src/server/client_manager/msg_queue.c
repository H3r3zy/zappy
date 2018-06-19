/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** msg_queue.c
*/

#include <memory.h>
#include <stdlib.h>
#include "debug.h"
#include "server.h"

void add_to_queue(client_t *client, char *msg)
{
	if (client->queue_index < LIMIT_TASK_NUMBER)
		client->queue[client->queue_index++] = strdup(msg);
	else
		debug(ERROR "Response queue of client %d is full.\n",
		client->fd);
}

int try_write(const int fd, char *msg)
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
	debug(GINFO "Send to %i => %s", fd, msg);
	return 0;
}

int send_responses(client_t *client)
{
	while (client->queue_index) {
		if (try_write(client->fd, *client->queue) != 0) {
			return 1;
		}
		free(*client->queue);
		for (uint32_t i = 1; client->queue[i]; i++) {
			client->queue[i - 1] = client->queue[i];
		}
		client->queue[client->queue_index - 1] = NULL;
		--client->queue_index;
	}
	return 0;
}
