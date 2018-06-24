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
void update_resource(map_t *map, pos_t *pos, entity_type_t t, int n)
{
	map->map[pos->y][pos->x].items[t] += n;
	map->stock[t] += n;
}

/**
* Initialize the map
* Allocate each row
* @param map
*/
void init_map(map_t *map)
{
	float density = 5.0f;
	uint32_t elements = (uint32_t)(map->size.x * map->size.y * density);
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
		update_resource(map, &pos, rand() % RESOURCE_NB, 1);
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

	entity->prev = NULL;
	entity->next = *front;
	if (*front)
		entity->next->prev = entity;
	*front = entity;
}
/* LINE 65 ?
new->prev = NULL;
new->next = server->clients;
if (new->next)
	new->next->prev = new;
server->clients = new;*/

/**
* Remove a player from the cell at the pos of the entity
* @param map
* @param entity
*/
void remove_player_from_map(map_t *map, entity_t *entity)
{
	entity_t **front = &map->map[entity->pos.y][entity->pos.x].players;

	if (*front == entity) {
		*front = (*front)->next;
		if (*front)
			(*front)->prev = NULL;
	} else {
		if ((entity)->prev)
			(entity)->prev->next = (entity)->next;
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
