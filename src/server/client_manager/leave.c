/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdlib.h>
#include "gui_command.h"
#include "debug.h"
#include "egg.h"

static void drop_player_ressource(server_t *server, client_t *client)
{
	for (uint i = 0; i < RESOURCE_NB; ++i) {
		while (client->user.bag[i]) {
			update_resource(&server->map, &client->entity->pos, i,
				1);
			gui_pdr(server, client, i);
			client->user.bag[i]--;
		}
	}
}

static void disconnect_of_team(__attribute__((unused)) server_t *server,
	teams_t *team, client_t *client
)
{
	for (uint32_t i = 0; i < team->client_max; i++) {
		if (team->clients[i] == client) {
			debug(INFO "the client %d left the team '%s'\n",
				client->fd, team->name);
			team->remaining_place++;
			team->clients[i] = NULL;
		}
	}
}

static void disconnect_of_teams(server_t *server, client_t *client)
{
	for (teams_t *team = server->teams; team; team = team->next)
		if (team == client->team)
			disconnect_of_team(server, team, client);
}

void disconnect(server_t *server, client_t *client)
{
	debug(INFO "The client %d left the game\n", client->fd);
	if (client->status == EGG)
		remove_egg(get_egg_of(client));
	drop_player_ressource(server, client);
	if (server->clients == client)
		server->clients = client->next;
	if (client->prev)
		client->prev->next = client->next;
	if (client->next)
		client->next->prev = client->prev;
	if (server->teams && client->team) {
		disconnect_of_teams(server, client);
		remove_player_from_map(&server->map, client->entity);
	}
	gui_pdi(server, client);
	shutdown(client->fd, SHUT_RDWR);
	close(client->fd);
	free(client->entity);
	free(client);
	server->client_nb--;
}