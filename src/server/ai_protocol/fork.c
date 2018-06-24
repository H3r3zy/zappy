/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <time.h>
#include <stdlib.h>
#include "gui_command.h"
#include "debug.h"
#include "scheduler.h"

static void init_egg(server_t *server, egg_t *egg, client_t *client, ms_t now)
{
	static uint32_t id = 2;

	egg->started_time = now;
	egg->client = NULL;
	egg->team = client->team;
	add_slot_in_team(client->team);
	egg->pos.x = client->entity->pos.x;
	egg->pos.y = client->entity->pos.y;
	egg->next = client->team->eggs;
	if (egg->next)
		egg->next->prev = egg;
	egg->prev = NULL;
	egg->id = id;
	client->team->eggs = egg;
	gui_pfk(server, client);
	id++;
}

void fork_cmd(__attribute__((unused)) server_t *server, client_t *client,
	__attribute__((unused)) char *arg
)
{
	struct timespec spec;
	egg_t *egg = malloc(sizeof(egg_t));
	ms_t now;

	debug(GINFO "'%i' place an egg in (%i;%i)\n", client->fd,
		client->entity->pos.y, client->entity->pos.x);
	if (!egg) {
		debug(ERROR "Can't place egg (Malloc failed)\n");
		add_to_queue(client, "ko\n");
		return;
	}
	clock_gettime(CLOCK_REALTIME, &spec);
	now = spec.tv_sec * STOMS + spec.tv_nsec / NTOMS;
	init_egg(server, egg, client, now);
	add_to_queue(client, "ok\n");
}