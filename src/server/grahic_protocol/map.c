/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <server.h>
#include <debug.h>
#include "server.h"

void gui_msz(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[16] = {0};

	snprintf(buff, 16, "msz %u;%u\n", server->map.size.x,
		server->map.size.y);
	add_to_gui_queue(&server->gui, buff);
}

static void print_map_cell(server_t *server, size_t x, size_t y)
{
	char buff[50] = {0};
	uint *items = server->map.map[y][x].items;

	snprintf(buff, 55, "bct %zu %zu %u %u %u %u %u %u %u\n", x, y,
		items[Food], items[Linemate], items[Deraumere],
		items[Sibur], items[Mendiane], items[Phiras],
		items[Thystame]);
	add_to_gui_queue(&server->gui, buff);
}

void gui_bct(server_t *server, char *arg)
{
	long x = strtol(arg, NULL, 10);
	long y = strtol(strchr(arg, ' ') + 1, NULL, 10);

	if (x < 0 || y < 0 || x >= server->map.size.x ||
		y >= server->map.size.y)
		add_to_gui_queue(&server->gui, "ko\n");
	else
		print_map_cell(server, (size_t)x, (size_t)y);
}

void gui_mct(server_t *server, __attribute__((unused)) char *arg)
{
	for (int y = 0; y < server->map.size.y; y++)
		for (int x = 0; x < server->map.size.x; x++)
			print_map_cell(server, x, y);
}