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
	float density = 0.667f;
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