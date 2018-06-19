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

gui_command_t *get_commands()
{
	static gui_command_t commands[] = {
		{"msz", &gui_msz, has_arg: false, status: false, arg: NULL},
		{"bct", &gui_bct, has_arg: true, status: false, arg: NULL},
		{"mct", &gui_mct, has_arg: false, status: false, arg: NULL},
		{"ppo", &gui_ppo, has_arg: true, status: false, arg: NULL},
		{"plv", &gui_plv, has_arg: true, status: false, arg: NULL},
		{"pin", &gui_pin, has_arg: true, status: false, arg: NULL},
		{"nbu", &gui_nbu, has_arg: false, status: false, arg: NULL},
		{"nbt", &gui_nbt, has_arg: false, status: false, arg: NULL},
		{"nbr", &gui_nbr, has_arg: false, status: false, arg: NULL},
		{"sgt", &gui_sgt, has_arg: false, status: false, arg: NULL},
		{"sst", &gui_sst, has_arg: true, status: false, arg: NULL},
		{"tna", &gui_tna, has_arg: false, status: false, arg: NULL},
		{NULL, NULL, false, false, NULL}
	};

	return commands;
}

uint32_t my_strlen_backn(char *str)
{
	uint32_t i = 0;

	while (str && str[i] != '\n')
		i++;
	return i;
}

/**
* Add a string to the GUI Queue
* @param gui
* @param str
*/
void add_to_gui_queue(gui_t *gui, char *str)
{
	uint32_t len = my_strlen_backn(str);

	debug(ERROR "%i => %s\n", len, str);
	if (!gui->logged)
		return;
	if (gui->len + len >= gui->size) {
		gui->size += GUI_QUEUE_SIZE;
		gui->queue = realloc(gui->queue, gui->size);
	}
	strcat(gui->queue + gui->len, str);
	gui->len += len;
}

static void check_gui_command(server_t *server, gui_command_t *command,
	char *arg)
{
	if (command->has_arg && !arg) {
		debug(INFO "%s need argument\n", command->name);
		add_to_gui_queue(&server->gui, "ko\n");
		return;
	}
	(*command->function)(server, arg, &command->status);
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
	for (gui_command_t *cmd = get_commands(); cmd->name; cmd++) {
		if (strcmp(name, cmd->name) == 0) {
			check_gui_command(server, cmd, arg);
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
	for (gui_command_t *cmd = get_commands(); cmd->name; cmd++) {
		if (cmd->status)
			(*cmd->function)(server, cmd->arg, &cmd->status);
	}
}