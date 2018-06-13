/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include <stdio.h>
#include <server.h>
#include "server.h"

void inventory_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg)
{
	char response[106] = {0};

	snprintf(response, 106, "[food %d, linemate %d, deraumere %d, sibur "
			 "%d, mendiane %d, phiras %d, thystame %d]\n",
		client->user.bag[Food], client->user.bag[Linemate],
		client->user.bag[Deraumere], client->user.bag[Sibur],
		client->user.bag[Mendiane], client->user.bag[Phiras],
		client->user.bag[Thystame]);
	add_to_queue(client, response);
}