/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void connect_nbr_cmd(server_t *server, client_t *client,
	__attribute__((unused)) char *arg)
{
	char buffer[128] = "";

	sprintf(buffer, "%i\n", client->team->remaining_place);
	add_to_queue(client, buffer);
}