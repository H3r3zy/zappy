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
#include <memory.h>
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

/**
 * Response to GUI when a expulsion is call
 * @param server
 * @param client
 *
 * @response pex clientID\n
 */
void gui_pex(server_t *server, client_t *client)
{
	char buffer[124] = {0};

	snprintf(buffer, 124, "pex %li\n", client->entity->id);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when a broadcast is call
 * @param server
 * @param client
 * @param arg
 *
 * @response pbc clientID\n
 */
void gui_pbc(server_t *server, client_t *client, char *arg)
{
	char *buffer = malloc(sizeof(char) * (strlen(arg) + 26));

	if (!buffer)
		return;
	sprintf(buffer, "pbc %li %s\n", client->entity->id, arg);
	add_to_gui_queue(&server->gui, buffer);
	free(buffer);
}

/**
 * Response to GUI when Incantation is launch
 * @param server
 * @param client
 * @param entity
 *
 * @response pic clientX clientY [all clientID in incantation]\n
 */
void gui_pic(server_t *server, client_t *client, entity_t *entity)
{
	char buffer[1024] = {0};
	char tmp_buff[11]  = {0};

	sprintf(buffer, "pic %i %i", POS(client).x, POS(client).y);
	for (entity_t *en = entity; en; en = en->next) {
		sprintf(buffer, " %li", en->id);
		strcat(buffer, tmp_buff);
	}
	strcat(buffer, "\n");
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when an Incantation is done
 * @param server
 * @param client
 *
 * @response pie clientX clientY IncantationResponse
 */
void gui_pie(server_t *server, client_t *client)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "pie %i %i %i\n", POS(client).x, POS(client).y, client->user.level);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when an egg is laying
 * @param server
 * @param client
 *
 * @response pfk clientID
 */
void gui_pfk(server_t *server, client_t *client)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "pfk %li\n", client->entity->id);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when a resource is dropped
 * @param server
 * @param client
 * @param type
 *
 * @response pdr clientID resourceID
 */
void gui_pdr(server_t *server, client_t *client, entity_type_t type)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "pdr %li %i\n", client->entity->id, type);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when a resource is taken
 * @param server
 * @param client
 * @param type
 *
 * @response pdt clientID resourceType
 */
void gui_pdt(server_t *server, client_t *client, entity_type_t type)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "pdt %li %i\n", client->entity->id, type);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when a player die
 * @param server
 * @param client
 *
 * @response pdi clientID
 */
void gui_pdi(server_t *server, client_t *client)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "pdi %li\n", client->entity->id);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when a player drop an egg
 * @param server
 * @param egg
 * @param client
 *
 * @response enw eggID clientID clientX clientY
 */
void gui_enw(server_t *server, egg_t *egg, client_t *client)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "enw %li %li %i %i\n", egg->id,
		client->entity->id, POS(client).x, POS(client).y);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when an egg is hatching
 * @param server
 * @param egg
 *
 * @response eht eggID
 */
void gui_eht(server_t *server, egg_t *egg)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "eht %li\n", egg->id);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when a player is spawning in an egg
 * @param server
 * @param egg
 *
 * @response ebo eggID
 */
void gui_ebo(server_t *server, egg_t *egg)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "ebo %li\n", egg->id);
	add_to_gui_queue(&server->gui, buffer);
}

/**
 * Response to GUI when an egg is destroyed
 * @param server
 * @param egg
 *
 * @response edi eggID
 */
void gui_edi(server_t *server, egg_t *egg)
{
	char buffer[1024] = {0};

	snprintf(buffer, 1024, "edi %li\n", egg->id);
	add_to_gui_queue(&server->gui, buffer);
}