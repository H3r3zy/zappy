/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include <stdio.h>
#include <server.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "server.h"
#include "command.h"

look_type_t ENTITY_TYPES[ENTITY_NB] = {
	{" linemate", 9},
	{" deraumere", 10},
	{" sibur", 6},
	{" mendiane", 9},
	{" phiras", 7},
	{" thystame", 9},
	{" food", 5},
	{" player", 7}
};

static char *concat(char *s1, char *s2)
{
	char *str;

	if (!s1)
		return s2;
	if (!s2)
		return s1;
	str = realloc(s1, strlen(s1) + strlen(s2) + 1);
	if (!str)
		return s1;
	str = strcat(str, s2);
	return str;
}

static char *add_objects(char *response, cell_t *cell)
{
	for (entity_t *entity = cell->players; entity; entity = entity->next) {
		response = concat(response, " player");
	}
	for (int i = 0; i < RESOURCE_NB; i++) {
		for (uint n = 0; n < cell->items[i]; n++) {
			response = concat(response, ENTITY_TYPES[i].name);
		}
	}
	return response;
}

static char *look_horizontal(map_t *map, pos_t pos, look_opt_t opt, uint currv)
{
	char *response = strdup("");
	char *tmp = NULL;
	pos_t start = (pos_t){pos.x, pos.y};

	start.x = (opt.d < 0 && !pos.x) ? map->size.x - 1 : pos.x + opt.d;
	start.y = (opt.d < 0 && !pos.y) ? map->size.y - 1 : pos.y + opt.d;
	pos = start;
	for (uint i = 0; i < currv * 2 + 1; i++) {
		pos.y = (pos.y > map->size.y - 1) ? 0 : pos.y;
		pos.x = (pos.x > map->size.x - 1) ? 0 : pos.x;
		debug(WARNING "Look in %i;%i\n", pos.x, pos.y);
		response = add_objects(response, &map->map[pos.y][pos.x]);
		if (i < currv * 2) {
			response = concat(response, ",");
		}
		pos.y = opt.d < 0 && !pos.y ? map->size.y - 1 : pos.y + opt.d;
	}
	if (currv < opt.vision) {
		tmp = look_horizontal(map, start, opt, currv + 1);
		response = concat(response, tmp);
		free(tmp);
	}
	return response;

}

/**
* Perform a vertical 'look'
* @param map
* @param pos
* @param opt
* @param currv
* @return
*/
static char *look_vertical(map_t *map, pos_t pos, look_opt_t opt, uint currv)
{
	char *response = strdup("");
	char *tmp = NULL;
	pos_t start = (pos_t){pos.x, pos.y};

	start.x = (opt.d < 0 && !pos.x) ? map->size.x - 1 : pos.x + opt.d;
	start.y = (opt.d < 0 && !pos.y) ? map->size.y - 1 : pos.y + opt.d;
	pos = start;
	for (size_t i = 0; i < currv * 2 + 1; i++) {
		pos.y = (pos.y > map->size.y - 1) ? 0 : pos.y;
		pos.x = (pos.x > map->size.x - 1) ? 0 : pos.x;
		response = add_objects(response, &map->map[pos.y][pos.x]);
		if (i < currv * 2) {
			response = concat(response, ",");
		}
		pos.x = opt.d < 0 && !pos.x ? map->size.x - 1 : pos.x + opt.d;
	}
	if (currv < opt.vision) {
		tmp = look_vertical(map, start, opt, currv + 1);
		response = concat(response, tmp);
		free(tmp);
	}
	return response;
}

/**
* Look around the player in a cone shape
* @param server
* @param client
* @param arg
*/
void look_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg)
{
	char *response = strdup("[");
	char *tmp = NULL;
	int dx = (client->user.orientation % 2 != 0) ?
		-(client->user.orientation - 2) : 0;
	int dy = (client->user.orientation % 2 == 0) ?
		client->user.orientation - 1 : 0;
	look_opt_t opt = {client->user.vision, 0};

	debug(GINFO "'%d' call Look command (%i,%i:%i)\n", client->fd, client->entity->pos.x, client->entity->pos.y, (int)client->user.orientation);
	response = add_objects(response, &server->map.map[client->entity->pos.y][client->entity->pos.x]);
	response = concat(response, ",");
	if (dx) {
		opt.d = dx;
		tmp = look_horizontal(&server->map, client->entity->pos, opt, 1);
	} else if (dy) {
		opt.d = dy;
		tmp = look_vertical(&server->map, client->entity->pos, opt, 1);
	}
	response = concat(response, tmp);
	free(tmp);
	response = concat(response, " ]\n");
	add_to_queue(client, response);
	free(response);
}