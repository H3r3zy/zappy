/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include <stdio.h>
#include <server.h>
#include <string.h>
#include "server.h"

static char *add_objects(char *response, entity_t *entities)
{
	/*while (entities) {

		entities = entities->next;
	}*/
}

static void look_horizontal(map_t *map, uint vision, pos_t pos, int dx)
{
}

static void look_vertical(map_t *map, uint vision, pos_t pos, int dy)
{
	/*pos_t start = (pos_t){pos.x, pos.y};

	pos.x = (dy < 0 && !pos.x) ? map->size.x - 1 : pos.x + dy;
	pos.y = (dy < 0 && !pos.y) ? map->size.y - 1 : pos.y + dy;*/
}

void look_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg)
{
	/*char *response = strdup("[player,");
	int dx = (client->user.orientation % 2 != 0) ?
		-(client->user.orientation - 2) : 0;
	int dy = (client->user.orientation % 2 == 0) ?
		client->user.orientation - 1 : 0;

	if (dx)
		look_horizontal(&server->map, client->user.vision,
			client->entity->pos, dx);
	if (dy)
		look_vertical(&server->map, client->user.vision,
			client->entity->pos, dy);
	//add_to_queue(client, response);*/
}