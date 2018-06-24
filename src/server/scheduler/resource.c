/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <math.h>
#include <time.h>
#include <server.h>
#include "debug.h"
#include "server.h"
#include "scheduler.h"
#include "gui_command.h"

static void generate_resource(server_t *server)
{
	pos_t pos;
	entity_type_t id;

	for (uint i = 0; i < server->client_nb * 2; ++i) {
		pos = (pos_t){rand() % server->map.size.x,
			rand() % server->map.size.y};
		id = Food;
		update_resource(&server->map, &pos, id, 1);
		gui_sgr(server, &pos, id);
	}
	for (uint i = 0; i < server->client_nb * 2; ++i) {
		pos = (pos_t){rand() % server->map.size.x,
			rand() % server->map.size.y};
		id = rand() % RESOURCE_NB;
		update_resource(&server->map, &pos, id, 1);
		gui_sgr(server, &pos, id);
	}
}

void schedule_resource_generator(server_t *server, ms_t now)
{
	static long long int started_time = -1;

	if (started_time == -1)
		started_time = now;
	if (now > (started_time + UNITTOMS(126, server->freq))) {
		generate_resource(server);
		started_time = now;
	}
}