/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** egg.c
*/

#include "server.h"

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
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
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
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
}

/**
* Response to GUI when a player is spawning in an egg
* @param server
* @param egg
*
* @response ebo eggID
*/
void gui_ebo(server_t *server, egg_t *egg, client_t *client)
{
	char buffer[1024] = "ebo egID clID\n";
	int idx = 4;

	write_uint32(buffer, &idx, egg->id);
	++idx;
	write_uint32(buffer, &idx, client->entity->id);
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
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
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
}