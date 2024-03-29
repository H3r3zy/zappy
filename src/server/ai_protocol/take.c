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
#include <gui_command.h>
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

/**
* Try to take an object (arg) on the cell where the client is
* @param server
* @param client
* @param arg
*/
void take_cmd(server_t *server, client_t *client, char *arg)
{
	debug(INFO "'%i' call Take '%s'\n", client->fd, arg);
	for (int i = 0; TYPENAME[i]; i++) {
		if (!strcasecmp(TYPENAME[i], arg) && server->map.map[
		POS(client).y][POS(client).x].items[i]) {
			update_resource(&server->map, &client->entity->pos,
				i, -1);
			client->user.bag[i]++;
			add_to_queue(client, "ok\n");
			gui_pgt(server, client, i);
			return;
		}
	}
	add_to_queue(client, "ko\n");
}