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

char *str_types[ENTITY_NB ] = {
	"linemate",
	"deraumere",
	"sibur",
	"mendiane",
	"phiras",
	"thystame",
	"food",
	"player"
};

static char *concat(char *s1, char *s2)
{
	char *str;

	if (!s1)
		return s2;
	str = malloc(strlen(s1) + strlen(s2) + 1);
	str = strcpy(str, s1);
	str = strcat(str, s2);
	return str;
}

static char *add_objects(char *response, entity_t *entities)
{
	size_t len = (response) ? strlen(response) : 0;
	response = realloc(response, len + 2);

	strcpy(response + len, ",");
	while (entities) {
		response = strcat(strcat(realloc(response, strlen(str_types
		[entities->type]) + 2), " "), str_types[entities->type]);
		entities = entities->next;
	}
	debug(INFO "add_objects : %s\n", response);
	return response;
}

//,

static void look_horizontal(map_t *map, uint vision, pos_t pos, int dx)
{
}

static char *look_vertical(map_t *map, pos_t pos, look_opt_t opt, uint currv)
{
	/*char *response = NULL;
	pos_t start = (pos_t){pos.x, pos.y};

	start.x = (opt.d < 0 && !pos.x) ? map->size.x - 1 : pos.x + opt.d;
	start.y = (opt.d < 0 && !pos.y) ? map->size.y - 1 : pos.y + opt.d;
	pos = start;
	for (int i = 0; i < currv * 2 + 1; i++) {
		debug(INFO "Looking at pos %d;%d\n", pos.x, pos.y);
		response = concat(response,
			add_objects(response, map->map[pos.y][pos.y]));
		pos.x -= opt.d;
	}
	if (currv < opt.vision)
		return concat(look_vertical(map, start, opt, currv + 1),
			response);
	else
		return response;*/
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
	/*int dx = (client->user.orientation % 2 != 0) ?
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
	}*/
	response = concat(response, "]");
	debug(ERROR "Response : %s\n", response);
	//add_to_queue(client, response);
}