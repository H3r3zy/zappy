/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "server.h"
#include "gui_command.h"
#include "debug.h"
#include "command.h"

const char angles[] = {
	'1',
	'8',
	'7',
	'6',
	'5',
	'4',
	'3',
	'2',
};

/**
* Determine from which tile comes the broadcast message,
* based on the oriented angle between from & to vectors
* @param from
* @param to
* @param vf_x
* @param vf_y
* @return
*/
static char calcul_broadcast_tile(orientation_t orientation, int vf_x,
	int vf_y
)
{
	int vt_x = (orientation % 2 != 0) ? -(orientation - 2) : 0;
	int vt_y = (orientation % 2 == 0) ? orientation - 1 : 0;
	double angle = atan2(vt_y, vt_x) - atan2(vf_y, vf_x);
	double m;

	if (angle < 0)
		angle += 2 * M_PI;
	angle = (angle <= M_PI) ? M_PI - angle : 3 * M_PI - angle;
	if (angle >= 2 * M_PI - M_PI_8 || angle < M_PI_8)
		return '1';
	for (short i = 1; i < 8; i++) {
		m = i * M_PI_4;
		if (angle >= m - M_PI_8 && angle < m + M_PI_8)
			return angles[i];
	}
	return '1';
}

/**
* Get the broadcast tile
* 	0 if sender and receiver are on the same cell
* 	calcul it otherwise
* @param from
* @param clt
* @param vf_x
* @param vf_y
* @return
*/
static char get_broadcast_tile(pos_t *from, client_t *clt, int vf_x, int vf_y)
{
	if (from->x == clt->entity->pos.x && from->y == clt->entity->pos.y)
		return '0';
	return calcul_broadcast_tile(clt->user.orientation, vf_x, vf_y);
}

/**
* Send a broadcast message to all clients, and indicate the orientation
* @param server
* @param client
* @param arg
*/
void broadcast_cmd(server_t *server, client_t *client, char *arg)
{
	pos_t *pos = &client->entity->pos;
	char *response = malloc(13 + strlen(arg));
	pos_t d = {0};
	char tile;

	sprintf(response, "message 0, %s\n", arg);
	for (client_t *clt = server->clients; clt; clt = clt->next) {
		if (clt != client) {
			d.x = MAP_SHORTEST_PATH(POS(clt).x - pos->x,
				server->map.size.x);
			d.y = MAP_SHORTEST_PATH(POS(clt).y - pos->y,
				server->map.size.y);
			tile = get_broadcast_tile(pos, clt, d.x, d.y);
			response[8] = tile;
			add_to_queue(clt, response);
		}
	}
	free(response);
	add_to_queue(client, "ok\n");
	gui_pbc(server, client, arg);
}