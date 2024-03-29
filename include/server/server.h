/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_SERVER_H
#define PSU_ZAPPY_2017_SERVER_H


typedef struct teams_s teams_t;
typedef struct look_opt_s look_opt_t;
typedef struct look_type_s look_type_t;

#include <unistd.h>
#include <poll.h>
#include <stdint.h>
#include "socket.h"
#include "command.h"

#define READ_SIZE (1 << 8)
#define LIMIT_TASK_NUMBER (10)

#define RESOURCE_NB (7)

#define ENTITY_NB ((RESOURCE_NB) + 1)
#define START_FOOD (10)

#define EGG_ID ((RESOURCE_NB) + 1)

#define FOOD_UNIT_TIME (126)
#define EGG_UNIT_TIME (600)

#define LOOK_STR_SIZE (1 << 9)

#define GUI_QUEUE_SIZE (1 << 12)
#define GUI_OK ((char []){'o', 'k', -5})
#define GUI_KO ((char []){'k', 'o', -5})

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
	struct entity_s *prev;
	struct entity_s *next;
	pos_t pos;
	uint32_t id;
	void *ptr;
} entity_t;

typedef struct {
	uint32_t bag[RESOURCE_NB];
	uint32_t level;
	uint32_t vision;
	orientation_t orientation;
} user_t;

typedef struct task_s {
	long long int started_time;
	uint32_t time_unit;
	char *command;
	void (*function)(server_t *server, client_t *invoker, char *command);
} task_t;

typedef struct egg_s {
	long long int started_time;
	pos_t pos;
	uint32_t id;
	struct egg_s *prev;
	struct egg_s *next;
	client_t *client;
	teams_t *team;
} egg_t;

struct client_s {
	socket_t fd;
	long long int started_time;
	user_t user;
	task_t *task[LIMIT_TASK_NUMBER];
	teams_t *team;
	char *queue[LIMIT_TASK_NUMBER + 1];
	entity_t *entity;
	struct client_s *prev;
	struct client_s *next;
	status_t status;
	int queue_index;
	char *buff;
	size_t buff_len;
	size_t buff_size;
};

struct teams_s {
	client_t **clients;
	struct teams_s *next;
	egg_t *eggs;
	char *name;
	uint32_t remaining_place;
	uint32_t client_max;
};

typedef struct cell_s {
	entity_t *players;
	uint32_t items[RESOURCE_NB];
} cell_t;

typedef struct {
	pos_t size;
	cell_t **map;
	uint32_t stock[RESOURCE_NB + 1];
	uint32_t max_id;
} map_t;

typedef struct gui_s {
	char *queue;
	size_t size;
	size_t len;
	int fd;
	char logged;
	char *buff;
	size_t buff_len;
	size_t buff_size;
} gui_t;

struct server_s {
	socket_t fd;
	ushort port;
	uint32_t freq;
	uint32_t max_clients_per_teams;
	map_t map;
	teams_t *teams;
	teams_t *end;
	client_t *clients;
	uint32_t client_nb;
	gui_t gui;
};

char *gnl(int fd, char *delim);

int server(server_t *serv);
void destroy_server(server_t *serv);
void is_ended(server_t *server);

void server_loop(server_t *server);
void disconnect(server_t *server, client_t *client);
void die(server_t *server, client_t *client);

void add_teams(server_t *server, char *name);
void add_to_team(server_t *server, client_t *client, char *name);
void create_teams_clients(server_t *server);
void add_slot_in_team(teams_t *teams);

void handle_new_client(server_t *server);
int pollin_client(server_t *server, client_t *client);
void add_to_queue(client_t *client, char *msg);
int send_responses(client_t *client);

int try_write(int fd, char *msg);
int try_write_gui(int fd, char *msg, uint32_t len);

int pollin_gui(server_t *server);
void gui_continue_commands(server_t *);
void add_to_gui_queue(gui_t *gui, char *str, int len);

void init_map(map_t *map);
void add_player_to_map(map_t *map, entity_t *entity);
void remove_player_from_map(map_t *map, entity_t *entity);
void move_player_to(map_t *map, entity_t *entity, pos_t *pos);

int get_o_w_dlt(pos_t *delta, orientation_t orientation);
void fill_delta(pos_t *size, pos_t *pos1, pos_t *pos2, pos_t *delta);

void update_resource(map_t *map, pos_t *pos, entity_type_t t, int n);

void write_uint32(char *buffer, int *idx, uint32_t nb);
uint32_t read_uint32(char *buffer, int *idx);

size_t char_nb(const char *str, char c);
void concat(char *toadd, size_t len, look_opt_t *opt);

int read_client(client_t *client);
int command_manager(server_t *server, client_t *client, char *command);

extern look_type_t ENTITY_NAMES[ENTITY_NB];

#define POS(c) (c)->entity->pos
#define OR(c) (c)->user.orientation

#endif //PSU_ZAPPY_2017_SERVER_H
