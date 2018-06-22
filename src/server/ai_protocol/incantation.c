/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdbool.h>
#include <stdio.h>
#include <server.h>
#include <memory.h>
#include <gui_command.h>
#include "elevation.h"
#include "debug.h"

const elevation_t ELEVATIONS[] = {{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 0, 0, 0, 0, 2}, {2, 0, 1, 0, 2, 0, 0, 2},
	{1, 1, 2, 0, 1, 0, 0, 4}, {1, 2, 1, 3, 0, 0, 0, 4},
	{1, 2, 3, 0, 1, 0, 0, 6}, {2, 2, 2, 2, 2, 1, 0, 6}, {0}};

static bool can_do_incantation(client_t *client, cell_t *cell)
{
	uint32_t nb = 0;

	for (uint32_t i = 0; i < RESOURCE_NB; i++) {
		if (cell->items[i] != ELEVATIONS[client->user.level - 1][i]) {
			//debug(INFO "%i failed: %i instead of %i\n", i, cell->items[i], ELEVATIONS[client->user.level - 1][i]);
			return false;
		}
	}
	for (entity_t *cl = cell->players; cl; cl = cl->next) {
		if (((client_t *)cl->ptr)->user.level != client->user.level)
			return false;
		nb++;
	}
	return (nb == ELEVATIONS[client->user.level - 1][RESOURCE_NB]);
}

static void lvlup(cell_t *cell)
{
	client_t *client;

	for (entity_t *cl = cell->players; cl; cl = cl->next) {
		client = ((client_t *)cl->ptr);
		++client->user.level;
		++client->user.vision;
		debug(GINFO "'%i' lvlup: %i\n", client->fd, client->user.level);
	}
}

static void remove_stones(map_t *map, pos_t *pos, uint32_t level)
{
	for (uint32_t i = 0; i < RESOURCE_NB; i++) {
		update_resource(map, pos, i, ELEVATIONS[level - 1][i] * -1);
	}
}

bool incantation_verify(server_t *server, client_t *client,
	__attribute__((unused)) char *arg
)
{
	cell_t *cell = &server->map.map[client->entity->pos.y]
		[client->entity->pos.x];
	bool st = can_do_incantation(client, cell);
	client_t *tmp;

	debug(GINFO "'%i' %s Incantation\n", client->fd,
		(st) ? ("Start") : ("Fail"));
	if (!st)
		return st;
	gui_pic(server, client, cell->players);
	for (entity_t *cl = cell->players; cl; cl = cl->next) {
		tmp = ((client_t *)cl->ptr);
		tmp->status = INCANTATION;
		debug(INFO "\t'%i' participated\n", tmp->fd);
		add_to_queue(tmp, "Elevation underway\n");
	}
	return st;
}

void incantation_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg
)
{
	cell_t *cell = &server->map.map[client->entity->pos.y]
		[client->entity->pos.x];
	char buffer[126];

	debug(INFO "Incantation called\n");
	if (!can_do_incantation(client, cell)) {
		add_to_queue(client, "ko\n");
		debug(GINFO "Incantation failed\n");
		return;
	}
	remove_stones(&server->map, &client->entity->pos, client->user.level);
	lvlup(cell);
	snprintf(buffer, 126, "Current level: %i\n", client->user.level);
	for (entity_t *cl = cell->players; cl; cl = cl->next) {
		((client_t *)cl->ptr)->status = NORMAL;
		add_to_queue(cl->ptr, buffer);
		gui_pie(server, cl->ptr);
	}
	is_ended(server);
}