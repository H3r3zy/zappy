/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** command.c
*/

#include <string.h>
#include "gui_command.h"
#include "debug.h"
#include "server.h"

gui_command_t *get_commands(void)
{
	static gui_command_t commands[] = {
		{"msz", &gui_msz, false, false, NULL},
		{"bct", &gui_bct, true, false, NULL},
		{"mct", &gui_mct, false, false, NULL},
		{"ppo", &gui_ppo, true, false, NULL},
		{"plv", &gui_plv, true, false, NULL},
		{"pin", &gui_pin, true, false, NULL},
		{"nbu", &gui_nbu, false, false, NULL},
		{"nbt", &gui_nbt, false, false, NULL},
		{"nbr", &gui_nbr, false, false, NULL},
		{"sgt", &gui_sgt, false, false, NULL},
		{"sst", &gui_sst, true, false, NULL},
		{"tna", &gui_tna, false, false, NULL},
		{NULL, NULL, false, false, NULL}
	};

	return commands;
}

static void check_gui_command(server_t *server, gui_command_t *command,
	char *arg)
{
	if (command->has_arg && !arg) {
		debug(INFO "%s need argument\n", command->name);
		add_to_gui_queue(&server->gui, GUI_KO, 3);
		return;
	}
	(*command->function)(server, arg, &command->status);
}

void gui_command_manager(server_t *server, char *command)
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
	add_to_gui_queue(&server->gui, GUI_KO, 3);
}

void gui_continue_commands(server_t *server)
{
	for (gui_command_t *cmd = get_commands(); cmd->name; cmd++) {
		if (cmd->status)
			(*cmd->function)(server, cmd->arg, &cmd->status);
	}
}