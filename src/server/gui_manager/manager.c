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

uint32_t my_strlen_proto(char const *str)
{
	uint32_t i = 0;

	while (str && str[i] != -5)
		i++;
	return i;
}

/**
* Add a string to the GUI Queue
* @param gui
* @param str
*/
void add_to_gui_queue(gui_t *gui, char *str, int len)
{
	if (!gui->logged)
		return;
	if (gui->len + len >= gui->size) {
		gui->size += GUI_QUEUE_SIZE;
		gui->queue = realloc(gui->queue, gui->size);
	}

	memcpy(gui->queue + gui->len, str, len);
	gui->len += len;
}

static int read_gui(gui_t *gui)
{
	char buff[READ_SIZE + 1];
	ssize_t status = read(gui->fd, buff, READ_SIZE);

	if (status < 1)
		return 1;
	buff[status] = 0;
	if (strlen(gui->buff) + status >= READ_SIZE) {
		gui->buff_size += READ_SIZE;
		gui->buff = realloc(gui->buff, gui->buff_size + 1);
	}
	strcat(gui->buff, buff);
	gui->buff_len += status;
	return 0;
}

static void shift_gui_buff(server_t *server, size_t off)
{
	if (server->gui.buff[off]) {
		memmove(server->gui.buff, server->gui.buff + off,
			server->gui.buff_len - off + 1);
		server->gui.buff_len -= off;
	}
	else
		server->gui.buff_len = 0;
}

int pollin_gui(server_t *server)
{
	int status = read_gui(&server->gui);
	char *cmdend;
	char *cmd;
	size_t off = 0;

	if (status != 0)
		return 1;
	cmd = server->gui.buff;
	cmdend = strchr(cmd, '\n');
	while (cmdend) {
		*cmdend = 0;
		gui_command_manager(server, cmd);
		off += cmdend - cmd + 1;
		cmd = cmdend + 1;
		cmdend = strchr(cmd, '\n');
	}
	*server->gui.buff = 0;
	shift_gui_buff(server, off);
	return 0;
}