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

look_type_t ENTITY_TYPES[ENTITY_NB ] = {
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
	str = realloc(s1, strlen(s1) + strlen(s2) + 1);
	str = strcat(str, s2);
	return str;
}

static char *add_objects(char *response, cell_t *cell)
{
	size_t len = (response) ? strlen(response) : 0;
	response = realloc(response, len + 2);

	strcpy(response + len, ",");
	for (entity_t *entity = cell->players; entity; entity = entity->next)
		response = strcat(realloc(response,
			strlen(response) + 8), " player");
	for (int i = 0; i < RESOURCE_NB; i++) {
		for (int n = 0; n < cell->items[i]; n++) {
			response = concat(response, ENTITY_TYPES[i].name);
		}
	}
	return response;
}

static void look_horizontal(map_t *map, uint vision, pos_t pos, int dx)
{
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
	char *response = NULL;
	pos_t start = (pos_t){pos.x, pos.y};

	start.x = (opt.d < 0 && !pos.x) ? map->size.x - 1 : pos.x + opt.d;
	start.y = (opt.d < 0 && !pos.y) ? map->size.y - 1 : pos.y + opt.d;
	pos = start;
	for (int i = 0; i < currv * 2 + 1; i++) {
		response = add_objects(response, &map->map[pos.y][pos.x]);
		pos.x -= opt.d;
	}
	if (currv < opt.vision)
		return concat(response,
			look_vertical(map, start, opt, currv + 1));
	else
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
	char *response = strdup("[player");
	int dx = (client->user.orientation % 2 != 0) ?
		-(client->user.orientation - 2) : 0;
	int dy = (client->user.orientation % 2 == 0) ?
		client->user.orientation - 1 : 0;
	look_opt_t opt = {client->user.vision, 0};

	if (dx) {
		opt.d = dx;
		look_horizontal(&server->map, client->user.vision,
			client->entity->pos, dx);
	} else if (dy) {
		opt.d = dy;
		response = concat(response, look_vertical(&server->map,
			client->entity->pos, opt, 1));
	}
	response = concat(response, "]");
	add_to_queue(client, response);
}