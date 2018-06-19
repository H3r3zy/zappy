/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manager.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gui_command.h"
#include "debug.h"
#include "server.h"

static const gui_command_t COMMAND[] = {
	{"msz", &gui_msz, false},
	{"ppo", &gui_ppo, true},
	{"plv", &gui_plv, true},
	{"pin", &gui_pin, true},
	{"bct", &gui_bct, true},
	{"mct", &gui_mct, false},
	{"nbu", &gui_nbu, false},
	{"nbt", &gui_nbt, false},
	{"nbr", &gui_nbr, false},
	{"sgt", &gui_sgt, false},
	{"sst", &gui_sst, true},
	{"tna", &gui_tna, false},
	{NULL, NULL, false}
};

/**
 * Add a string to the GUI Queue
 * @param gui
 * @param str
 */
void add_to_gui_queue(gui_t *gui, char *str)
{
	uint32_t len = strlen(str);

	if (!gui->logged)
		return;
	printf("str: %s\n", str);
	if (gui->len + len >= gui->size) {
		gui->size += GUI_QUEUE_SIZE;
		gui->queue = realloc(gui->queue, gui->size);
	}
	strcat(gui->queue + gui->len, str);
	gui->len += len;
}

static void check_gui_command(server_t *server, uint32_t i, char *arg)
{
	if (COMMAND[i].argument && !arg) {
		debug(INFO "%s need argument\n", COMMAND[i].name);
		add_to_gui_queue(&server->gui, "ko\n");
		return;
	}
	(*COMMAND[i].function)(server, arg);
}

static void gui_command_manager(server_t *server, char *command)
{
	size_t tmp_len = strlen(command);
	char *name = strtok(command, " \t");
	char *arg = NULL;

	if (!name)
		return;
	if (tmp_len != strlen(name))
		arg = &command[strlen(name) + 1];
	for (uint32_t i = 0; COMMAND[i].name; i++) {
		if (strcmp(name, COMMAND[i].name) == 0) {
			check_gui_command(server, i, arg);
			return;
		}
	}
	add_to_gui_queue(&server->gui, "ko\n");
}

int read_gui(server_t *server)
{
	char *request = gnl(server->gui.fd, "\n");

	if (!request)
		return 1;
	debug(INFO "GUI request : %s\n", request);
	gui_command_manager(server, request);
	free(request);
	return 0;
}