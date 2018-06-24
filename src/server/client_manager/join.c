/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "scheduler.h"
#include "server.h"
#include "debug.h"

/**
* Malloc and memset all resources used in a client
* @param client
* @return
*/
static bool malloc_client_data(client_t *client)
{
	client->entity = malloc(sizeof(entity_t));
	if (!client->entity) {
		debug(ERROR "Can't create user (" CLR(RED,
			"Malloc error") ")\n");
		return false;
	}
	memset(client->queue, 0, sizeof(char *) * (LIMIT_TASK_NUMBER + 1));
	memset(client->user.bag, 0, sizeof(uint32_t) * RESOURCE_NB);
	memset(client->task, 0, sizeof(task_t *) * LIMIT_TASK_NUMBER);
	return true;
}

/**
* Fill data in client
* @param server
* @param client
*/
static void init_client_data(server_t *server, client_t *client)
{
	client->entity->pos.x = 0;
	client->entity->pos.y = 0;
	client->entity->id = ++server->map.max_id;
	client->entity->ptr = client;
	client->user.level = 1;
	client->user.vision = 1;
	client->queue_index = 0;
	client->team = NULL;
	client->user.bag[Food] = START_FOOD;
	#ifdef DEBUG
	client->user.bag[Food] = 10;
	#endif
	client->user.orientation = (orientation_t)(rand() % 4);
	client->started_time = 0;
	client->status = NORMAL;
	client->buff = calloc(READ_SIZE + 1, 1);
	client->buff_len = 0;
	client->buff_size = READ_SIZE + 1;
}

/**
* Accept a client in the server, initialise it and add it in the map
* @param server
* @param client
*/
void init_client(server_t *server, client_t *client)
{
	if (!malloc_client_data(client))
		return;
	init_client_data(server, client);
	server->client_nb++;
	add_to_queue(client, "WELCOME\n");
	debug(INFO "New client on fd %i : id %d (pos : %d;%d)\n", client->fd,
		client->entity->id,
		client->entity->pos.x, client->entity->pos.y);
}

/**
* Handle a connexion (create new client_t)
* @param server
*/
void handle_new_client(server_t *server)
{
	int fd = i_socket_accept(server->fd);
	client_t *new;

	if (fd == SOCKET_ERROR) {
		debug(ERROR "Can't create user (" CLR(RED,
			"Accept error") ")\n");
		return;
	}
	new = malloc(sizeof(client_t));
	if (!new) {
		debug(ERROR "can't create user (malloc failed)\n");
		return;
	}
	new->fd = fd;
	new->prev = NULL;
	new->next = server->clients;
	if (new->next)
		new->next->prev = new;
	server->clients = new;
	init_client(server, new);
}