/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** Created by sahel.lucas-saoudi@epitech.eu,
*/

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "server.h"
#include "command.h"
#include "gui_command.h"
#include "debug.h"
#include "scheduler.h"

static const command_t COMMAND[] = {
	{
		name: "Forward",
		function: &forward_cmd,
		verify: NULL,
		time_unit: 7,
		argument: false
	}, {
		name: "Right",
		function: &right_cmd,
		verify: NULL,
		time_unit: 7,
		argument: false
	}, {
		name: "Left",
		function: &left_cmd,
		verify: NULL,
		time_unit: 7,
		argument: false
	}, {
		name: "Look",
		function: &look_cmd,
		verify: NULL,
		time_unit: 7,
		argument: false
	}, {
		name: "Inventory",
		function: &inventory_cmd,
		verify: NULL,
		time_unit: 1,
		argument: false
	}, {
		name: "Broadcast",
		function: &broadcast_cmd,
		verify: NULL,
		time_unit: 7,
		argument: true
	}, {
		name: "Connect_nbr",
		function: &connect_nbr_cmd,
		verify: NULL,
		time_unit: 0,
		argument: false
	}, {
		name: "Fork",
		function: &fork_cmd,
		verify: NULL,
		time_unit: 42,
		argument: false
	}, {
		name: "Eject",
		function: &eject_cmd,
		verify: NULL,
		time_unit: 7,
		argument: false
	}, {
		name: "Take",
		function: &take_cmd,
		verify: NULL,
		time_unit: 7,
		argument: true
	}, {
		name: "Set",
		function: &set_cmd,
		verify: NULL,
		time_unit: 7,
		argument: true
	}, {
		name: "Incantation",
		function: &incantation_cmd,
		verify: &incantation_verify,
		time_unit: 300,
		argument: false
	},
#ifdef DEBUG
	{
		name: "Pos",
		function: &pos,
		verify: NULL,
		time_unit: 1,
		argument: false
	}, {
		name: "Setpos",
		function: &setpos_cmd,
		verify: NULL,
		time_unit: 1,
		argument: false
	},
#endif
	{
		name: NULL,
		function: NULL,
		verify: NULL,
		time_unit: 0,
		argument: false
	}
};

static void check_command(server_t *server, client_t *client, uint32_t i,
	char *arg
)
{
	if (client->status == EGG) {
		debug(INFO "'%i' is an EGG, can't do action\n", client->fd);
		add_to_queue(client, "ko\n");
		return;
	}
	if (COMMAND[i].argument && !arg) {
		debug(INFO "%s need argument\n", COMMAND[i].name);
		add_to_queue(client, "ko\n");
		return;
	}
	if (COMMAND[i].verify && !COMMAND[i].verify(server, client, arg)) {
		add_to_queue(client, "ko\n");
	}
	add_task_to_schedule(client, COMMAND[i].time_unit, arg,
		COMMAND[i].function);
}

static void add_gui_client(server_t *server, client_t *client)
{
	client_t **list = &server->clients;

	debug(GINFO "GUI Client connected\n");
	if (client->next)
		client->next->prev = client->prev;
	if (client->prev)
		client->prev->next = client->next;
	if (*list == client)
		*list = client->next;
	--server->client_nb;
	server->gui.fd = client->fd;
	server->gui.logged = 1;
	add_to_gui_queue(&server->gui, (char[]){'o', 'k', -5}, 3);
	for (client_t *clt = server->clients; clt; clt = clt->next) {
		if (clt->team)
			gui_pnw(server, clt);
	}
}

static int set_client_team(server_t *server, client_t *client, char *command)
{
	if (!strcmp(command, "gui"))
		add_gui_client(server, client);
	else {
		debug(INFO "'%i' Try to join '%s' team\n", client->fd,
			command);
		add_to_team(server, client, command);
	}
	return 0;
}

static int command_manager(server_t *server, client_t *client, char *command)
{
	size_t tmp_len = strlen(command);
	char *name = strtok(command, " \t");
	char *arg = NULL;

	if (!name)
		return 0;
	if (!client->team)
		return set_client_team(server, client, command);
	if (tmp_len != strlen(name))
		arg = &command[strlen(name) + 1];
	for (uint32_t i = 0; COMMAND[i].name; i++) {
		if (strcmp(name, COMMAND[i].name) == 0) {
			check_command(server, client, i, arg);
			return 0;
		}
	}
	add_to_queue(client, "ko\n");
	return 1;
}

static int read_client(client_t *client)
{
	char buff[READ_SIZE + 1];
	ssize_t status = read(client->fd, buff, READ_SIZE);

	if (status < 1)
		return 1;
	buff[status] = 0;
	if (strlen(client->buff) + status >= READ_SIZE) {
		client->buff_size += READ_SIZE;
		client->buff = realloc(client->buff, client->buff_size + 1);
	}
	strcat(client->buff, buff);
	client->buff_len += status;
	return 0;
}

int pollin_client(server_t *server, client_t *client)
{
	int status = read_client(client);
	char *end;
	char *cmd;
	size_t off = 0;

	if (status != 0)
		return 1;
	cmd = client->buff;
	end = strchr(cmd, '\n');
	while (end) {
		*end = 0;
		command_manager(server, client, cmd);
		off += end - cmd + 1;
		cmd = end + 1;
		end = strchr(cmd, '\n');
	}
	*client->buff = 0;
	if (client->buff[off]) {
		memmove(client->buff, client->buff + off,
			client->buff_len - off + 1);
		client->buff_len -= off;
	}
	return 0;
}