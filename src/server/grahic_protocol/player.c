/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player.c
*/

// ppo n X Y O\n ppo #n\n player’s position

#include <stdlib.h>
#include <stdio.h>
#include <server.h>
#include "server.h"

static client_t *get_client_by_id(server_t *server, size_t id)
{
	for (client_t *clt = server->clients; clt; clt = clt->next)
		if (clt->entity->id == id)
			return clt;
	return NULL;
}

void gui_pnw(server_t *server, client_t *client)
{
	char buff[281] = {0};

	snprintf(buff, 281, "pnw %u %u %u %d %u %s\n",
		client->entity->id, POS(client).x, POS(client).y,
		client->user.orientation + 1, client->user.level,
		(client->team) ? client->team->name : "");
	add_to_gui_queue(&server->gui, buff);
}

void gui_ppo(server_t *server, char *arg)
{
	size_t id = atoi(arg);
	char buff[22] = {0};
	client_t *player = get_client_by_id(server, id);

	if (player) {
		snprintf(buff, 22, "ppo %zu %u %u\n",
			id, POS(player).x, POS(player).y);
		add_to_gui_queue(&server->gui, buff);
	} else
		add_to_gui_queue(&server->gui, "ko\n");
}

void gui_plv(server_t *server, char *arg)
{
	size_t id = atoi(arg);
	char buff[12] = {0};
	client_t *player = get_client_by_id(server, id);

	if (player) {
		snprintf(buff, 12, "plv %zu %u\n", id, player->user.level);
		add_to_gui_queue(&server->gui, buff);
	} else
		add_to_gui_queue(&server->gui, "ko\n");
}

void gui_pin(server_t *server, char *arg)
{
	size_t id = atoi(arg);
	char buff[55] = {0};
	client_t *clt = get_client_by_id(server, id);

	if (clt) {
		snprintf(buff, 55, "pin %zu %u %u %u %u %u %u %u %u %u\n",
			id, POS(clt).x, POS(clt).y, clt->user.bag[Food],
			clt->user.bag[Linemate], clt->user.bag[Deraumere],
			clt->user.bag[Sibur], clt->user.bag[Mendiane],
			clt->user.bag[Phiras], clt->user.bag[Thystame]);
		add_to_gui_queue(&server->gui, buff);
	} else
		add_to_gui_queue(&server->gui, "ko\n");
}