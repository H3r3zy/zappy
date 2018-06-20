/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <gui_command.h>
#include "server.h"
#include "debug.h"

void die(server_t *server, client_t *client)
{
	debug(GINFO "'%i' die\n", client->fd);
	write(client->fd, "dead\n", 5);
	gui_pdi(server, client);
	disconnect(server, client);
}