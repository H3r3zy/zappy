/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <server.h>
#include <memory.h>
#include <debug.h>
#include "server.h"

static client_t *get_client_by_id(server_t *server, size_t id)
{
	for (client_t *clt = server->clients; clt; clt = clt->next)
		if (clt->entity->id == id)
			return clt;
	return NULL;
}

/**
*
* @param server
* @param client
*
* @response pnw clientID<uint32_t> posX<uint32_t> posY<uint32_t>
* 	orientation<uint32_t> team<string>
*/
void gui_pnw(server_t *server, client_t *client)
{
	static char buff[281] = "pnw clID POSX POSY CLOR CLVL \n";
	int idx = 4;

	write_uint32(buff, &idx, client->entity->id);
	idx++;
	write_uint32(buff, &idx, (uint32_t) POS(client).x);
	idx++;
	write_uint32(buff, &idx, (uint32_t) POS(client).y);
	idx++;
	write_uint32(buff, &idx, OR(client) + 1);
	idx++;
	write_uint32(buff, &idx, client->user.level);
	idx++;
	buff[idx] = '\0';
	strcat(buff, client->team ? client->team->name : "");
	strcat(buff, "\n");
	add_to_gui_queue(&server->gui, buff);
}

/**
*
* @param server
* @param arg
*
* @response ppo clientID<uint32_t> posX<uint32_t> posY<uint32_t>
*/
void gui_ppo(server_t *server, char *arg, __attribute__((unused)) bool *status)
{
	uint32_t id = atoi(arg);
	static char buff[22] = "ppo clID posX posY\n";
	int idx = 4;
	client_t *player = get_client_by_id(server, id);

	if (player) {
		write_uint32(buff, &idx, id);
		idx++;
		write_uint32(buff, &idx, (uint32_t) POS(player).x);
		idx++;
		write_uint32(buff, &idx, (uint32_t) POS(player).y);
		add_to_gui_queue(&server->gui, buff);
	} else
		add_to_gui_queue(&server->gui, "ko\n");
}

/**
*
* @param server
* @param arg
*
* @ersponse plv clientID<uint32_t> level<uint32_t>
*/
void gui_plv(server_t *server, char *arg, __attribute__((unused)) bool *status)
{
	uint32_t id = atoi(arg);
	static char buff[16] = "plv clID plvl\n";
	client_t *player = get_client_by_id(server, id);
	int idx = 4;

	if (player) {
		write_uint32(buff, &idx, id);
		idx++;
		write_uint32(buff, &idx, player->user.level);
		add_to_gui_queue(&server->gui, buff);
	} else
		add_to_gui_queue(&server->gui, "ko\n");
}

/**
*
* @param server
* @param arg
*
* @response pin clientID<uint32_t> posX<uint32_t> posY<uint32_t>
* 	food<uint32_t> linemate<uint32_t> deraumere<uint32_t> sibur<uint32_t>
* 	mendiane<uint32_t> phiras<uint32_t> thystame<uint32_t>
*/
void gui_pin(server_t *server, char *arg, __attribute__((unused)) bool *status)
{
	uint32_t id = atoi(arg);
	static char buff[55] = "pin clid posx posy food line dera sibu mend "
		"phir thys\n";
	int idx = 4;
	client_t *clt = get_client_by_id(server, id);

	if (clt) {
		write_uint32(buff, &idx, id);
		idx++;
		write_uint32(buff, &idx, (uint32_t) POS(clt).x);
		idx++;
		write_uint32(buff, &idx, (uint32_t) POS(clt).y);
		idx++;
		write_uint32(buff, &idx, clt->user.bag[Food]);
		idx++;
		for (uint i = 1; i <= Thystame; i++) {
			write_uint32(buff, &idx, clt->user.bag[i]);
			idx++;
		}
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
	static char buffer[124] = "pex clId\n";
	int idx = 4;

	write_uint32(buffer, &idx, client->entity->id);
	add_to_gui_queue(&server->gui, buffer);
}

/**
* Response to GUI when a broadcast is call
* @param server
* @param client
* @param arg
*
* @response pbc clientID<uint32_t> message<string>\n
*/
void gui_pbc(server_t *server, client_t *client, char *arg)
{
	char *buffer = malloc(sizeof(char) * (strlen(arg) + 26));
	int idx = 4;

	if (!buffer)
		return;
	memcpy(buffer, "pbc ", 4);
	write_uint32(buffer, &idx, client->entity->id);
	buffer[idx] = ' ';
	buffer[idx + 1] = 0;
	strcat(buffer, arg);
	strcat(buffer, "\n");
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
	static char buffer[1024] = "pic posX posY ";
	int idx = 4;

	write_uint32(buffer, &idx, (uint32_t) POS(client).x);
	++idx;
	write_uint32(buffer, &idx, (uint32_t) POS(client).y);
	for (entity_t *en = entity; en && idx + 5 < 1022; en = en->next) {
		buffer[idx++] = ' ';
		write_uint32(buffer, &idx, en->id);
	}
	buffer[idx++] = '\n';
	buffer[idx++] = 0;
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
	static char buffer[1024] = "pie posX posY clvl\n";
	int idx = 4;

	write_uint32(buffer, &idx, (uint32_t) POS(client).x);
	++idx;
	write_uint32(buffer, &idx, (uint32_t) POS(client).y);
	++idx;
	write_uint32(buffer, &idx, client->user.level);
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
	static char buffer[1024] = "pfk clID\n";
	int idx = 4;

	write_uint32(buffer, &idx, client->entity->id);
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
	static char buffer[1024] = "pdr clID enTp\n";
	int idx = 4;

	write_uint32(buffer, &idx, client->entity->id);
	++idx;
	write_uint32(buffer, &idx, type);
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
void gui_pgt(server_t *server, client_t *client, entity_type_t type)
{
	static char buffer[1024] = "pgt clID enTy\n";
	int idx = 4;

	write_uint32(buffer, &idx, client->entity->id);
	++idx;
	write_uint32(buffer, &idx, type);
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
	static char buffer[1024] = "pdi clID\n";
	int idx = 4;

	write_uint32(buffer, &idx, client->entity->id);
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
	static char buffer[1024] = "enw egID clID posX posY\n";
	int idx = 4;

	write_uint32(buffer, &idx, egg->id);
	++idx;
	write_uint32(buffer, &idx, client->entity->id);
	++idx;
	write_uint32(buffer, &idx, (uint32_t) POS(client).x);
	++idx;
	write_uint32(buffer, &idx, (uint32_t) POS(client).y);
	++idx;
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
	static char buffer[1024] = "eht egID\n";
	int idx = 4;

	write_uint32(buffer, &idx, egg->id);
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
	char buffer[1024] = "ebo egID\n";
	int idx = 4;

	write_uint32(buffer, &idx, egg->id);
	add_to_gui_queue(&server->gui, buffer);
}

/**
* Response to GUI when an egg is destroyed
* @param server
* @param egg
*
* @response edi eggID<uint32_t>
*/
void gui_edi(server_t *server, egg_t *egg)
{
	char buffer[10] = "edi egID\n";
	int idx = 4;

	write_uint32(buffer, &idx, egg->id);
	add_to_gui_queue(&server->gui, buffer);
}