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

/**
 * GUI command : get map size
 * @param server
 * @param arg
 */
void gui_msz(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[16] = {0};

	snprintf(buff, 16, "msz %u;%u\n", server->map.size.x,
		server->map.size.y);
	add_to_gui_queue(&server->gui, buff);
}

/**
 * Print the content of a cell into a buffer
 * @param server
 * @param x
 * @param y
 */
static void print_map_cell(server_t *server, uint x, uint y)
{
	static char buff[50] = "bct xpos ypos food line dera sibu mend phir thys\n";
	uint *items = server->map.map[y][x].items;

	memcpy(buff + 4, &x, sizeof(uint));
	memcpy(buff + 9, &y, sizeof(uint));
	for (size_t i = 0; i < RESOURCE_NB; i++) {
		memcpy(buff + 14 + i * (sizeof(uint) + 1), &items[i],
			sizeof(uint));

	}
	add_to_gui_queue(&server->gui, buff);
}

/**
 * GUI command : get cell content at pos X Y
 * @param server
 * @param arg
 */
void gui_bct(server_t *server, char *arg)
{
	long x = strtol(arg, NULL, 10);
	long y = strtol(strchr(arg, ' ') + 1, NULL, 10);

	if (x < 0 || y < 0 || x >= server->map.size.x ||
		y >= server->map.size.y)
		add_to_gui_queue(&server->gui, "ko\n");
	else
		print_map_cell(server, x, y);
}

/**
 * GUI command : get full map content
 * @param server
 * @param arg
 */
void gui_mct(server_t *server, __attribute__((unused)) char *arg)
{
	for (int y = 0; y < server->map.size.y; y++)
		for (int x = 0; x < server->map.size.x; x++)
			print_map_cell(server, x, y);
}