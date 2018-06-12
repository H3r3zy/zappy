/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_COMMAND_H
#define PSU_ZAPPY_2017_COMMAND_H

#include <stdbool.h>
#include "server.h"

typedef struct {
	char *name;
	void (*function)(server_t *server, client_t *client, char *arg);
	bool (*verify)(server_t *server, client_t *client, char *arg);
	uint time_unit;
	bool argument;
} command_t;

void inventory(server_t *server, client_t *client, char *arg);

#endif //PSU_ZAPPY_2017_COMMAND_H
