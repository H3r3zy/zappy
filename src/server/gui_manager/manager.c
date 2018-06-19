/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manager.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gui_command.h>
#include "gui_command.h"
#include "debug.h"
#include "server.h"

static const gui_command_t COMMAND[] = {
	{"msz", &gui_msz, has_arg: false, status: false, NULL},
	{"bct", &gui_bct, has_arg: true, status: false, NULL},
	{"mct", &gui_mct, has_arg: false, status: false, NULL},
	{"ppo", &gui_ppo, has_arg: true, status: false, NULL},
	{"plv", &gui_plv, has_arg: true, status: false, NULL},
	{"pin", &gui_pin, has_arg: true, status: false, NULL},
	{"nbu", &gui_nbu, has_arg: false, status: false, NULL},
	{"nbt", &gui_nbt, has_arg: false, status: false, NULL},
	{"nbr", &gui_nbr, has_arg: false, status: false, NULL},
	{"sgt", &gui_sgt, has_arg: false, status: false, NULL},
	{"sst", &gui_sst, has_arg: true, status: false, NULL},
	{"tna", &gui_tna, has_arg: false, status: false, NULL},
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
	if (COMMAND[i].has_arg && !arg) {
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

void gui_continue_commands(server_t *server)
{
	/*for (const gui_command_t *cmd = COMMAND; cmd->name; cmd++) {
		if (cmd->status)
			(*cmd->function)(server, cmd->arg);
	}*/
}