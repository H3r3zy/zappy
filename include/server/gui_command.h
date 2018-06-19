/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#ifndef PSU_ZAPPY_2017_GUI_COMMAND_H
#define PSU_ZAPPY_2017_GUI_COMMAND_H

#include <stdbool.h>
#include "server.h"

typedef struct {
	char *name;
	void (*function)(server_t *server, char *arg);
	bool argument;
} gui_command_t;


/**
 * GUI Map requests
 * @param server
 * @param arg
 */
void gui_msz(server_t *server, char *arg);
void gui_bct(server_t *server, char *arg);
void gui_mct(server_t *server, char *arg);

/**
 * GUI Player requests
 * @param server
 * @param client
 */
void gui_pnw(server_t *server, client_t *client);
void gui_ppo(server_t *server, char *arg);
void gui_plv(server_t *server, char *arg);
void gui_pin(server_t *server, char *arg);
void gui_pex(server_t *server, client_t *client);
void gui_pbc(server_t *server, client_t *client, char *arg);
void gui_pic(server_t *server, client_t *client, entity_t *entity);
void gui_pfk(server_t *server, client_t *client);
void gui_pie(server_t *server, client_t *client);
void gui_pdr(server_t *server, client_t *client, entity_type_t type);
void gui_pgt(server_t *server, client_t *client, entity_type_t type);
void gui_pdi(server_t *server, client_t *client);
void gui_enw(server_t *server, egg_t *egg, client_t *client);
void gui_eht(server_t *server, egg_t *egg);
void gui_ebo(server_t *server, egg_t *egg);
void gui_edi(server_t *server, egg_t *egg);

/**
 * GUI Server requests
 */
void gui_nbu(server_t *server, char *arg);
void gui_nbt(server_t *server, char *arg);
void gui_nbr(server_t *server, char *arg);

void gui_sgt(server_t *server, char *arg);
void gui_sst(server_t *server, char *arg);
void gui_tna(server_t *server, char *arg);

uint32_t read_uint(char *buffer, int *idx);
void write_uint(char *buffer, int *idx, uint32_t nb);

#endif //PSU_ZAPPY_2017_GUI_COMMAND_H
