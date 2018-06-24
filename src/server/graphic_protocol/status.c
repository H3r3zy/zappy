/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** stat.c
*/

#include <string.h>
#include <debug.h>
#include "server.h"

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
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
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

	write_uint32(buffer, &idx, (uint32_t)POS(client).x);
	++idx;
	write_uint32(buffer, &idx, (uint32_t)POS(client).y);
	for (entity_t *en = entity; en && idx + 5 < 1022; en = en->next) {
		buffer[idx++] = ' ';
		write_uint32(buffer, &idx, en->id);
	}
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
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

	write_uint32(buffer, &idx, (uint32_t)POS(client).x);
	++idx;
	write_uint32(buffer, &idx, (uint32_t)POS(client).y);
	++idx;
	write_uint32(buffer, &idx, client->user.level);
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
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
	write_uint32(buff, &idx, (uint32_t)POS(client).x);
	idx++;
	write_uint32(buff, &idx, (uint32_t)POS(client).y);
	idx++;
	write_uint32(buff, &idx, OR(client) + 1);
	idx++;
	write_uint32(buff, &idx, client->user.level);
	idx++;
	if (strlen(client->team->name))
		memcpy(buff + idx, client->team->name,
			strlen(client->team->name));
	buff[idx + strlen(client->team->name)] = -5;
	add_to_gui_queue(&server->gui, buff,
		idx + strlen(client->team->name) + 1);
}
