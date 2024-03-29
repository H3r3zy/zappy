/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <server.h>
#include <memory.h>
#include <debug.h>
#include "server.h"

static client_t *get_client_by_id(server_t *server, size_t id)
{
	for (client_t *clt = server->clients; clt; clt = clt->next)
		if (clt->entity->id == id)
			return clt;
	return NULL;
}

/**
*
* @param server
* @param arg
*
* @response ppo clientID<uint32_t> posX<uint32_t> posY<uint32_t>
*/
void gui_ppo(server_t *server, char *arg, __attribute__((unused)) bool *status)
{
	char *err = NULL;
	long id = (arg) ? strtol(arg, &err, 10) : 0;
	static char buff[22] = "ppo clID posX posY\n";
	int idx = 4;
	client_t *clt = (!*err && id > 0)
		? get_client_by_id(server, (size_t)id) : NULL;

	if (clt) {
		write_uint32(buff, &idx, id);
		idx++;
		write_uint32(buff, &idx, (uint32_t) POS(clt).x);
		idx++;
		write_uint32(buff, &idx, (uint32_t) POS(clt).y);
		buff[idx] = -5;
		add_to_gui_queue(&server->gui, buff, idx + 1);
	} else
		add_to_gui_queue(&server->gui, GUI_KO, 3);
}

/**
*
* @param server
* @param arg
*
* @ersponse plv clientID<uint32_t> level<uint32_t>
*/
void gui_plv(server_t *server, char *arg, __attribute__((unused)) bool *status)
{
	char *err = NULL;
	long id = (arg) ? strtol(arg, &err, 10) : 0;
	static char buff[16] = "plv clID plvl\n";
	client_t *clt = (!*err && id > 0)
		? get_client_by_id(server, (size_t)id) : NULL;
	int idx = 4;

	if (clt) {
		write_uint32(buff, &idx, id);
		idx++;
		write_uint32(buff, &idx, clt->user.level);
		buff[idx] = -5;
		add_to_gui_queue(&server->gui, buff, idx + 1);
	} else
		add_to_gui_queue(&server->gui, GUI_KO, 3);
}

static void write_pin_clt_infos(client_t *clt, char buff[55],
	int *idx, uint32_t id)
{
	write_uint32(buff, idx, id);
	(*idx)++;
	write_uint32(buff, idx, (uint32_t) POS(clt).x);
	(*idx)++;
	write_uint32(buff, idx, (uint32_t) POS(clt).y);
	(*idx)++;
	write_uint32(buff, idx, clt->user.bag[Food]);
	(*idx)++;
}

/**
*
* @param server
* @param arg
*
* @response pin clientID<uint32_t> posX<uint32_t> posY<uint32_t>
* 	food<uint32_t> linemate<uint32_t> deraumere<uint32_t> sibur<uint32_t>
* 	mendiane<uint32_t> phiras<uint32_t> thystame<uint32_t>
*/
void gui_pin(server_t *server, char *arg, __attribute__((unused)) bool *status)
{
	char *err = NULL;
	long id = (arg) ? strtol(arg, &err, 10) : 0;
	static char buff[55] = "pin clid posx posy food line dera sibu mend "
		"phir thys\n";
	int idx = 4;
	client_t *clt = (!*err && id > 0)
		? get_client_by_id(server, (size_t)id) : NULL;

	if (clt) {
		write_pin_clt_infos(clt, buff, &idx, (uint32_t)id);
		for (uint i = 0; i <= Thystame; i++) {
			write_uint32(buff, &idx, clt->user.bag[i]);
			idx++;
		}
		buff[idx - 1] = -5;
		add_to_gui_queue(&server->gui, buff, idx);
	} else
		add_to_gui_queue(&server->gui, GUI_KO, 3);
}