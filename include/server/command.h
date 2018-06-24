/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_COMMAND_H
#define PSU_ZAPPY_2017_COMMAND_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

typedef struct client_s client_t;
typedef struct server_s server_t;

#define M_PI_8 (M_PI_4 / 2)

#define MAP_SHORTEST_PATH(x, s) (((x) > (s) / 2) ? (x) - (s) : (x))

typedef struct {
	char *name;
	void (*function)(server_t *server, client_t *client, char *arg);
	bool (*verify)(server_t *server, client_t *client, char *arg);
	uint32_t time_unit;
	bool argument;
} command_t;

typedef struct look_opt_s {
	uint32_t vision;
	size_t *size;
	size_t *len;
	char **str;
	int d;
} look_opt_t;

typedef struct look_type_s {
	char *name;
	size_t len;
} look_type_t;

void inventory_cmd(server_t *server, client_t *client, char *arg);
void forward_cmd(server_t *server, client_t *client, char *arg);
void left_cmd(server_t *server, client_t *client, char *arg);
void right_cmd(server_t *server, client_t *client, char *arg);
void look_cmd(server_t *srv, client_t *client, char *arg);
void connect_nbr_cmd(server_t *server, client_t *client, char *arg);
void take_cmd(server_t *server, client_t *client, char *arg);
void set_cmd(server_t *server, client_t *client, char *arg);
void fork_cmd(server_t *server, client_t *client, char *arg);
void broadcast_cmd(server_t *server, client_t *client, char *arg);
void incantation_cmd(server_t *server, client_t *client, char *arg);
void eject_cmd(server_t *server, client_t *client, char *arg);

bool incantation_verify(server_t *server, client_t *client, char *arg);

#endif //PSU_ZAPPY_2017_COMMAND_H
