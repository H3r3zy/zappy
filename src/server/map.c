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
* Initialize the map
* 	- allocate each row
* 	-
* @param map
*/
void init_map(map_t *map)
{
	float density = 1.0f;
	uint elements = (uint)(map->size.x * map->size.y * density);
	pos_t pos;

	map->map = malloc(sizeof(cell_t *) * map->size.y);
	for (size_t y = 0; y < map->size.y; y++)
		map->map[y] = calloc(map->size.x, sizeof(cell_t));
	map->max_id = 0;
	srand(time(NULL));
	while (elements--) {
		pos = (pos_t){rand() % map->size.x, rand() % map->size.y};
		UPDATE_RESOURCE(map, pos, rand() % RESOURCE_NB, 1);
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
		(*front)->prev = entity;
	*front = entity;
}

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
		return;
	} else {
		if ((entity)->prev)
			(entity)->prev->next = (entity)->next;
		if ((entity)->next)
			(entity)->next->prev = (entity)->prev;
	}
}

// TODO Remove this shit
int print_da_letter(uint *items, entity_t *entities)
{
	int ok = 1;
	if (items[Linemate])
		printf("L");
	else if (items[Deraumere])
		printf("D");
	else if (items[Sibur])
		printf("S");
	else if (items[Mendiane])
		printf("M");
	else if (items[Phiras])
		printf("P");
	else if (items[Thystame])
		printf("T");
	else if (items[Food])
		printf("F");
	else if (entities)
		printf("0");
	else
		ok = 0;
	return ok;
}

// TODO Also remove this shit
void print_map(map_t *map)
{
	for (size_t y = 0; y < map->size.y; y++) {
		if (y || y < map->size.y - 1) {
			for (size_t x = 0; x < map->size.x; x++)
				printf("--");
			printf("\n");
		}
		for (size_t x = 0; x < map->size.x; x++) {
			if (x || x < map->size.x - 1)
				printf("|");
			if (!print_da_letter(map->map[y][x].items, map->map[y][x].players))
				printf(" ");
		}
		printf("\n");
	}
}
