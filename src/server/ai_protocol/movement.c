/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <server.h>
#include <gui_command.h>

/**
* Move up one tile
* @param server
* @param client
* @param arg
*/
void forward_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg
)
{
	remove_player_from_map(&server->map, client->entity);
	switch (client->user.orientation) {
	case TOP:
		client->entity->pos.y =
			(!client->entity->pos.y) ? server->map.size.y - 1 :
				client->entity->pos.y - 1;
		break;
	case RIGHT:
		client->entity->pos.x =
			(client->entity->pos.x == server->map.size.x - 1) ? 0 :
				client->entity->pos.x + 1;
		break;
	case BOTTOM:
		client->entity->pos.y =
			(client->entity->pos.y == server->map.size.y - 1) ? 0 :
				client->entity->pos.y + 1;
		break;
	case LEFT:
		client->entity->pos.x =
			(!client->entity->pos.x) ? server->map.size.x - 1 :
				client->entity->pos.x - 1;
		break;
	}
	add_player_to_map(&server->map, client->entity);
	gui_pmv(server, client);
	add_to_queue(client, "ok\n");
}

/**
* Turn -90° the player (top -> left)
* @param server
* @param client
* @param arg
*/
void left_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg
)
{
	if (client->user.orientation != TOP)
		--client->user.orientation;
	else
		client->user.orientation = LEFT;
	gui_ptu(server, client);
	add_to_queue(client, "ok\n");
}

/**
* Turn 90° the player (top -> right)
* @param server
* @param client
* @param arg
*/
void right_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg
)
{
	if (client->user.orientation != LEFT)
		++client->user.orientation;
	else
		client->user.orientation = TOP;
	gui_ptu(server, client);
	add_to_queue(client, "ok\n");
}

void pos(__attribute__((unused)) server_t *server, client_t *client,
	__attribute__((unused)) char *arg
)
{
	char response[13] = {0};

	snprintf(response, 13, "%d;%d (%d)\n", client->entity->pos.x,
		client->entity->pos.y, client->user.orientation);
	add_to_queue(client, response);
}

void setpos_cmd(server_t *server, client_t *client, char *arg)
{
	uint32_t dx = atoi(arg);
	uint32_t dy = atoi(strchr(arg, ';') + 1);

	remove_player_from_map(&server->map, client->entity);
	client->entity->pos.x = dx;
	client->entity->pos.y = dy;
	add_player_to_map(&server->map, client->entity);
}