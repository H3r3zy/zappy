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

/**
 * GUI Server requests
 */
void gui_nbu(server_t *server, char *arg);
void gui_nbt(server_t *server, char *arg);
void gui_nbr(server_t *server, char *arg);

void gui_sgt(server_t *server, char *arg);
void gui_sst(server_t *server, char *arg);
void gui_tna(server_t *server, char *arg);

#endif //PSU_ZAPPY_2017_GUI_COMMAND_H
