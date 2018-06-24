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
#include "command.h"

const look_type_t ENTITY_TYPES[ENTITY_NB] = {
	{" linemate", 9}, {" deraumere", 10},
	{" sibur", 6}, {" mendiane", 9},
	{" phiras", 7}, {" thystame", 9},
	{" food", 5}, {" player", 7}};

static void add_objects(look_opt_t *opt, cell_t *cell)
{
	for (entity_t *entity = cell->players; entity; entity = entity->next)
		concat(" player", 7, opt);
	for (int i = 0; i < RESOURCE_NB; i++) {
		for (uint32_t n = 0; n < cell->items[i]; n++) {
			concat(ENTITY_TYPES[i].name, ENTITY_TYPES[i].len, opt);
		}
	}
}

static void update_look_pos(int dx, int dy, pos_t *pos, pos_t *size)
{
	if (dx < 0)
		pos->x = (pos->x > 0) ? pos->x + dx : size->x - 1;
	else if (dx > 0)
		pos->x = (pos->x < size->x - 1) ? pos->x + dx : 0;
	if (dy < 0)
		pos->y = (pos->y > 0) ? pos->y + dy : size->y - 1;
	else if (dy > 0)
		pos->y = (pos->y < size->y - 1) ? pos->y + dy : 0;
}

static char *look_horizontal(map_t *map, pos_t pos, look_opt_t *opt,
	uint32_t currv)
{
	pos_t start = pos;

	update_look_pos(opt->d, -opt->d, &start, &map->size);
	pos = start;
	for (uint32_t i = 0; i < currv * 2 + 1; i++) {
		add_objects(opt, &map->map[pos.y][pos.x]);
		if (i < currv * 2) {
			concat(",", 1, opt);
		}
		update_look_pos(0, opt->d, &pos, &map->size);
	}
	if (currv < opt->vision) {
		concat(",", 1, opt);
		look_horizontal(map, start, opt, currv + 1);
	}
	return *opt->str;
}

/**
* Perform a vertical 'look'
* @param map
* @param pos
* @param opt
* @param currv
* @return
*/
static char *look_vertical(map_t *map, pos_t pos, look_opt_t *opt,
	uint32_t currv)
{
	pos_t start = pos;

	update_look_pos(opt->d, opt->d, &start, &map->size);
	pos = start;
	for (size_t i = 0; i < currv * 2 + 1; i++) {
		add_objects(opt, &map->map[pos.y][pos.x]);
		if (i < currv * 2) {
			concat(",", 1, opt);
		}
		update_look_pos(-opt->d, 0, &pos, &map->size);
	}
	if (currv < opt->vision) {
		concat(",", 1, opt);
		look_vertical(map, start, opt, currv + 1);
	}
	return *opt->str;
}

/**
* Look around the player in a cone shape
* @param srv
* @param client
* @param arg
*/
void look_cmd(server_t *srv, client_t *clt,
	__attribute__((unused)) char *arg)
{
	static char *str = NULL;
	static size_t size = 0;
	int dx = (clt->user.orientation % 2) ? -clt->user.orientation + 2 : 0;
	int dy = !(clt->user.orientation % 2) ? clt->user.orientation - 1 : 0;
	size_t len = 1;
	look_opt_t opt = {clt->user.vision, &size, &len, &str, (dx) ? dx : dy};

	if (!str) {
		str = strcat(calloc(LOOK_STR_SIZE, 1), "[");
		size = LOOK_STR_SIZE;
	}
	add_objects(&opt,
		&srv->map.map[clt->entity->pos.y][clt->entity->pos.x]);
	concat(",", 1, &opt);
	if (dx)
		look_horizontal(&srv->map, clt->entity->pos, &opt, 1);
	else
		look_vertical(&srv->map, clt->entity->pos, &opt, 1);
	concat(" ]\n", 3, &opt);
	add_to_queue(clt, str);
}