/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <server.h>
#include "server.h"
#include "scheduler.h"
#include "gui_command.h"
#include "debug.h"

void add_teams(server_t *server, char *name)
{
	teams_t *team = server->teams;
	teams_t *new = malloc(sizeof(teams_t));

	if (!new)
		return;
	new->eggs = NULL;
	new->name = strdup(name);
	if (!team) {
		server->teams = new;
		new->next = NULL;
		return;
	}
	new->next = team->next;
	team->next = new;
}

void create_teams_clients(server_t *server)
{
	for (teams_t *team = server->teams; team; team = team->next) {
		team->remaining_place = server->max_clients_per_teams;
		team->clients = calloc(server->max_clients_per_teams,
			sizeof(client_t *));
		debug(GINFO "Team '%s' created\n", team->name);
	}
}

static void spawn(server_t *server, client_t *client, teams_t *team)
{
	for (egg_t *egg = team->eggs; egg; egg = egg->next) {
		if (egg->client == NULL) {
			debug(INFO "Pop in an egg (%i,%i)\n", egg->pos.x,
				egg->pos.y);
			egg->client = client;
			client->entity->pos.x = egg->pos.x;
			client->entity->pos.y = egg->pos.y;
			client->status = EGG;
			gui_ebo(server, egg);
			return;
		}
	}
	gui_pnw(server, client);
	client->entity->pos.x = rand() % server->map.size.x;
	client->entity->pos.y = rand() % server->map.size.y;
}

static void add_client_to_team(server_t *server, client_t *client,
	teams_t *team)
{
	char buffer[128] = {0};
	struct timespec spec;

	for (uint32_t i = 0; i < server->max_clients_per_teams; i++) {
		if (team->clients[i] == NULL) {
			team->clients[i] = client;
			team->remaining_place--;
			client->team = team;
			spawn(server, client, team);
			clock_gettime(CLOCK_REALTIME, &spec);
			client->started_time =
				spec.tv_sec * STOMS + spec.tv_nsec / NTOMS;
			add_player_to_map(&server->map, client->entity);
			sprintf(buffer, "%i\n%i %i\n", team->remaining_place,
				server->map.size.x, server->map.size.y);
			add_to_queue(client, buffer);
			return;
		}
	}
	add_to_queue(client, "ko\n");
}

void add_to_team(server_t *server, client_t *client, char *name)
{
	for (teams_t *tm = server->teams; tm; tm = tm->next) {
		if (strcmp(tm->name, name) != 0)
			continue;
		add_client_to_team(server, client, tm);
		return;
	}
	add_to_queue(client, "ko\n");
}