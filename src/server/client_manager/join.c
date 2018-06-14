/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <scheduler.h>
#include <server.h>
#include "debug.h"
#include "server.h"

static void init_client_data(server_t *server, client_t *client)
{
	client->entity = malloc(sizeof(entity_t));
	if (!client->entity)
		return;
	client->entity->pos.x = rand() % server->map.size.x;
	client->entity->pos.y = rand() % server->map.size.y;
	client->entity->id = ++server->map.max_id;
	client->entity->type = Client;
	client->user.level = 1;
	client->user.vision = 1;
	memset(client->queue, 0,
		sizeof(char *) * (LIMIT_TASK_NUMBER + 1));
	client->queue_index = 0;
	client->team = NULL;
	client->user.orientation = (orientation_t)(rand() % 4);
}

void init_client(server_t *server, client_t *client)
{
	struct timespec spec;

	srand(time(NULL));
	client->fd = i_socket_accept(server->fd);
	if (client->fd != SOCKET_ERROR) {
		init_client_data(server, client);
		if (!client->entity)
			return;
		memset(client->user.bag, 0, sizeof(uint) * RESOURCE_NB);
		memset(client->task, 0,
			sizeof(task_t *) * LIMIT_TASK_NUMBER);
		debug(INFO "New client on fd %i (pos : %d;%d)\n", client->fd,
			client->entity->pos.x, client->entity->pos.y);
		server->client_nb++;
		add_to_queue(client, strdup("WELCOME\n"));
		add_player_to_map(&server->map, client->entity);
		clock_gettime(CLOCK_REALTIME, &spec);
		client->user.bag[Food] = STARTED_FOOD;
		debug("%i\n", client->user.bag[Food]);
		client->started_time = spec.tv_sec * STOMS + spec.tv_nsec / NTOMS;
	} else
		debug(ERROR "Accept error\n");
}