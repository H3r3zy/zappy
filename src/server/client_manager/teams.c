/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdlib.h>
#include <memory.h>
#include <server.h>
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
		team->clients = calloc(server->max_clients_per_teams,
			sizeof(client_t *));
		debug(GINFO "Team '%s' created\n", team->name);
	}
}