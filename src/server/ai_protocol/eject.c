/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <stdbool.h>
#include <stdio.h>
#include <server.h>
#include <gui_command.h>
#include "command.h"

/**
* Eject all the clients in the cell (not himself)
* @param server
* @param client
* @param ejected_to
* @param delta
* @return
*/
static bool eject_client(server_t *server, client_t *client, pos_t *ejected_to,
	pos_t *delta
)
{
	char buffer[124];
	entity_t *next;
	client_t *tmp;
	bool found = false;

	for (entity_t *en =
		server->map.map[POS(client).y][POS(client).x].players; en;) {
		next = en->next;
		tmp = en->ptr;
		if (tmp != client) {
			found = true;
			move_player_to(&server->map, en, ejected_to);
			snprintf(buffer, 124, "eject: %i\n",
				get_o_w_dlt(delta, OR(tmp)));
			add_to_queue(tmp, buffer);
			gui_pex(server, client);
		}
		en = next;
	}
	return found;
}

/**
* Eject all the player in the cell where the client is
* They are ejected in the direction he look
* @param server
* @param client
* @param arg
*/
void eject_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg
)
{
	pos_t ejected_to;
	pos_t delta;
	bool found;

	ejected_to = client->entity->pos;
	if (OR(client) == TOP)
		ejected_to.y = ejected_to.y == 0 ? server->map.size.y - 1 :
			ejected_to.y - 1;
	if (OR(client) == LEFT)
		ejected_to.x = ejected_to.x == 0 ? server->map.size.x - 1 :
			ejected_to.x - 1;
	if (OR(client) == RIGHT)
		ejected_to.x = ejected_to.x == server->map.size.x - 1 ? 0 :
			ejected_to.x + 1;
	if (OR(client) == BOTTOM)
		ejected_to.y = ejected_to.y == server->map.size.y - 1 ? 0 :
			ejected_to.y + 1;
	fill_delta(&server->map.size, &POS(client), &ejected_to, &delta);
	found = eject_client(server, client, &ejected_to, &delta);
	add_to_queue(client, (found) ? "ok\n" : "ko\n");
}