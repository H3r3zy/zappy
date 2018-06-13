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

static int generate_resource_at(map_t *map, uint x, uint y)
{
	entity_t **entities = &map->map[y][x];
	entity_t *entity = malloc(sizeof(entity_t));

	if (!entity)
		return 1;
	entity->id = map->max_id++;
	entity->type = (entity_type_t)(rand() % 7);
	entity->pos = (pos_t){x, y};
	entity->prev = NULL;
	entity->next = *entities;
	if (*entities)
		(*entities)->prev = entity;
	*entities = entity;
	return 0;
}

void smooth_print(float percentage)
{
	static int last = 0;
	int rounded = (int)(percentage * 100);

	if (rounded && rounded % 10 == 0 && last != rounded) {
		fprintf(stderr, "\r");
		debug(GINFO "Generating map [");
		last = rounded;
		for (int i = 0; i < 10; i++)
			fprintf(stderr, (i <= (rounded / 10) ? "=" : " "));
		fprintf(stderr, "]");
		fflush(stdout);
	}
}

void generate_map(map_t *map)
{
	float density = 0.1f;
	uint cell_nb = map->size.x * map->size.y;
	uint elements = (uint)(cell_nb * 6 * density);
	float percentage = 0.0f;
	float percentage_add = 1.f / elements;

	srand(time(NULL));
	debug(GINFO "Generating map [          ]");
	while (elements--) {
		if (generate_resource_at(map,
			rand() % map->size.x, rand() % map->size.y) != 0) {
			debug(ERROR "Allocation error while generating map");
			break;
		}
		percentage += percentage_add;
		smooth_print(percentage);
	}
	printf("\n");
}

void add_to_map(map_t *map, entity_t *entity)
{
	entity_t **front = &map->map[entity->pos.y][entity->pos.x];

	entity->next = *front;
	if (*front)
		(*front)->prev = entity;
	*front = entity;
}

void remove_from_map(map_t *map, entity_t *entity)
{
	entity_t **front = &map->map[entity->pos.y][entity->pos.x];

	if (*front == entity) {
		(*front)->prev = NULL;
		*front = (*front)->next;
	} else {
		if ((*front)->prev)
			(*front)->prev->next = (*front)->next;
		if ((*front)->next)
			(*front)->next->prev = (*front)->prev;
	}
}

#ifdef DEBUG
void print_da_letter(entity_t *entity)
{
	while (entity) {
		switch (entity->type) {
		case Linemate:
			printf("L");
			break;
		case Deraumere:
			printf("D");
			break;
		case Sibur:
			printf("S");
			break;
		case Mendiane:
			printf("M");
			break;
		case Phiras:
			printf("P");
			break;
		case Thystame:
			printf("T");
			break;
		case Food:
			printf("F");
			break;
		case Client:
			printf("O");
			break;
		}
		entity = entity->next;
	}
}

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
			if (map->map[y][x])
				print_da_letter(map->map[y][x]);
			else
				printf(" ");
		}
		printf("\n");
	}
}
#endif