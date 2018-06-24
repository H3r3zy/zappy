/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** action.c
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

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
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
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
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
}

/**
* Response to GUI when an egg is laying
* @param server
* @param client
*
* @response pfk clientID
*/
void gui_pfk(server_t *server, client_t *client, egg_t *egg)
{
	static char buffer[1024] = "pfk clID eggID\n";
	int idx = 4;

	write_uint32(buffer, &idx, client->entity->id);
	++idx;
	write_uint32(buffer, &idx, egg->id);
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
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
	buffer[idx++] = ' ';
	buffer[idx++] = 0;
	memcpy(buffer + idx, arg, strlen(arg));
	buffer[idx + strlen(arg)] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + strlen(arg) + 1);
	free(buffer);
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
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, idx + 1);
}