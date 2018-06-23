/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include "server.h"
#include "gui_command.h"

/**
* Response to GUI when a client move
* @param server
* @param client
*
* @response pmv clientID<uint32_t> posX<uint32_t> posY<uint32_t>
* 	orientation<uint32_t>(1: TOP, 2: RIGHT, 3: BOTTOM, 4: LEFT)
*/
void gui_pmv(server_t *server, client_t *client)
{
	static char buff[25] = "pmv clID posX posY clOR\n";
	int idx = 4;

	write_uint32(buff, &idx, client->entity->id);
	idx++;
	write_uint32(buff, &idx, (uint32_t) POS(client).x);
	idx++;
	write_uint32(buff, &idx, (uint32_t) POS(client).y);
	idx++;
	write_uint32(buff, &idx, (uint32_t) OR(client) + 1);
	buff[idx] = -5;
	add_to_gui_queue(&server->gui, buff, idx + 1);
}

/**
* Response to GUI when a player turn (LEFT or RIGHT)
* @param server
* @param client
*
* @response ptu clientID<uint32_t>
* 	orientation<uint32_t>(1: TOP, 2: RIGHT, 3: BOTTOM, 4: LEFT)
*/
void gui_ptu(server_t *server, client_t *client)
{
	static char buff[15] = "ptu clID clOR\n";
	int idx = 4;

	write_uint32(buff, &idx, client->entity->id);
	idx++;
	write_uint32(buff, &idx, (uint32_t) OR(client) + 1);
	buff[idx] = -5;
	add_to_gui_queue(&server->gui, buff, idx + 1);
}