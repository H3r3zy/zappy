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

/**
* Add a string to the GUI Queue
* @param gui
* @param str
*/
void add_to_gui_queue(gui_t *gui, char *str)
{
	char *pos = strchr(str, '\n');
	size_t len = (pos) ? pos - str : 0;

	if (!gui->logged)
		return;
	if (gui->len + len >= gui->size) {
		gui->size += GUI_QUEUE_SIZE;
		gui->queue = realloc(gui->queue, gui->size);
	}
	strcat(gui->queue + gui->len, str);
	gui->len += len;
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