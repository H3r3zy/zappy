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

#define READ_SIZE (16)

typedef enum {
	Linemate,
	Deraumere,
	Sibur,
	Mendiane,
	Phiras,
	Thystame,
	Food,
	Client,
} entity_type_t;

#define LIMIT_TASK_NUMBER (10)

typedef struct {
	uint x;
	uint y;
} pos_t;

typedef struct {
	ulong id;
	entity_type_t type;
	pos_t pos;
} entity_t;

typedef struct {
	uint x;
	uint y;
	uint level;
	uint vision;
	uint bag[7];
} user_t;

typedef struct client_s client_t;
typedef struct server_s server_t;

typedef struct {
	long long int started_time;
	long long int resting_time;
	char *command;
	void (*function)(server_t *server, client_t *invoker, char *command);
} scheduler_t;

struct client_s {
	socket_t fd;
	user_t user;
	scheduler_t *task[LIMIT_TASK_NUMBER];
	char *queue[LIMIT_TASK_NUMBER + 1];
	size_t queue_index;
	struct client_s *prev;
	struct client_s *next;
};

typedef struct teams_s {
	char *name;
	client_t **clients;
	struct teams_s *prev;
	struct teams_s *next;
} teams_t;

typedef struct {
	pos_t size;
	ulong max_id;
	entity_t **map;
} map_t;

struct server_s {
	socket_t fd;
	ushort port;
	uint freq;
	uint max_clients_per_teams;
	map_t map;
	teams_t *teams;
	client_t *clients;
	ssize_t client_nb;
};

char *gnl(int fd, char *delim);

int init_server(server_t *serv);
int server(server_t *serv);
void destroy_server(server_t *serv);

void server_loop(server_t *server);
void disconnect(server_t *server, client_t *client);

void add_teams(server_t *server, char *name);
void create_teams_clients(server_t *server);

void init_client(server_t *server, client_t *client);
void read_client(server_t *server, client_t *client);
void add_to_queue(client_t *client, char *msg);
void send_responses(client_t *client);

#endif //PSU_ZAPPY_2017_SERVER_H
