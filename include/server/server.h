/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_SERVER_H
#define PSU_ZAPPY_2017_SERVER_H

#include <unistd.h>
#include "socket.h"

typedef struct {
	uint width;
	uint height;
} map_t;

typedef struct {
	uint x;
	uint y;
	uint level;
} user_t;

typedef struct client_s {
	socket_t fd;
	user_t user;
	struct client_s *prev;
	struct client_s *next;
} client_t;

typedef struct teams_s {
	char *name;
	client_t **clients;
	struct teams_s *prev;
	struct teams_s *next;
} teams_t;

typedef struct {
	socket_t fd;
	ushort 	port;
	uint	freq;
	uint max_clients_per_teams;
	map_t	map;
	teams_t *teams;
	client_t *clients;
	ssize_t client_nb;
} server_t;

int server(server_t *serv);
void disconnect(server_t *server, client_t *client);

void add_teams(server_t *server, char *name);
void create_teams_clients(server_t *server);

void read_client(server_t *server, client_t *client);

#endif //PSU_ZAPPY_2017_SERVER_H
