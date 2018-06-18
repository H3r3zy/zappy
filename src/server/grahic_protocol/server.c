/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** server.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void gui_nbu(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[10] = {0};

	snprintf(buff, 10, "nbu %lu\n", server->client_nb);
	add_to_gui_queue(&server->gui, buff);
}

void gui_nbt(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[10] = {0};
	size_t n = 0;

	for (teams_t *team = server->teams; team; team = team->next)
		++n;
	snprintf(buff, 10, "nbt %lu\n", n);
	add_to_gui_queue(&server->gui, buff);
}

void gui_sgt(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[11] = {0};

	snprintf(buff, 11, "sgt %u\n", server->freq);
	add_to_gui_queue(&server->gui, buff);
}

void gui_sst(server_t *server, char *arg)
{
	long freq = strtol(arg, NULL, 10);

	server->freq = (uint)freq;
	add_to_gui_queue(&server->gui, "ok\n");
}

void gui_tna(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[262] = {0};

	for (teams_t *team = server->teams; team; team = team->next) {
		snprintf(buff, 262, "tna %s\n", team->name);
		add_to_gui_queue(&server->gui, buff);
	}
	add_to_gui_queue(&server->gui, "endtna\n");
}