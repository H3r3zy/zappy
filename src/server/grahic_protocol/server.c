/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** server.c
*/

#include <stdio.h>
#include <stdlib.h>
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
	add_to_gui_queue(&server->gui, buff);
}

/**
* GUI command : set time unit
* @param server
* @param arg
*/
void gui_sst(server_t *server, char *arg)
{
	long freq = strtol(arg, NULL, 10);

	server->freq = (uint32_t)freq;
	add_to_gui_queue(&server->gui, "ok\n");
}

/**
* GUI command : get all team names
* @param server
* @param arg
*/
void gui_tna(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[262] = {0};

	for (teams_t *team = server->teams; team; team = team->next) {
		snprintf(buff, 262, "tna %s\n", team->name);
		add_to_gui_queue(&server->gui, buff);
	}
	add_to_gui_queue(&server->gui, "endtna\n");
}