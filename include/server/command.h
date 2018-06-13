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

void inventory_cmd(server_t *server, client_t *client, char *arg);
void forward_cmd(server_t *server, client_t *client, char *arg);
void left_cmd(server_t *server, client_t *client, char *arg);
void right_cmd(server_t *server, client_t *client, char *arg);
void look_cmd(server_t *server, client_t *client, char *arg);
void connect_nbr_cmd(server_t *server, client_t *client, char *arg);
void take_cmd(server_t *server, client_t *client, char *arg);

#ifdef DEBUG
void pos(server_t *server, client_t *client, char *arg);
#endif

#endif //PSU_ZAPPY_2017_COMMAND_H
