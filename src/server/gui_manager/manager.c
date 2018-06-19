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

uint32_t my_strlen_backn(char *str)
{
	uint32_t i = 0;

	while (str && str[i] != '\n')
		i++;
	return i;
}

void my_strcpy_backn(char *dest, char *str)
{
	uint32_t  i =0;

	while (str && str[i] != '\n') {
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\n';
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
	my_strcpy_backn(gui->queue + gui->len, str);
	gui->len += len;
	debug(ERROR "%s\n", gui->queue);
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