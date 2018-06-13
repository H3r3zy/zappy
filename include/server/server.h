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
#define LIMIT_TASK_NUMBER (10)
#define RESOURCE_NB (7)
#define ENTITY_NB ((RESOURCE_NB) + 1)
#define STARTED_FOOD (10)

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

typedef enum orientation_s {
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
} orientation_t;

typedef struct {
	uint x;
	uint y;
} pos_t;

typedef struct entity_s {
	ulong id;
	entity_type_t type;
	pos_t pos;
	struct entity_s *prev;
	struct entity_s *next;
} entity_t;

typedef struct {
	uint level;
	uint vision;
	uint bag[RESOURCE_NB];
	orientation_t orientation;
} user_t;

typedef struct client_s client_t;
typedef struct server_s server_t;
typedef struct teams_s teams_t;

typedef struct {
	long long int started_time;
	long long int spending_time;
	char *command;
	void (*function)(server_t *server, client_t *invoker, char *command);
} scheduler_t;

struct client_s {
	socket_t fd;
	user_t user;
	scheduler_t *task[LIMIT_TASK_NUMBER];
	teams_t *team;
	char *queue[LIMIT_TASK_NUMBER + 1];
	size_t queue_index;
	entity_t *entity;
	long long int started_time;
	struct client_s *prev;
	struct client_s *next;
};

struct teams_s {
	char *name;
	uint remaining_place;
	client_t **clients;
	struct teams_s *prev;
	struct teams_s *next;
};

typedef struct cell_s {
	uint items[RESOURCE_NB];
	entity_t *players;
} cell_t;

typedef struct {
	pos_t size;
	ulong max_id;
	cell_t **map;
} map_t;

#define UPDATE_RESOURCE(m, p, t, n) ((m)->map[(p).x][(p).y].items[(t)] += (n))

struct server_s {
	socket_t fd;
	ushort port;
	uint freq;
	uint max_clients_per_teams;
	map_t map;
	teams_t *teams;
	client_t *clients;
	size_t client_nb;
	scheduler_t *task[LIMIT_TASK_NUMBER];
};

extern char *str_types[ENTITY_NB];

char *gnl(int fd, char *delim);

int init_server(server_t *serv);
int server(server_t *serv);
void destroy_server(server_t *serv);

void server_loop(server_t *server);
void disconnect(server_t *server, client_t *client);
void die(server_t *server, client_t *client);

void add_teams(server_t *server, char *name);
void add_to_team(server_t *server, client_t *client, char *name);
void create_teams_clients(server_t *server);

void init_client(server_t *server, client_t *client);
void read_client(server_t *server, client_t *client);
void add_to_queue(client_t *client, char *msg);
void send_responses(client_t *client);

void add_to_map(map_t *map, entity_t *entity);

// new map ===================================================
void init_map(map_t *map);
void add_player_to_map(map_t *map, entity_t *entity);
void remove_player_from_map(map_t *map, entity_t *entity);
// ===========================================================

void remove_from_map(map_t *map, entity_t *entity);


int create_entity_at(map_t *map, uint x, uint y, entity_type_t type);
void generate_map(map_t *map);
void print_map(map_t *map);

#endif //PSU_ZAPPY_2017_SERVER_H
