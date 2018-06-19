/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <time.h>
#include <stdlib.h>
#include <gui_command.h>
#include "debug.h"
#include "scheduler.h"
#include "server.h"

void fork_cmd(server_t *__attribute__((unused))server, client_t *client, char *__attribute__((unused))arg)
{
	struct timespec spec;
	egg_t *egg = malloc(sizeof(egg_t));
	static uint32_t id = 2;

	debug(GINFO "'%i' place an egg in (%i;%i)\n", client->fd, client->entity->pos.y, client->entity->pos.x);
	if (!egg) {
		debug(ERROR "Can't place egg (Malloc failed)\n");
		add_to_queue(client, "ko\n");
		return;
	}
	clock_gettime(CLOCK_REALTIME, &spec);
	egg->started_time = spec.tv_sec * STOMS + spec.tv_nsec / NTOMS;
	egg->client = NULL;
	egg->team = client->team;
	egg->pos.x = client->entity->pos.x;
	egg->pos.y = client->entity->pos.y;
	egg->next = client->team->eggs;
	if (egg->next)
		egg->next->prev = egg;
	egg->prev = NULL;
	egg->id = id;
	client->team->eggs = egg;
	gui_pfk(server, client);
	add_to_queue(client, "ok\n");
	id++;
}