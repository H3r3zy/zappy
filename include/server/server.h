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

#define FOOD_UNIT_TIME (126)
#define EGG_UNIT_TIME (600)

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

typedef enum status_e {
	NORMAL,
	INCANTATION,
	EGG
} status_t;

typedef struct {
	int x;
	int y;
} pos_t;

typedef struct entity_s {
	ulong id;
	entity_type_t type;
	void *ptr;
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

typedef struct task_s {
	long long int started_time;
	uint time_unit;
	char *command;
	void (*function)(server_t *server, client_t *invoker, char *command);
} task_t;

typedef struct egg_s {
	long long int started_time;
	teams_t *team;
	client_t *client;
	pos_t pos;
	struct egg_s *prev;
	struct egg_s *next;
} egg_t;

struct client_s {
	socket_t fd;
	user_t user;
	task_t *task[LIMIT_TASK_NUMBER];
	teams_t *team;
	char *queue[LIMIT_TASK_NUMBER + 1];
	size_t queue_index;
	entity_t *entity;
	long long int started_time;
	status_t status;
	struct client_s *prev;
	struct client_s *next;
};

struct teams_s {
	char *name;
	uint remaining_place;
	client_t **clients;
	egg_t *eggs;
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

#define UPDATE_RESOURCE(m, p, t, n) ((m)->map[(p).y][(p).x].items[(t)] += (n))

struct server_s {
	socket_t fd;
	ushort port;
	uint freq;
	uint max_clients_per_teams;
	map_t map;
	teams_t *teams;
	client_t *clients;
	size_t client_nb;
};

extern char *str_types[ENTITY_NB];

char *gnl(int fd, char *delim);

int server(server_t *serv);
void destroy_server(server_t *serv);

void server_loop(server_t *server);
void disconnect(server_t *server, client_t *client);
void die(server_t *server, client_t *client);

void add_teams(server_t *server, char *name);
void add_to_team(server_t *server, client_t *client, char *name);
void create_teams_clients(server_t *server);

void handle_new_client(server_t *server);
int read_client(server_t *server, client_t *client);
void add_to_queue(client_t *client, char *msg);
int send_responses(client_t *client);

void add_to_map(map_t *map, entity_t *entity);

// new map ===================================================
void init_map(map_t *map);
void add_player_to_map(map_t *map, entity_t *entity);
void remove_player_from_map(map_t *map, entity_t *entity);
void move_player_to(map_t *map, entity_t *entity, pos_t *pos);
// ===========================================================

void print_map(map_t *map);

int get_o_w_dlt(pos_t *delta, orientation_t orientation);
void fill_delta(pos_t *size, pos_t *pos1, pos_t *pos2, pos_t *delta);


#define POS(c) (c)->entity->pos
#define OR(c) (c)->user.orientation

#endif //PSU_ZAPPY_2017_SERVER_H
