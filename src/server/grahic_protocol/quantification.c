/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** quantification.c
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

/**
 * GUI command : get number of clients
 * @param server
 * @param arg
 *
 * @response nbu clts
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
 * @response nbt team
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
 * @response nbr food line dera sibu mend phir thys eggs
 */
void gui_nbr(server_t *server, __attribute__((unused)) char *arg)
{
	static char buff[50] = "nbr xpos ypos food line dera sibu mend phir thys\n";
	/*uint *items = server->map.map[y][x].items;

	memcpy(buff + 4, &x, sizeof(uint));
	memcpy(buff + 9, &y, sizeof(uint));
	for (size_t i = 0; i < RESOURCE_NB; i++) {
		memcpy(buff + 14 + i * (sizeof(uint) + 1), &items[i],
			sizeof(uint));

	}*/
	add_to_gui_queue(&server->gui, buff);
}