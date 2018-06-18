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
	char buff[10] = {0};

	snprintf(buff, 10, "nbu %u\n", server->client_nb);
	add_to_gui_queue(&server->gui, buff);
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
	char buff[10] = {0};
	uint n = 0;

	for (teams_t *team = server->teams; team; team = team->next)
		++n;
	snprintf(buff, 10, "nbt %u\n", n);
	add_to_gui_queue(&server->gui, buff);
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
	size_t i = 0;

	for (; i < RESOURCE_NB + 1; i++) {
		memcpy(buff + 14 + i * (sizeof(uint) + 1),
			&server->map.stock[i], sizeof(uint));

	}
	add_to_gui_queue(&server->gui, buff);
}