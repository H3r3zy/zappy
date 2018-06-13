/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <memory.h>
#include <server.h>
#include <stdio.h>
#include "server.h"
#include "debug.h"
#include "server.h"

void add_teams(server_t *server, char *name)
{
	teams_t *team = server->teams;
	teams_t *new = malloc(sizeof(teams_t));

	if (!new)
		return;
	new->name = strdup(name);
	if (!team) {
		server->teams = new;
		new->next = NULL;
		new->prev = NULL;
		return;
	}
	new->next = team->next;
	if (team->next)
		team->next->prev = new;
	team->next = new;
	new->prev = team;
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

static void add_client_to_team(server_t *server, client_t *client, teams_t *team)
{
	char buffer[128] = {0};

	for (uint i = 0; i < server->max_clients_per_teams; i++) {
		if (team->clients[i] == NULL) {
			team->clients[i] = client;
			team->remaining_place--;
			client->team = team;
			sprintf(buffer, "%i\n%i %i\n", team->remaining_place,
			server->map.size.x, server->map.size.y);
			add_to_queue(client, strdup(buffer));
			return;
		}
	}
	add_to_queue(client, strdup("ko\n"));
}

void add_to_team(server_t *server, client_t *client, char *name)
{
	for (teams_t *tm = server->teams; tm; tm = tm->next) {
		if (strcmp(tm->name, name) == 0) {
			add_client_to_team(server, client, tm);
			return;
		}
	}
	add_to_queue(client, strdup("ko\n"));
}