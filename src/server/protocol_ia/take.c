/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <server.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <debug.h>
#include "server.h"

static const char *TYPENAME[] = {
	"Linemate",
	"Deraumere",
	"Sibur",
	"Mendiane",
	"Phiras",
	"Thystame",
	"Food",
	NULL
};

static bool is_of_type(entity_t *entity, char *type)
{
	if (entity->type == Client)
		return false;
	if (strcasecmp(TYPENAME[entity->type], type) == 0)
		return true;
	return false;
}

void take_cmd(server_t *server, client_t *client, char *arg)
{
	entity_t *entities = server->map.map[client->entity->pos.y][client->entity->pos.x];

	debug(INFO "'%i' call Take '%s'\n", client->fd, arg);
	while (entities) {
		if (is_of_type(entities, arg)) {
			client->user.bag[entities->type]++;
			remove_from_map(&server->map, entities);
			free(entities);
			add_to_queue(client, strdup("ok\n"));
			return;
		}
		entities = entities->next;
	}
	add_to_queue(client, strdup("ko\n"));
}