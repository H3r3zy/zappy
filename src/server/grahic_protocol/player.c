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
	uint32_t id = atoi(arg);
	static char buff[22] = "ppo clID posX posY\n";
	int idx = 4;
	client_t *player = get_client_by_id(server, id);

	if (player) {
		write_uint32(buff, &idx, id);
		idx++;
		write_uint32(buff, &idx, (uint32_t) POS(player).x);
		idx++;
		write_uint32(buff, &idx, (uint32_t) POS(player).y);
		add_to_gui_queue(&server->gui, buff);
	} else
		add_to_gui_queue(&server->gui, "ko\n");
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
	uint32_t id = atoi(arg);
	static char buff[16] = "plv clID plvl\n";
	client_t *player = get_client_by_id(server, id);
	int idx = 4;

	if (player) {
		write_uint32(buff, &idx, id);
		idx++;
		write_uint32(buff, &idx, player->user.level);
		add_to_gui_queue(&server->gui, buff);
	} else
		add_to_gui_queue(&server->gui, "ko\n");
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
	uint32_t id = atoi(arg);
	static char buff[55] = "pin clid posx posy food line dera sibu mend "
		"phir thys\n";
	int idx = 4;
	client_t *clt = get_client_by_id(server, id);

	if (clt) {
		write_pin_clt_infos(clt, buff, &idx, id);
		for (uint i = 1; i <= Thystame; i++) {
			write_uint32(buff, &idx, clt->user.bag[i]);
			idx++;
		}
		add_to_gui_queue(&server->gui, buff);
	} else
		add_to_gui_queue(&server->gui, "ko\n");
}