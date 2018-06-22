/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <server.h>
#include "server.h"

static void team_end(server_t *server, teams_t *team)
{
	uint nb = 0;

	for (uint i = 0; i < team->client_max; i++) {
		if (team->clients[i] && team->clients[i]->user.level == 8)
			nb++;
	}
	if (nb == 6)
		server->end = team;
}

void is_ended(server_t *server)
{
	for (teams_t *team = server->teams; team; team = team->next) {
		team_end(server, team);
	}
}