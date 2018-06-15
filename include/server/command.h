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

typedef struct look_opt_s {
	uint vision;
	int d;
} look_opt_t;

typedef struct look_type_s {
	char *name;
	size_t len;
} look_type_t;

extern look_type_t ENTITY_NAMES[ENTITY_NB];

void inventory_cmd(server_t *server, client_t *client, char *arg);
void forward_cmd(server_t *server, client_t *client, char *arg);
void left_cmd(server_t *server, client_t *client, char *arg);
void right_cmd(server_t *server, client_t *client, char *arg);
void look_cmd(server_t *server, client_t *client, char *arg);
void connect_nbr_cmd(server_t *server, client_t *client, char *arg);
void take_cmd(server_t *server, client_t *client, char *arg);
void set_cmd(server_t *server, client_t *client, char *arg);
void fork_cmd(server_t *server, client_t *client, char *arg);
void incantation_cmd(server_t *server, client_t *client, char *arg);

bool incantation_verify(server_t *server, client_t *client, char *arg);


#ifdef DEBUG
void pos(server_t *server, client_t *client, char *arg);
#endif

#endif //PSU_ZAPPY_2017_COMMAND_H
