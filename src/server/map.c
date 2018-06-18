/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.c
*/

#include <time.h>
#include <stdlib.h>
#include <server.h>
#include <stdio.h>
#include "server.h"
#include "debug.h"

/**
 * Update resource 't' at pos 'pos' by and add 'n'
 * @param map
 * @param pos
 * @param t
 * @param n
 */
void update_resource(map_t *map, pos_t pos, entity_type_t t, int n)
{
	map->map[pos.y][pos.x].items[t] += n;
	map->stock[t] += n;
}

/**
* Initialize the map
* Allocate each row
* @param map
*/
void init_map(map_t *map)
{
	float density = 1.0f;
	uint elements = (uint)(map->size.x * map->size.y * density);
	pos_t pos;

	map->map = malloc(sizeof(cell_t *) * map->size.y);
	if (!map->map)
		return;
	for (int y = 0; y < map->size.y; y++)
		map->map[y] = calloc(map->size.x, sizeof(cell_t));
	map->max_id = 1;
	srand(time(NULL));
	while (elements--) {
		pos = (pos_t){rand() % map->size.x, rand() % map->size.y};
		update_resource(map, pos, rand() % RESOURCE_NB, 1);
	}
}

/**
* Add a player in the cell at the pos of the entity
* @param map
* @param entity
*/
void add_player_to_map(map_t *map, entity_t *entity)
{
	entity_t **front = &map->map[entity->pos.y][entity->pos.x].players;

	debug(INFO "Add entity id %d on map\n", entity->id);
	entity->prev = NULL;
	entity->next = *front;
	if (*front)
		entity->next->prev = entity;
	*front = entity;

	/*new->prev = NULL;
	new->next = server->clients;
	if (new->next)
		new->next->prev = new;
	server->clients = new;*/
}

/**
* Remove a player from the cell at the pos of the entity
* @param map
* @param entity
*/
void remove_player_from_map(map_t *map, entity_t *entity)
{
	entity_t **front = &map->map[entity->pos.y][entity->pos.x].players;

	debug(INFO "Remove entity : id = %d\n", entity->id);
	if (*front == entity) {
		*front = (*front)->next;
		if (*front)
			(*front)->prev = NULL;
	} else {
		debug(INFO "entity->prev : %p\n", entity->prev);
		if ((entity)->prev)
			(entity)->prev->next = (entity)->next;
		debug(INFO "entity->next : %p\n", entity->next);
		if ((entity)->next)
			(entity)->next->prev = (entity)->prev;
	}
}

/**
 * Move a player from the cell at the pos of the entity to the pos in arg
 * @param map
 * @param entity
 * @param pos
 */
void move_player_to(map_t *map, entity_t *entity, pos_t *pos)
{
	remove_player_from_map(map, entity);
	entity->pos.x = pos->x;
	entity->pos.y = pos->y;
	add_player_to_map(map, entity);
}

// TODO Remove this shit
int print_da_letter(uint *items, entity_t *entities)
{
	int ok = 1;
	if (items[Linemate])
		fprintf(stderr, "L");
	else if (items[Deraumere])
		fprintf(stderr, "D");
	else if (items[Sibur])
		fprintf(stderr, "S");
	else if (items[Mendiane])
		fprintf(stderr, "M");
	else if (items[Phiras])
		fprintf(stderr, "P");
	else if (items[Thystame])
		fprintf(stderr, "T");
	else if (items[Food])
		fprintf(stderr, "F");
	else if (entities)
		fprintf(stderr, "0");
	else
		ok = 0;
	return ok;
}

// TODO Also remove this shit
void print_map(map_t *map)
{
	for (int y = 0; y < map->size.y; y++) {
		if (y || y < map->size.y - 1) {
			for (int x = 0; x < map->size.x; x++)
				fprintf(stderr, "--");
			fprintf(stderr, "\n");
		}
		for (int x = 0; x < map->size.x; x++) {
			if (x || x < map->size.x - 1)
				fprintf(stderr, "|");
			if (!print_da_letter(map->map[y][x].items, map->map[y][x].players))
				fprintf(stderr, " ");
		}
		fprintf(stderr, "\n");
	}
}
