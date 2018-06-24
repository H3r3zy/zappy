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

/**
* GUI command : get map size
* @param server
* @param arg
*
* @response msz sizeX:4 sizeY:4
*/
void gui_msz(server_t *server, __attribute__((unused)) char *arg,
	__attribute__((unused)) bool *status
)
{
	static char buff[16] = "msz mapX mapY\n";
	int idx = 4;

	write_uint32(buff, &idx, (uint32_t)server->map.size.x);
	++idx;
	write_uint32(buff, &idx, (uint32_t)server->map.size.y);
	buff[idx] = -5;
	add_to_gui_queue(&server->gui, buff, idx + 1);
}

/**
* Print the content of a cell into a buffer
* @param server
* @param x
* @param y
*/
static void print_map_cell(server_t *server, uint32_t x, uint32_t y)
{
	static char buff[50] = "bct xpos ypos food line dera "
			"sibu mend phir thys\n";
	uint32_t *items = server->map.map[y][x].items;

	memcpy(buff + 4, &x, sizeof(uint32_t));
	memcpy(buff + 9, &y, sizeof(uint32_t));
	for (size_t i = 0; i < RESOURCE_NB; i++) {
		memcpy(buff + 14 + i * (sizeof(uint32_t) + 1), &items[i],
			sizeof(uint32_t));
	}
	buff[49] = -5;
	add_to_gui_queue(&server->gui, buff, 50);
}

/**
* GUI command : get cell content at pos X Y
* @param server
* @param arg
*
* @response bct xpos:4 ypos:4 line:4 dera:4 sibu:4 mend:4 phir:4 thys:4 food:4
*/
void gui_bct(server_t *server, char *arg, __attribute__((unused)) bool *status)
{
	char *err = 0;
	long x = (arg) ? strtol(arg, &err, 10) : -1;
	long y = ((!*err || *err == ' ') && x > -1 && strchr(arg, ' ')) ?
		strtol(strchr(arg, ' ') + 1, &err, 10) : -1;

	if (!*err && x < server->map.size.x && y > -1 &&
		y < server->map.size.y)
		print_map_cell(server, x, y);
	else
		add_to_gui_queue(&server->gui, GUI_KO, 3);
}

int process_map_printing(server_t *server, pos_t *pos, uint32_t *cells_done,
	bool *status
)
{
	for (; pos->x < server->map.size.x; pos->x++) {
		print_map_cell(server, pos->x, pos->y);
		++(*cells_done);
		if (*cells_done >= 50) {
			*status = true;
			return 1;
		}
	}

	return 0;
}

/**
* GUI command : get full map content
* @param server
* @param arg
*
* @response bct xpos:4 ypos:4 line:4 dera:4 sibu:4 mend:4 phir:4 thys:4 food:4
* for each cell
*/
void gui_mct(server_t *server, __attribute__((unused)) char *arg, bool *status)
{
	static pos_t pos = {0};
	uint32_t cells_done = 0;

	for (; pos.y < server->map.size.y; pos.y++) {
		if (process_map_printing(server, &pos, &cells_done, status))
			return;
		pos.x = 0;
	}
	pos.x = 0;
	pos.y = 0;
	*status = false;
}