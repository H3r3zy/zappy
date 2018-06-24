/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** server.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <debug.h>
#include "server.h"

/**
* GUI command : get time unit
* @param server
* @param arg
*
* @response sgt srvFreq<uint32_t>
*/
void gui_sgt(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[11] = "sgt freq\n";
	int idx = 4;

	write_uint32(buff, &idx, server->freq);
	buff[idx] = -5;
	add_to_gui_queue(&server->gui, buff, idx + 1);
}

/**
* GUI command : set time unit
* @param server
* @param arg
*/
void gui_sst(server_t *server, char *arg)
{
	char *err = NULL;
	long freq;

	if (arg) {
		freq = strtol(arg, &err, 10);
		if (*err) {
			add_to_gui_queue(&server->gui, GUI_KO, 3);
			return;
		}
		server->freq = (uint32_t)freq;
		add_to_gui_queue(&server->gui, GUI_OK, 3);
	}
}

/**
* GUI command : get all team names
* @param server
* @param arg
*/
void gui_tna(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[262] = {0};
	static char end[] = {'e', 'n', 'd', 't', 'n', 'a', -5};
	int len = 0;

	for (teams_t *team = server->teams; team; team = team->next) {
		len = snprintf(buff, 262, "tna %s", team->name);
		buff[len] = -5;
		add_to_gui_queue(&server->gui, buff, 5 + strlen(team->name));
	}
	add_to_gui_queue(&server->gui, (char *)end, 3);
}

/**
* GUI response when a resource is generate
* @param server
* @param pos
* @param type
*
* @response sgr posX<uint32_t> posY<uint32_t> type<uint32_t>
*/
void gui_sgr(server_t *server, pos_t *pos, entity_type_t type)
{
	static char buffer[20] = "sgr posX posY enID\n";
	int idx = 4;

	write_uint32(buffer, &idx, (uint32_t) pos->x);
	idx++;
	write_uint32(buffer, &idx, (uint32_t) pos->x);
	idx++;
	write_uint32(buffer, &idx, (uint32_t) type);
	buffer[idx] = -5;
	add_to_gui_queue(&server->gui, buffer, 20);
}