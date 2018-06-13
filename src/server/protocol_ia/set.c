/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <server.h>
#include <memory.h>
#include <stdbool.h>
#include <stdlib.h>
#include <debug.h>
#include "server.h"

static const char *TYPENAME[] = {
	"Linemate",
	"Deraumere",
	"Sibur",
	"Mendiane",
	"Phiras",
	"Thystame",
	"Food",
	NULL
};

void set_cmd(server_t *server, client_t *client, char *arg)
{
	debug(INFO "'%i' call Set '%s'\n", client->fd, arg);
	for (uint i = 0; TYPENAME[i]; i++) {
		if (!strcasecmp(TYPENAME[i], arg) && client->user.bag[i]) {
			UPDATE_RESOURCE(&server->map, client->entity->pos,
				i, 1);
			client->user.bag[i]--;
			add_to_queue(client, strdup("ok\n"));
			return;
		}
	}
	add_to_queue(client, strdup("ko\n"));
}