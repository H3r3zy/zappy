/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.c
*/

#include <stdio.h>
#include "server.h"

void gui_msz(server_t *server, __attribute__((unused)) char *arg)
{
	char buff[16] = {0};

	snprintf(buff, 16, "msz %u;%u\n", server->map.size.x,
		server->map.size.y);
	add_to_gui_queue(&server->gui, buff);
}