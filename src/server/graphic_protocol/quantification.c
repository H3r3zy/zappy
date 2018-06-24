/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** quantification.c
*/

#include <stdio.h>
#include <string.h>
#include <server.h>
#include "server.h"

/**
* GUI command : get number of clients
* @param server
* @param arg
*
* @response nbu nbclients:4
*/
void gui_nbu(server_t *server, __attribute__((unused)) char *arg)
{
	static char buff[10] = "nbu nbus\n";
	int idx = 4;

	write_uint32(buff, &idx, server->client_nb);
	buff[idx] = -5;
	add_to_gui_queue(&server->gui, buff, idx + 1);
}

/**
* GUI command : get the number of teams
* @param server
* @param arg
*
* @response nbt nbteam:4
*/
void gui_nbt(server_t *server, __attribute__((unused)) char *arg)
{
	static char buff[10] = "nbt nbte\n";
	int idx = 4;
	uint32_t n = 0;

	for (teams_t *team = server->teams; team; team = team->next)
		++n;
	write_uint32(buff, &idx, n);
	buff[idx] = -5;
	add_to_gui_queue(&server->gui, buff, idx + 1);
}

/**
* GUI command : get the number of resources
* @param server
* @param arg
*
* @response nbr line:4 dera:4 sibu:4 mend:4 phir:4 thys:4 food:4 eggs:4
*/
void gui_nbr(server_t *server, __attribute__((unused)) char *arg)
{
	static char buff[55] = "nbr line dera sibu mend phir thys food eggs\n";
	int idx = 4;

	for (size_t i = 0; i < RESOURCE_NB + 1; i++) {
		write_uint32(buff, &idx, server->map.stock[i]);
		idx++;
	}
	buff[idx] = -5;
	add_to_gui_queue(&server->gui, buff, idx);
}